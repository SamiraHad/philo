# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsamira <hsamira@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/31 15:22:41 by hsamira           #+#    #+#              #
#    Updated: 2025/07/03 16:49:13 by hsamira          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = philo

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g

# Mode optionnel de compilation
MODE = none
ifeq ($(MODE), pretty)
	CFLAGS += -D DEBUG_FORMATTING=1
endif
ifeq ($(MODE), debug)
	CFLAGS += -D DEBUG_FORMATTING=1 -fsanitize=thread -g
endif

# Fichiers source et objets (tout est dans le dossier courant)
SRC = philo.c utils.c init.c monitor.c routine.c threads.c
OBJ = $(SRC:.c=.o)

# Règles de compilation

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
