/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_things.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 20:52:27 by alromero          #+#    #+#             */
/*   Updated: 2020/04/10 17:51:56 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int					start_process(t_utils *state)
{
	int			i;

	state->start = get_time();
	i = 0;
	while (i < state->number_of_philosophers)
	{
		state->filosofo[i].pid = fork();
		if (state->filosofo[i].pid < 0)
			return (1);
		else if (state->filosofo[i].pid == 0)
		{
			do_things(&state->filosofo[i]);
			exit(0);
		}
		usleep(100);
		i++;
	}
	return (0);
}

void				*do_things(void *philos)
{
	t_phil		*copy;
	pthread_t	tid;

	copy = (t_phil *)philos;
	copy->last_eat = get_time();
	copy->limit = copy->last_eat + copy->datos->time_to_die;
	pthread_create(&tid, NULL, monitor, copy);
	pthread_detach(tid);
	copy->datos->start = get_time();
	while (!copy->datos->someone_died)
	{
		eat(copy);
		usleep(copy->datos->time_to_sleep * 1000);
		put_message(THINK, philos);
	}
	return (NULL);
}

void				*monitor(void *philos)
{
	t_phil *copy;

	copy = (t_phil *)philos;
	while (!copy->datos->someone_died)
	{
		sem_wait(copy->mutex);
		if (!copy->is_eating && get_time() > 
		copy->limit && !copy->datos->someone_died)
		{
			put_message(DIED, philos);
			copy->datos->someone_died = 1;
			sem_post(copy->mutex);
			sem_post(copy->datos->dead);
			return (NULL);
		}
		sem_post(copy->mutex);
		usleep(1000);
	}
	return ((void *)0);
}

void				*watchover(void *state_v)
{
	t_utils *state;
	int		i;

	state = (t_utils*)state_v;
	while (state->must_eat_number < state->must_eat_count)
	{
		i = 0;
		while (i < state->number_of_philosophers)
		{
			sem_wait(state->filosofo[i].eat_count_m);
			i++;
		}
		state->must_eat_number++;
	}
	put_message(OVER, state->filosofo);
	state->someone_died = 1;
	sem_post(state->dead);
	return ((void*)0);
}

void				put_message(int preset, t_phil *philo)
{
	sem_wait(philo->datos->write);
	sem_wait(philo->datos->write_m);
	if (!philo->datos->someone_died)
	{
		ft_putnbr_fd(get_time() - philo->datos->start, 1);
		write(1, " ", 1);
		if (preset == OVER)
			write(1, "GAME OVER\n", 10);
		else
			ft_putnbr_fd(philo->position + 1, 1);
		if (preset == EAT)
			write(1, " is eating\n", 11);
		else if (preset == SLEEP)
			write(1, " is sleeping\n", 13);
		else if (preset == THINK)
			write(1, " is thinking\n", 13);
		else if (preset == DIED)
			write(1, " died\n", 6);
		else if (preset == FORK)
			write(1, " has taken a fork\n", 18);
	}
	if (preset != DIED && preset != OVER)
		sem_post(philo->datos->write_m);
	sem_post(philo->datos->write);
}
