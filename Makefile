# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlarue <jlarue@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/15 15:02:31 by jlarue            #+#    #+#              #
#    Updated: 2023/06/15 15:02:41 by jlarue           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo
CC				= cc -pthread
FLAG			= -Wall -Wextra -Werror
SRC_DIR			= ./sources/
INC_DIR			= ./includes/
SRC				= $(addprefix $(SRC_DIR),$(C_FILE))
OBJ				= $(SRC:.c=.o)
C_FILE			=  main.c\
				   init.c\
				   error_manager.c\
				   game.c\
				   utils.c\
				   ft_utils2.c\
				   libft_usage.c\
				   ft_testdeadforks.c\
				   meal_loop_one.c\
				   ft_norminette.c\

.c.o:
	$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAG) $(OBJ) -o $(NAME)

clean:
	@rm -f $(OBJ) $(OBJ_B)

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re
