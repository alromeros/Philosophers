/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 20:38:20 by alromero          #+#    #+#             */
/*   Updated: 2020/04/11 14:08:30 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_phil *philo)
{
	sem_wait(&philo->datos->forks_m);
	put_message(FORK, philo);
	sem_wait(&philo->datos->forks_m);
	put_message(FORK, philo);
	sem_wait(&philo->mutex);
	philo->is_eating = 1;
	put_message(EAT, philo);
	philo->last_eat = get_time();
	usleep(philo->datos->time_to_eat * 1000);
	philo->limit = philo->last_eat + philo->datos->time_to_die;
	put_message(SLEEP, philo);
	philo->is_eating = 0;
	sem_post(&philo->mutex);
	sem_post(&philo->eat_count_m);
	sem_post(&philo->datos->forks_m);
	sem_post(&philo->datos->forks_m);
}
