GREEN = \033[0;32m
RESET = \033[0m

NAME        = cub3D
NAME_BONUS  = cub3D_bonus

CC          = cc
CC_FLAGS    = -Wall -Wextra -Werror -g #-fsanitize=address

MLX = minilibx_linux/
MLX_FLAGS = -I -g3 -L /usr/X11/lib -Lincludes -L./mlx -lmlx -Imlx -lXext -lX11 -lz
LIBFT_F = inc/libft/
LIBFLAGS = -L$(LIBFT_F) -lft -I$(LIBFT_F) -I$(LIBFT_F)/src/ft_printf/ -I$(LIBFT_F)/src/get_next_line/

SRCS_F      = src/
OBJS_F      = obj/

SCRS_FBONUS = src_bonus/
OBJS_FBONUS = obj_bonus/

SRCS        = main.c error.c free.c \
              $(SRCS_F)parsing/list.c \
              $(SRCS_F)parsing/utils.c \
              $(SRCS_F)parsing/valid_map.c \
              $(SRCS_F)parsing/valid_symbols.c \
              $(SRCS_F)parsing/init_map.c \
              $(SRCS_F)parsing/check_map.c \
              $(SRCS_F)raycast/raycast.c \
              $(SRCS_F)raycast/render.c \
              $(SRCS_F)raycast/utils_raycast.c \
              $(SRCS_F)game/init_game.c \
              $(SRCS_F)game/input_game.c \
              $(SRCS_F)game/movement_game.c \
              $(SRCS_F)game/rotate_game.c \
              $(SRCS_F)game/init_walls.c

SRCS_BONUS = main.c error.c free.c \
              $(SCRS_FBONUS)parsing/list.c \
              $(SCRS_FBONUS)parsing/utils.c \
              $(SCRS_FBONUS)parsing/valid_map.c \
              $(SCRS_FBONUS)parsing/valid_symbols.c \
              $(SCRS_FBONUS)parsing/init_map.c \
              $(SCRS_FBONUS)parsing/check_map.c \
              $(SCRS_FBONUS)raycast/raycast.c \
              $(SCRS_FBONUS)raycast/render.c \
              $(SCRS_FBONUS)raycast/utils_raycast.c \
              $(SCRS_FBONUS)game/init_game.c \
              $(SCRS_FBONUS)game/input_game.c \
              $(SCRS_FBONUS)game/movement_game.c \
              $(SCRS_FBONUS)game/rotate_game.c \
              $(SCRS_FBONUS)game/init_walls.c \
              $(SCRS_FBONUS)game/input_mouse.c \
              $(SCRS_FBONUS)game/gun.c \
               

OBJS        = $(SRCS:%.c=%.o)
OBJS_BONUS  = $(SRCS_BONUS:%.c=%.o)

OBJS_P      = $(addprefix $(OBJS_F), $(OBJS))
OBJS_PBONUS = $(addprefix $(OBJS_FBONUS), $(OBJS_BONUS))

VPATH = $(SRCS_F) $(SRCS_F)parsing/ $(SRCS_F)raycast/ $(SRCS_F)game/
VPATH_BONUS = $(SCRS_FBONUS) $(SCRS_FBONUS)parsing/ $(SCRS_FBONUS)raycast/ $(SCRS_FBONUS)game/

all: $(NAME)

$(OBJS_F)%.o: %.c Makefile inc/cub3d.h
	@mkdir -p $(dir $@)
	@echo "Working on: $<"
	@$(CC) $(CC_FLAGS) -O3 -c $< -o $@

$(NAME): $(OBJS_P) $(LIBFT_F)
	@$(MAKE) -C $(MLX)
	$(MAKE) -C $(LIBFT_F)
	@$(CC) -O3 -o $(NAME) $(OBJS_P) $(CC_FLAGS) $(LIBFLAGS) -L$(MLX) $(MLX_FLAGS) -lm
	@echo "\n$(GREEN)\n—————————————✣ CUB3D COMPILED ✣—————————————\n$(RESET)"

bonus: $(NAME_BONUS)

$(OBJS_FBONUS)%.o: %.c Makefile inc/cub3d.h
	@mkdir -p $(dir $@)
	@echo "Compiling: $<"
	@$(CC) $(CC_FLAGS) -O3 -c $< -o $@

$(NAME_BONUS): $(OBJS_PBONUS) $(LIBFT_F)
	@$(MAKE) -C $(MLX)
	$(MAKE) -C $(LIBFT_F)
	@$(CC) -O3 -o $(NAME_BONUS) $(OBJS_PBONUS) $(CC_FLAGS) $(LIBFLAGS) -L$(MLX) $(MLX_FLAGS) -lm
	@echo "\n$(GREEN)\n—————————————✣ CUB3D BONUS COMPILED ✣—————————————\n$(RESET)"

clean:
	@rm -rf $(OBJS_F)
	@rm -rf $(OBJS_FBONUS)
	@$(MAKE) -C $(MLX) clean

fclean: clean
	@$(MAKE) -C $(LIBFT_F) fclean
	@rm -rf $(NAME)
	@rm -rf $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re
