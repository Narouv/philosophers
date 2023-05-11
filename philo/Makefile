# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 17:59:41 by rnauke            #+#    #+#              #
#    Updated: 2023/05/11 18:07:08 by rnauke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

OBJECTS_DIR = obj
SOURCES_DIR = src

SOURCES = main.c cleanup.c utils.c philo.c
OBJECTS = $(SOURCES:.c=.o)

DIR_SRC = $(addprefix $(SOURCES_DIR)/, $(SOURCES))
DIR_OBJ = $(addprefix $(OBJECTS_DIR)/, $(OBJECTS))

FLAGS = -pthread -Wall -Werror -Wextra
ARGS = $(FLAGS)
all:  $(NAME)

$(NAME): $(MLX42) $(DIR_OBJ) $(LIBFT)
	gcc -o $(NAME) $(DIR_OBJ) $(ARGS) 

$(OBJECTS_DIR)/%.o : $(SOURCES_DIR)/%.c
	mkdir -p $(OBJECTS_DIR)
	gcc -o $@ -c $< $(FLAGS)

clean:
	rm -rf $(OBJECTS_DIR)
	rm -rf $(BONUS_DIR)/$(OBJECTS_DIR)

fclean:
	rm -rf $(OBJECTS_DIR)
	rm -rf $(BONUS_DIR)/$(OBJECTS_DIR)
	rm -f $(NAME)

.PHONY: re fclean clean

re: clean all
