/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 12:41:02 by alromero          #+#    #+#             */
/*   Updated: 2020/04/11 20:44:34 by alromero         ###   ########.fr       */
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
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_DEAD);
	if (state->filosofo)
	{
		i = 0;
		while (i < state->number_of_philosophers)
		{
			semaphore_namer(SEM_PHILO, (char*)semaphore, i);
			sem_unlink(semaphore);
			semaphore_namer(SEM_PHILOEAT, (char*)semaphore, i++);
			sem_unlink(semaphore);
		}
		free(state->filosofo);
		free(state);
	}
}

void					init_philos(t_utils *data)
{
	int			j;
	char		semaphore[255];
	pthread_t	tid;

	j = 0;
	init_semaphores(data);
	while (j < data->number_of_philosophers)
	{
		data->filosofo[j].is_eating = 0;
		data->filosofo[j].position = j;
		data->filosofo[j].eat_count = 0;
		data->filosofo[j].datos = data;
		semaphore_namer(SEM_PHILO, (char*)semaphore, j);
		data->filosofo[j].mutex = ft_sem_open(semaphore, 1);
		semaphore_namer(SEM_PHILOEAT, (char*)semaphore, j);
		data->filosofo[j].eat_count_m = ft_sem_open(semaphore, 0);
		j++;
		usleep(100);
	}
	fork_init(data);
	if (data->must_eat_count > 0)
	{
		pthread_create(&tid, NULL, &watchover, (void*)data);
		pthread_detach(tid);
	}
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
	free_everything(data);
	usleep(1000);
	return (0);
}
