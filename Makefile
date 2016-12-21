# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpasqual <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 19:36:40 by tpasqual          #+#    #+#              #
#    Updated: 2016/12/21 12:05:30 by tpasqual         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

SRC_PATH = ./src/
SRC_NAME = 	main.c\
			file_checking.c\
			insert_part.c\
			linked_list.c\
			process_grid.c

OBJ = $(SRC_NAME:.c=.o)

INC_NAME = fillit.h

NAME = fillit

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
INC = $(addprefix $(INC_PATH),$(INC_NAME))

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) -c $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -L$(SRC_PATH) -lft -o $(NAME)
	@echo "Compilation success"

clean:
	@rm -rf $(OBJ)
	@echo "Delete .o"

fclean: clean
	@rm -rf $(NAME)
	@echo "Delete fillit"

re: fclean all

