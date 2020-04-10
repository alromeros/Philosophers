# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alromero <alromero@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/07 17:00:33 by alromero          #+#    #+#              #
#    Updated: 2020/04/09 16:34:10 by alromero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c utils.c eat.c do_things.c semaphores.c

OBJS			= $(SRC:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Werror -Wextra -I.
LIBS			= -lpthread

NAME			= philo_two

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -o ${NAME} ${OBJS} ${LIBS}

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)
