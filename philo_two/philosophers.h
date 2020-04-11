/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 12:51:22 by alromero          #+#    #+#             */
/*   Updated: 2020/04/11 15:04:04 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <fcntl.h>
# include <pthread.h>
# define EAT 	0
# define SLEEP 	1
# define FORK 	2
# define THINK	3
# define DIED 	4
# define OVER   5

int							ft_atoi(char const *str);
unsigned long long			get_time(void);
void						ft_putnbr_fd(unsigned long long n, int fd);
typedef struct				s_phil
{
	int						position;
	int						is_eating;
	unsigned long long		limit;
	unsigned long long		last_eat;
	int						eat_count;
	struct s_utils			*datos;
	sem_t					mutex;
	sem_t					eat_count_m;
}							t_phil;
typedef struct				s_utils
{
	int						number_of_philosophers;
	unsigned long long		time_to_die;
	unsigned long long		time_to_eat;
	unsigned long long		time_to_sleep;
	int						must_eat_count;
	int						must_eat_number;
	int						someone_died;
	t_phil					*filosofo;
	sem_t					forks_m;
	sem_t					write;
	sem_t					dead;
	unsigned long long		start;
}							t_utils;
void						put_message(int preset, t_phil *philo);
void						*do_things(void *philos);
void						*monitor(void *philos);
void						put_message(int preset, t_phil *philo);
void						*watchover(void *state_v);
void						take_forks(t_phil *copy);
void						drop_forks(t_phil *copy);
void						eat(t_phil *philo);
void						init_philos(t_utils *data);
void						parse_params(int argc, char **argv, t_utils *data);
void						init_semaphores(t_utils *state);
void						init_philos(t_utils *data);

#endif
