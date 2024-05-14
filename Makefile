# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 18:00:04 by tchartie          #+#    #+#              #
#    Updated: 2024/05/14 18:01:58 by tchartie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#============ NAME ============#

NAME		=		philo

#========= COMPILATOR =========#

CC			=		clang

#=========== FLAGS ============#

CFLAGS		=		-Wall -Wextra -Werror	#Usual flags
GFLAGS		=		$(CFLAGS) -g			#Flag for gdb or valgrind

#=========== COLOR ============#

BASE_COLOR 	=		\033[0;39m
GRAY 		=		\033[0;90m
RED 		=		\033[0;91m
GREEN 		=		\033[0;92m
YELLOW 		=		\033[0;93m
BLUE 		=		\033[0;94m
MAGENTA		=		\033[0;95m
CYAN 		=		\033[0;96m
WHITE		=		\033[0;97m

#========== SOURCES ===========#

INCLUDE_DIR	=		include
INCLUDE		=		$(INCLUDE_DIR)/philosophers.h

SRCS_DIR	=		src/
OBJS_DIR	=		obj/

SRCS		=		main.c \
					parsing.c \
					parsing_utils.c \
					data_init.c \
					handle_mutex.c \
					error_check.c

OBJS		=		$(SRCS:.c=.o)

SRCS_F		=		$(addprefix $(SRCS_DIR),$(SRCS))

OBJS_F		=		$(addprefix $(OBJS_DIR),$(OBJS))

#========= EXECUTABLE =========#

all :				$(NAME)

$(NAME) :			$(OBJS_F)
					@$(CC) $(OBJS_F) -o $(NAME) -I$(INCLUDE_DIR)
					@echo "$(GREEN)Philosophers successfully compiled! $(BASE_COLOR)"

$(OBJS_DIR)%.o :	$(SRCS_DIR)%.c $(INCLUDE)
					@mkdir -p $(OBJS_DIR)
					@echo "$(YELLOW)Compiling: $< $(BASE_COLOR)"
					@$(CC) $(GFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean :
					@rm -rf $(OBJS_DIR)
					@echo "$(BLUE)Philosophers objects files cleanned! $(BASE_COLOR)"

fclean :
					@rm -rf $(OBJS_DIR)
					@echo "$(BLUE)Philosophers objects files cleanned! $(BASE_COLOR)"
					@rm -rf $(NAME)
					@echo "$(CYAN)Philosophers executable file cleanned! $(BASE_COLOR)"

re :				fclean all

.PHONY :			all makelibft clean fclean re
