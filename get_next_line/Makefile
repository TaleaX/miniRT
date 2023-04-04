# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dns <dns@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/10 23:35:44 by dantonik          #+#    #+#              #
#    Updated: 2023/03/30 16:14:53 by dns              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror
NAME	= 	gnl.a
SRC		= 	get_next_line.c get_next_line_utils.c
OBJ		= 	$(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) -c $(FLAGS) $^ -o $@

$(NAME): $(OBJ)
	@ar -rc $@ $^

clean:
	@rm -fr $(OBJ)

fclean: clean
	@rm -fr $(NAME)

re: fclean all
