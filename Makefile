# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpasqual <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 19:36:40 by tpasqual          #+#    #+#              #
#    Updated: 2016/12/23 13:53:27 by tpasqual         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
SRC = ./src
INC = ./includes
OBJ = .
LIST_SRC = $(SRC)/main.c $(SRC)/file_checking.c $(SRC)/insert_part.c\
		   $(SRC)/linked_list.c $(SRC)/process_grid.c

LIST_OBJ = $(LIST_SRC:$(SRC)/%.c=$(OBJ)/%.o)

LIBFT = libft.a
LIBFTPATH = ./libft/
INC_LIBFTPATH  = $(LIBFTPATH)

all: $(NAME)

$(NAME): $(LIST_SRC)
	make -C $(LIBFTPATH)
	gcc $(CFLAG) -I $(INC) -I $(INC_LIBFTPATH) $(LIST_SRC) -L$(LIBFTPATH) -lft -o $(NAME)

clean:
	make clean -C $(LIBFTPATH)
	rm -f  $(LIST_OBJ)

fclean: clean
	make fclean -C $(LIBFTPATH)
	rm -f $(NAME)

re: fclean all
