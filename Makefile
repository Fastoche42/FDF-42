# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 17:21:54 by fl-hote           #+#    #+#              #
#    Updated: 2022/11/23 18:03:54 by fl-hote          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf
NAMEB	= fdf_bonus

SRC_PATH	= ./srcs/
OBJ_PATH	= ./objs/

SRC_NAME = fdf_main.c fdf_mlx.c fdf_utils.c fdf_draw.c fdf_matrix.c \
		   fdf_color.c fdf_hooks.c
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC_NAMEB = fdf_main_bonus.c fdf_mlx_bonus.c fdf_utils_bonus.c fdf_draw_bonus.c \
			fdf_matrix_bonus.c fdf_color_bonus.c fdf_hooks_bonus.c
OBJ_NAMEB = $(SRC_NAMEB:.c=.o)

SRC	= $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ	= $(addprefix $(OBJ_PATH),$(OBJ_NAME))

SRCB	= $(addprefix $(SRC_PATH),$(SRC_NAMEB))
OBJB	= $(addprefix $(OBJ_PATH),$(OBJ_NAMEB))

CPPFLAGS= -I./includes/ -I./libft/ -I./MLX42/include/MXL42/
#CFLAGS	= -Wall -Wextra -Werror -Wunreachable-code -Ofast
CFLAGS	= -Wall -Wextra -Werror -Ofast
CC		= gcc

UNAME := $(shell uname -s)
ifeq ($(UNAME), Darwin)
	LDFLAGS	= -lglfw -framework Cocoa -framework OpenGL -framework IOKit -L ~/goinfre/.brew/opt/glfw/lib/
else
	LDFLAGS = -ldl -lglfw -pthread -lm
endif


all: $(NAME)

debug: CFLAGS += -g -fsanitize=address
debug: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft
	@make -C ./MLX42
	$(CC) $(OBJ) -o $@ $(CFLAGS) -L./libft -lft -L./MLX42 -lmlx42 $(LDFLAGS)

bonus: $(OBJB)
	@make -C ./libft
	@make -C ./MLX42
	$(CC) $(OBJB) -o $(NAMEB) $(CFLAGS) -L./libft -lft -L./MLX42 -lmlx42 $(LDFLAGS)
	
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

clean:
	@make -C ./libft clean
	@make -C ./MLX42 clean
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean:
	@make -C ./libft/ fclean
	@make -C ./MLX42 fclean
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	rm -f $(NAME) $(NAMEB)

re: fclean all

.PHONY: all clean fclean re debug
