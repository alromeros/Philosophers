/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 10:49:09 by alromero          #+#    #+#             */
/*   Updated: 2020/04/25 14:09:55 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void			init_philos(t_utils *data)
{
	int			j;
	pthread_t	tid;

	j = 0;
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_lock(&data->dead);
	pthread_mutex_init(&data->monitor, NULL);
	while (j < data->number_of_philosophers)
	{
		data->filosofo[j].is_eating = 0;
		data->filosofo[j].position = j;
		data->filosofo[j].lfork = j;
		data->filosofo[j].rfork = (j + 1) % data->number_of_philosophers;
		data->filosofo[j].datos = data;
		pthread_create(&tid, NULL, do_things, (void *)&(data->filosofo[j]));
		j++;
		usleep(100);
	}
	if (data->must_eat_count > 0)
		pthread_create(&tid, NULL, &watchover, (void*)data);
	pthread_detach(tid);
}

void			parse_params(int argc, char **argv, t_utils *data)
{
	int i;

	i = 0;
	data->someone_died = 0;
	data->must_eat_number = 0;
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat_count = (argc == 6) ? ft_atoi(argv[5]) : 0;
	data->forks_m = (pthread_mutex_t *)
	malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	data->filosofo = (t_phil *)
	malloc(sizeof(t_phil) * data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&(data->forks_m[i]), NULL);
		pthread_mutex_init(&data->filosofo[i].number_eat, NULL);
		pthread_mutex_lock(&data->filosofo[i].number_eat);
		i++;
	}
	pthread_mutex_init(&data->write, NULL);
	init_philos(data);
}

void			free_everything(t_utils *data)
{
	int i;

	i = 0;
	if (data->someone_died)
	{
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_destroy(&(data->forks_m[i]));
			pthread_mutex_destroy(&(data->filosofo[i].mutex));
			pthread_mutex_destroy(&(data->filosofo[i].number_eat));
			i++;
		}
		pthread_mutex_destroy(&data->write);
		pthread_mutex_destroy(&data->dead);
		pthread_mutex_destroy(&data->monitor);
		free(data->filosofo);
		free(data->forks_m);
		free(data);
	}
}

int				main(int argc, char **argv)
{
	t_utils *data;

	if (!(data = (t_utils *)malloc(sizeof(t_utils))))
		return (0);
	if (argc != 5 && argc != 6)
		return (write(1, "Error: Invalid arguments\n", 25));
	parse_params(argc, argv, data);
	pthread_mutex_lock(&data->dead);
	pthread_mutex_unlock(&data->dead);
	free_everything(data);
	return (0);
}
