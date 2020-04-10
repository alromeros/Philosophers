/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_things.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 18:18:29 by alromero          #+#    #+#             */
/*   Updated: 2020/04/09 16:33:09 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    put_message(int preset, t_phil *philo)
{
    pthread_mutex_lock(&philo->datos->write);
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
        write (1, " has taken a fork\n", 18);
    if (preset != OVER && preset != DIED)
        pthread_mutex_unlock(&philo->datos->write);
}

void    *monitor(void *philos)
{
    t_phil *copy;

    copy = (t_phil *)philos;
    while (!copy->datos->someone_died)
    {
        pthread_mutex_lock(&copy->mutex);
        if ((!copy->is_eating) && (get_time() > copy->limit) && !copy->datos->someone_died)
        {
            put_message(DIED, philos);
            copy->datos->someone_died = 1;
            pthread_mutex_unlock(&copy->mutex);
            pthread_mutex_unlock(&copy->datos->dead);
            return (NULL);
        }
        pthread_mutex_unlock(&copy->mutex);
        usleep(1000);
    }
    return (void *)(0);
}

void    *do_things(void *philos)
{
    t_phil *copy;
    pthread_t tid;
    
    copy = (t_phil *)philos;
    pthread_mutex_init(&copy->mutex, NULL);
    copy->last_eat = get_time();
    copy->limit = copy->last_eat + copy->datos->time_to_die;
    if (pthread_create(&tid, NULL, monitor, copy) != 0)
        return ((void *) 1);
    copy->datos->start = get_time();
    while (!copy->datos->someone_died)
    {
        eat(copy);
        usleep(copy->datos->time_to_sleep * 1000);
        put_message(THINK, philos);
    }
    return (NULL);
}

void    *watchover(void *data)
{
    t_utils *dato;
    int i;

    dato = (t_utils *)data;
    while (dato->must_eat_number < dato->must_eat_count)
    {
        i = 0;
        while (i < dato->number_of_philosophers)
        {
            pthread_mutex_lock(&dato->filosofo[i].number_eat);
            i++;
        }
		dato->must_eat_number++;
	}
    put_message(OVER, dato->filosofo);
    dato->someone_died = 1;
	pthread_mutex_unlock(&dato->dead);
    return ((void *)0);
}
