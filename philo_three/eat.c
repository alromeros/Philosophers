/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 20:54:18 by alromero          #+#    #+#             */
/*   Updated: 2020/04/09 13:00:57 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_phil *philo)
{
    sem_wait(philo->datos->forks_m);
    put_message(FORK, philo);
    sem_wait(philo->datos->forks_m);
    put_message(FORK, philo);
	sem_wait(philo->mutex);
	philo->is_eating = 1;
    usleep(philo->datos->time_to_eat * 1000);
    put_message(EAT, philo);
 	philo->eat_count++;
    if ((philo->eat_count == philo->datos->must_eat_count) && philo->datos->must_eat_count)
        philo->datos->must_eat_number++;
    philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->datos->time_to_die;
    put_message(SLEEP, philo);
    philo->is_eating = 0;
    sem_post(philo->mutex);
    sem_post(philo->eat_count_m);
    sem_post(philo->datos->forks_m);
    sem_post(philo->datos->forks_m);
}
