# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydemange <ydemange@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/24 17:41:30 by ydemange          #+#    #+#              #
#    Updated: 2021/09/24 17:41:34 by ydemange         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREY    = \033[030m
RED     = \033[031m
GREEN   = \033[032m
YELLOW  = \033[033m
BLUE    = \033[034m
MAGENTA = \033[035m
CYAN	= \033[036m
RESET   = \033[0m

# ############################################################################ #

CC = gcc

FL_OPTI = -O2
#-O3 -flto
FLAGS = -Wall -Wextra -Werror -Wconversion -Wunused -Wuninitialized $(FL_OPTI)
LFLAGS = $(FLAGS)
CFLAGS = -c $(FLAGS)

SDL_DIR = frameworks
FRAMEWORKS = -F $(SDL_DIR) -framework SDL2 -Wl,-rpath $(SDL_DIR) -framework OpenGL

CINCLUDE = -I include -I frameworks/SDL2.framework/headers \

# ############################################################################ #

NAME = scop

HEADERS = \
include/scop.h		\

SRC_FILES = 	\
init.c		\
main.c		\
main_loop.c		\
shader.c		\
utils.c		\
parser.c		\
matrix.c		\

# ############################################################################ #

SRC_DIR = src/
SRC := $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))
OBJ_DIR = obj/
OBJ := $(addprefix $(OBJ_DIR), $(OBJ_FILES))

# ft library
FT		= ./libft/
FT_LNK	= -L ./libft -l ft -l pthread
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft

all: $(FT_LIB) $(NAME) 
	@echo "$(CYAN)$(NAME) ready !$(RESET)"

$(NAME): $(OBJ_DIR) $(OBJ) 
	@echo "$(GREEN)objects done !$(RESET)"
	@$(CC) $(FT_LNK) $(FRAMEWORKS) $(LFLAGS) -o $(NAME) $(OBJ)
	@echo "$(GREEN)$(NAME) compiled !$(RESET)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADERS)
	@$(CC) $(CINCLUDE) $(FT_INC) $(CFLAGS) -o $@ $<
	@echo -n '.'

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)
	@echo "$(GREEN)Object directory created!$(RESET)"

$(FT_LIB):
	@make -C $(FT)

clean:
	make -C $(FT) clean
	@rm -f $(OBJ)
	@echo "$(RED)Objects deleted $(RESET)"
	@rm -rf $(OBJ_DIR)
	@#echo "$(RED)Object directory $(RESET)"

fclean: clean
	make -C $(FT) fclean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) deleted $(RESET)"

re: fclean all
