# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaud <albaud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 10:47:51 by albaud            #+#    #+#              #
#    Updated: 2023/01/26 15:02:26 by albaud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
FILES	= global/execute.c global/file.c global/main.c global/pipi.c injection/fd_fd_injection.c injection/fd_injection.c 
OBJS 	= ${FILES:.c=.o}
LIB		= koflibc/libft.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
SAN		= 

.c.o 	:
		${CC} -g ${CFLAGS} -c $< -o ${<:.c=.o}
		

all: ${NAME}

${NAME}: ${OBJS}
		gcc -g -Wall -Werror -Wextra ${SAN} ${OBJS} ${LIB} -o ${NAME} -lreadline

c:
	find *.c */*.c | tr '\n' ' '

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

run: all
	./minishell