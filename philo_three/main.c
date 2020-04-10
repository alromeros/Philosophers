/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 12:41:02 by alromero          #+#    #+#             */
/*   Updated: 2020/04/10 18:19:07 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void					free_everything(t_utils *state)
{
	int		i;
	char	semaphore[255];

	i = 0;
	while (i < state->number_of_philosophers)
		kill(state->filosofo[i++].pid, SIGKILL);
	sem_unlink(SEMAPHORE_FORK);
	sem_unlink(SEMAPHORE_WRITE);
	sem_unlink(SEMAPHORE_DEAD);
	if (state->filosofo)
	{
		i = 0;
		while (i < state->number_of_philosophers)
		{
			make_semaphore_name(SEMAPHORE_PHILO, (char*)semaphore, i);
			sem_unlink(semaphore);
			make_semaphore_name(SEMAPHORE_PHILOEAT, (char*)semaphore, i++);
			sem_unlink(semaphore);
		}
		free(state->filosofo);
	}
}

void					init_philos(t_utils *data)
{
	int			i;
	int			j;
	char		semaphore[255];
	pthread_t	tid;

	j = 0;
	i = data->number_of_philosophers;
	init_semaphores(data);
	while (j < i)
	{
		data->filosofo[j].is_eating = 0;
		data->filosofo[j].position = j;
		data->filosofo[j].eat_count = 0;
		data->filosofo[j].datos = data;
		make_semaphore_name(SEMAPHORE_PHILO, (char*)semaphore, j);
		data->filosofo[j].mutex = ft_sem_open(semaphore, 1);
		make_semaphore_name(SEMAPHORE_PHILOEAT, (char*)semaphore, j);
		data->filosofo[j].eat_count_m = ft_sem_open(semaphore, 0);
		j++;
		usleep(100);
	}
	start_process(data);
	if (data->must_eat_count > 0)
		pthread_create(&tid, NULL, &watchover, (void*)data);
	pthread_detach(tid);
}

void					parse_params(int argc, char **argv, t_utils *data)
{
	data->someone_died = 0;
	data->must_eat_number = 0;
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = 0;
	data->forks_m = (sem_t *)
	malloc(sizeof(sem_t) * data->number_of_philosophers);
	data->filosofo = (t_phil *)
	malloc(sizeof(t_phil) * data->number_of_philosophers);
	init_philos(data);
}

int						main(int argc, char **argv)
{
	t_utils *data;

	if (!(data = (t_utils *)malloc(sizeof(t_utils))))
		return (0);
	if (argc != 5 && argc != 6)
		return (write(1, "Error: Invalid arguments\n", 25));
	parse_params(argc, argv, data);
	sem_wait(data->dead);
	clear_state(data);
	usleep(1000);
	return (0);
}
