#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/27 15:23:08 by vlikhotk          #+#    #+#              #
#    Updated: 2017/11/02 15:15:21 by vlikhotk         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = lem-in

LIB_DIR = ./libft/

SFILES = main.c add_links.c links_parsing.c find_way.c str_processing.c reading.c clear.c \
room_validation.c room_proc.c comments_ants_parsing.c queue.c

OFILES = main.o add_links.o links_parsing.o find_way.o str_processing.o reading.o clear.o \
room_validation.o room_proc.o comments_ants_parsing.o queue.o

LIBFT = $(LIBFT_DIR)libftprintf.a
LIBFT_DIR = $(LIB_DIR)
LIBFT_INC = $(LIBFT_DIR)includes/

CC_FLAGS = -Wall -Wextra -Werror
HEADER_FLAGS = -I $(LIBFT_INC)

CC_FLAGS = -Wall -Wextra -Werror
CC = gcc

all: $(NAME)

$(NAME): $(LIBFT) $(OFILES)
	$(CC) $(OFILES) $(LIBFT) -o $(NAME)

$(OFILES): %.o:%.c
	$(CC) -c $< -o $@ $(CC_FLAGS) $(HEADER_FLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OFILES)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all
