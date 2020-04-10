/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 12:51:22 by alromero          #+#    #+#             */
/*   Updated: 2020/04/08 21:08:59 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
# define EAT 	0
# define SLEEP 	1
# define FORK 	2
# define THINK	3
# define DIED 	4
# define OVER   5
# define SEMAPHORE_FORK		"pSemaphoreFork"
# define SEMAPHORE_WRITE	"pSemaphoreWrite"
# define SEMAPHORE_DEAD		"pSemaphoreDead"
# define SEMAPHORE_PHILO	"pSemaphorePhilo"
# define SEMAPHORE_PHILOEAT	"pSemaphorePhiloEat"
# define SEMAPHORE_DEADW	"pSemaphoreDeadWrite"

int     			ft_strlen(char const *str);
int     			ft_atoi(char const *str);
unsigned long long	get_time(void);
void				ft_putnbr_fd(unsigned long long n, int fd);
int					ft_strcpy(char *dst, const char *src);
typedef struct		s_phil
{
	pid_t					pid;
	int						position;
	int						is_eating;
	unsigned long long		limit;
	unsigned long long		last_eat;
	int						lfork;
	int						rfork;
	int						eat_count;
	struct s_utils			*datos;
	sem_t					*mutex;
	sem_t 					*eat_count_m;
}					t_phil;
typedef struct  	s_utils
{
    int                 number_of_philosophers;
    unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	int				    must_eat_count;
	int					must_eat_number;
	int					someone_died;
	t_phil				*filosofo;
	sem_t				*forks_m;
	sem_t 				*write;
	sem_t				*write_m;
	sem_t				*dead;
	unsigned long long	start;

}               t_utils;
void				put_message(int preset, t_phil *philo);
int	start_process(t_utils *state);
void    *do_things(void *philos);
void    *monitor(void *philos);
void	*monitor_count(void *state_v);
void    put_message(int preset, t_phil *philo);
void    take_forks(t_phil *copy);
void    drop_forks(t_phil *copy);
void	eat(t_phil *philo);
int  init_semaphores(t_utils *state);
sem_t   *ft_sem_open(char const *name, int value);
char    *make_semaphore_name(char const *base, char *buffer, int position);

#endif
