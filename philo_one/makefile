# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alromero <alromero@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/16 17:49:06 by alromero          #+#    #+#              #
#    Updated: 2020/04/09 16:30:59 by alromero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c utils.c eat.c do_things.c

OBJS			= $(SRC:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Werror -Wextra -I.
LIBS			= -lpthread

NAME			= philo_one

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -o ${NAME} ${OBJS} ${LIBS}

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)
