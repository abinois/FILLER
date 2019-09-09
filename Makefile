# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abinois <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/21 11:59:11 by abinois           #+#    #+#              #
#    Updated: 2019/07/23 10:39:46 by abinois          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = abinois.filler
CFLAGS = -Wall -Werror -Wextra
CC = gcc
LIBFTPRINTF = libftprintf/libftprintf.a
LIB = libft/libft.a

SRC = $(addsuffix .c, read filler board parsing)
OBJ = $(SRC:.c=.o)

GREEN = \033[32m
BLUE = \033[34m
RED = \033[31m
YELLOW = \033[33m
BLINK = \033[5m
NOCOLOR = \033[0m

all: $(NAME)

$(NAME): $(OBJ) Makefile includes/filler.h libft/Makefile libft/libft.h \
	$(LIBFTPRINTF) includes/ft_printf.h
	make -C libft
	@echo "$(BLUE)⚡️ COMPILATION . . . . . . . . . . . . .$(YELLOW)"
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(LIBFTPRINTF) -o $(NAME)
	@echo "$(GREEN)TOUT EST ---------------------------> $(BLINK)OK$(NOCOLOR)"

clean:
	make clean -C libft
	@echo "$(BLUE)⚡️ SUPPR DES .O . . . . . . . . . .$(RED)"
	rm -f $(OBJ)
	@echo "$(GREEN)TOUT EST ---------------------------> $(BLINK)OK$(NOCOLOR)"

fclean: clean
	make fclean -C libft
	@echo "$(BLUE)⚡️ SUPPR DU .A . . . . . . . .$(RED)"
	rm -f $(NAME)
	@echo "$(GREEN)TOUT EST ---------------------------> $(BLINK)OK$(NOCOLOR)"

re: fclean all
	@echo "🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫  $(BLUE)ET C'EST REPARTI ! 🔫 🔫 🔫 🔫 🔫 🔫 🔫 🔫 "
	@echo "$(BLUE)⚡️ RELINK . . . . . . . . . . . . . . ."
	@echo "$(GREEN)TOUT EST ---------------------------> $(BLINK)OK$(NOCOLOR)"

.PHONY: all clean fclean re
