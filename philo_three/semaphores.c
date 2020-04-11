/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alromero <alromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 20:50:46 by alromero          #+#    #+#             */
/*   Updated: 2020/04/11 20:40:25 by alromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void				init_semaphores(t_utils *state)
{
	state->forks_m = ft_sem_open(SEM_FORK, state->number_of_philosophers);
	state->write = ft_sem_open(SEM_WRITE, 1);
	state->dead = ft_sem_open(SEM_DEAD, 0);
	state->write_m = ft_sem_open(SEM_DEADW, 1);
}

sem_t				*ft_sem_open(char const *name, int value)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

char				*semaphore_namer(char const *base,
char *buffer, int position)
{
	int	i;

	i = ft_strlen(base);
	ft_strcpy(buffer, base);
	while (position > 0)
	{
		buffer[i++] = (position % 10) + '0';
		position /= 10;
	}
	buffer[i] = 0;
	return (buffer);
}
