/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 12:41:02 by alromero          #+#    #+#             */
/*   Updated: 2020/04/11 14:56:30 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void				init_semaphores(t_utils *state)
{
	sem_init(&(state->forks_m), 0,  state->number_of_philosophers);
	sem_init(&(state->write), 0, 1);
	sem_init(&(state->dead), 0, 0);
}

void					free_everything(t_utils *state)
{
	int		i;

	sem_destroy(&state->forks_m);;
	sem_destroy(&state->write);
	sem_destroy(&state->dead);
	if (state->filosofo)
	{
		i = 0;
		while (i < state->number_of_philosophers)
		{
			sem_destroy(&state->filosofo[i].mutex);
			sem_destroy(&state->filosofo[i].eat_count_m);
			i++;
		}
		free(state->filosofo);
		free(state);
	}
}

void					init_philos(t_utils *data)
{
	int				i;
	int				j;
	pthread_t		tid;

	j = 0;
	i = data->number_of_philosophers;
	init_semaphores(data);
	while (j < i)
	{
		data->filosofo[j].is_eating = 0;
		data->filosofo[j].position = j;
		data->filosofo[j].eat_count = 0;
		data->filosofo[j].datos = data;
		sem_init(&(data->filosofo[j].mutex), 0, 1);
		sem_init(&(data->filosofo[j].eat_count_m), 0, 0);
		pthread_create(&tid, NULL, do_things, (void *)&(data->filosofo[j]));
		j++;
		usleep(100);
	}
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
	sem_wait(&data->dead);
	if (data->someone_died)
		free_everything(data);
}
