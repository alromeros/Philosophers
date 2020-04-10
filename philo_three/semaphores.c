/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 20:50:46 by alromero          #+#    #+#             */
/*   Updated: 2020/04/10 18:18:55 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int					init_semaphores(t_utils *state)
{
	state->forks_m = ft_sem_open(SEMAPHORE_FORK, state->number_of_philosophers);
	state->write = ft_sem_open(SEMAPHORE_WRITE, 1);
	state->dead = ft_sem_open(SEMAPHORE_DEAD, 0);
	state->write_m = ft_sem_open(SEMAPHORE_DEADW, 1);
	return (0);
}

sem_t				*ft_sem_open(char const *name, int value)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

char				*make_semaphore_name(char const *base,
char *buffer, int position)
{
	int	i;

	i = ft_strcpy(buffer, base);
	while (position > 0)
	{
		buffer[i++] = (position % 10) + '0';
		position /= 10;
	}
	buffer[i] = 0;
	return (buffer);
}
