/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 18:16:42 by alromero          #+#    #+#             */
/*   Updated: 2020/04/10 14:08:54 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_phil *philo)
{
    pthread_mutex_lock(&philo->datos->forks_m[philo->lfork]);
    put_message(FORK, philo);
    pthread_mutex_lock(&philo->datos->forks_m[philo->rfork]);
    put_message(FORK, philo);
	pthread_mutex_lock(&philo->mutex);
	philo->is_eating = 1;
   // usleep(philo->datos->time_to_eat * 1000);
    put_message(EAT, philo);
    philo->last_eat = get_time();
	usleep(philo->datos->time_to_eat * 1000);
	philo->limit = philo->last_eat + philo->datos->time_to_die;
    put_message(SLEEP, philo);
    philo->is_eating = 0;
	pthread_mutex_unlock(&philo->mutex);
    pthread_mutex_unlock(&philo->number_eat);
    pthread_mutex_unlock(&philo->datos->forks_m[philo->lfork]);
    pthread_mutex_unlock(&philo->datos->forks_m[philo->rfork]);
}
