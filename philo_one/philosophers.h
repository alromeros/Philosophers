/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 10:49:51 by alromero          #+#    #+#             */
/*   Updated: 2020/04/09 16:31:47 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
# define EAT 	0
# define SLEEP 1
# define FORK 	2
# define THINK	3
# define DIED 	4
# define OVER   5


int     ft_strlen(char const *str);
int     ft_atoi(char const *str);
unsigned long long	get_time(void);
void	ft_putnbr_fd(unsigned long long n, int fd);
typedef struct		s_phil
{
	int				position;
	int				is_eating;
	unsigned long long		limit;
	unsigned long long		last_eat;
	int				lfork;
	int				rfork;
	struct s_utils	*datos;
	pthread_mutex_t	mutex;
	pthread_mutex_t		number_eat;
	pthread_mutex_t eat_m;
}					t_phil;
typedef struct  s_utils
{
    int                 number_of_philosophers;
    unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	int				    must_eat_count;
	int					must_eat_number;
	int					someone_died;
	t_phil				*filosofo;
	pthread_mutex_t		*forks_m;
	pthread_mutex_t 	write;
	pthread_mutex_t		wait;
	pthread_mutex_t		dead;
	unsigned long long	start;

}               t_utils;
void    put_message(int preset, t_phil *philo);
void    *monitor(void *philos);
void    *do_things(void *philos);
void    *watchover(void *data);
void    take_forks(t_phil *copy);
void    drop_forks(t_phil *copy);
void	eat(t_phil *philo);

#endif
