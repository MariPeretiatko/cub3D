GREEN = \033[0;32m
RESET = \033[0m

NAME		= 	cub3D

CC				=	cc
CC_FLAGS		=	-Wall -Wextra -Werror -g #-fsanitize=address

MLX = minilibx_linux/
MLX_FLAGS = -I -g3 -L /usr/X11/lib -Lincludes -L./mlx -lmlx -Imlx -lXext -lX11 -lz
LIBFT_F = inc/libft/
LIBFLAGS = -L$(LIBFT_F) -lft -I$(LIBFT_F) -I$(LIBFT_F)/src/ft_printf/ -I$(LIBFT_F)/src/get_next_line/

SRCS		=	main.c split.c\
				error.c\
				free.c\
				list.c\
				sub_file.c\
				utils.c\
				utils_map.c\
				valid_map.c\

#SRCS_BONUS		=	main.c map_render.c \
#				image_render.c map_check.c utils.c \
#				map_create.c utils2.c raycast.c mouse.c \
#				file_render.c key_movement.c sprite_render.c\
#				key_rotation.c minimap.c key_movement2.c \
#				raycast_utils.c raycast_bonus.c sprite_utils.c \
#				map_check_utils.c map_check_utils2.c sky_bonus.c\
#				utils3.c\


#SCRS_FBONUS		= src_bonus/
#OBJS_FBONUS		= obj_bonus/


OBJS		=	$(SRCS:%.c=%.o)
#OBJS_BONUS	=	$(SRCS_BONUS:.c=.o)
OBJS_P		=	$(addprefix $(OBJS_F), $(OBJS))
#OBJS_PBONUS	=	$(addprefix $(OBJS_FBONUS), $(OBJS_BONUS))
#NAME_BONUS	=	cub3D_bonus

VPATH = $(SRCS_F) $(SRCS_F)parsing/
SRCS_F			= src/
OBJS_F			= obj/

all:$(NAME)

$(OBJS_F)%.o: %.c Makefile inc/cub3d.h
	@mkdir -p $(OBJS_F)
	@echo "Working on: $<"
	@$(CC) $(CC_FLAGS) -O3 -c $< -o $@

$(NAME): $(OBJS_P) $(LIBFT_F)
	@$(MAKE) -C $(MLX)
	$(MAKE) -C $(LIBFT_F)
	@$(CC) -O3 -o $(NAME) $(OBJS_P) $(CC_FLAGS) $(LIBFLAGS) -L$(MLX) $(MLX_FLAGS) -lm
	@echo "\n$(GREEN)\n—————————————✣ CUB3D COMPILED ✣—————————————\n$(RESET)"

#bonus: $(NAME_BONUS)
#
#$(OBJS_FBONUS)%.o: $(SCRS_FBONUS)%.c Makefile cub3d_bonus.h
#	@mkdir -p $(OBJS_FBONUS)
#	@echo "Working on: $<"
#	@$(CC) $(CC_FLAGS) -O3 -c $< -o $@
#
#$(NAME_BONUS): $(OBJS_PBONUS)
#	@$(MAKE) -C $(MLX)
#	@$(MAKE) -C $(LIBFT)
#	@$(CC) $(CC_FLAGS) -O3 -o $(NAME_BONUS) $(OBJS_PBONUS) -L$(MLX) $(MLX_FLAGS) $(LIBFT)/libft.a -lm
#	@echo "OK"

clean:
	@rm -rf $(OBJS_F)
	@$(MAKE) -C $(MLX) clean

fclean:	clean
	@$(MAKE) -C $(LIBFT_F) fclean
	@rm -rf $(NAME)

re:		fclean all

.PHONY:	all clean fclean re