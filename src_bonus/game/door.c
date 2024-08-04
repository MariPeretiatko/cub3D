/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:59:11 by mperetia          #+#    #+#             */
/*   Updated: 2024/08/04 19:05:59 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

double	calculate_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	toggle_door(t_game *game, int x, int y)
{
	double distance = calculate_distance(game->player.pos_x, game->player.pos_y, x, y);

    // printf("Attempt to toggle door at (%d, %d) with distance %f\n", x, y, distance);

    if (distance < 1.5) // Проверка расстояния
    {
        game->door_x = x;
        game->door_y = y;

        if (game->map->map[x][y] == 'D')
        {
            game->door_open = 1;
            // printf("Door at (%d, %d) set to open\n", x, y);
        }
        else if (game->map->map[x][y] == 'O')
        {
            game->door_open = 0;
            // printf("Door at (%d, %d) set to close\n", x, y);
        }
    }
    else
    {
        // printf("Door at (%d, %d) is too far to toggle\n", x, y);
    }
	//  double distance = calculate_distance(game->player.pos_x, game->player.pos_y, x, y);

    // if (distance < 2) // Проверка расстояния
    // {
    //     game->door_x = x;
    //     game->door_y = y;

    //     if (game->map->map[x][y] == 'D')
    //     {
    //         game->door_open = 1;
    //     }
    //     else if (game->map->map[x][y] == 'O')
    //     {
    //         game->door_open = 0;
    //     }
    // }
	// double distance = calculate_distance(game->player.pos_x, game->player.pos_y, x, y);

    // if (distance < 3) // Проверка расстояния
    // {
    //     game->door_x = x;
    //     game->door_y = y;

    //     if (game->map->map[x][y] == 'D')
    //     {
    //         game->door_open = 1;
    //         game->map->map[x][y] = 'O'; // Открытие двери
    //     }
    //     else if (game->map->map[x][y] == 'O')
    //     {
    //         game->door_open = 0;
    //         game->map->map[x][y] = 'D'; // Закрытие двери
    //     }
    // }
	
	// double distance = calculate_distance(game->player.pos_x, game->player.pos_y, x, y);

    // if (distance < 1.5) // Проверка расстояния
    // {
    //     if (game->map->map[x][y] == 'D')
    //     {
    //         game->door_open = 1;
    //         game->door_x = x;
    //         game->door_y = y;
    //         game->map->map[x][y] = 'O'; // Открытие двери
    //     }
    //     else if (game->map->map[x][y] == 'O')
    //     {
    //         game->door_open = 0;
    //         game->door_x = x;
    //         game->door_y = y;
    //         game->map->map[x][y] = 'D'; // Закрытие двери
    //     }
    // }
}

void	print_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map->map[i])
	{
		printf("%s\n", game->map->map[i]);
		i++;
	}
}

void	update_door_animation(t_game *game)
{
	 int door_x = game->door_x;
    int door_y = game->door_y;

    if (game->door_open)
    {
        if (game->door_offset < TEXWIDTH)
        {
            game->door_offset += DOOR_SPEED;
            if (game->door_offset > TEXWIDTH)
                game->door_offset = TEXWIDTH;
        }
        if (game->door_offset == TEXWIDTH && game->map->map[door_x][door_y] == 'D')
        {
            game->map->map[door_x][door_y] = 'O'; // Состояние "открыто"
            printf("Door at (%d, %d) opened\n", door_x, door_y);
            printf("game->door_offset = %f\n", game->door_offset);

        }
    }
    else
    {
        if (game->door_offset > 0)
        {
            game->door_offset -= DOOR_SPEED;
            if (game->door_offset < 0)
                game->door_offset = 0;
        }
        if (game->door_offset == 0 && game->map->map[door_x][door_y] == 'O')
        {
            game->map->map[door_x][door_y] = 'D'; // Состояние "закрыто"
            printf("Door at (%d, %d) closed\n", door_x, door_y);
            printf("game->door_offset = %f\n", game->door_offset);

        }
    }

    // Отладочная информация
    // printf("Door animation update: offset = %f, state = %c\n", game->door_offset, game->map->map[door_x][door_y]);

	//  int door_x = game->door_x;
    // int door_y = game->door_y;

    // if (game->door_open)
    // {
    //     if (game->door_offset < TEXWIDTH)
    //     {
    //         game->door_offset += DOOR_SPEED;
    //         if (game->door_offset > TEXWIDTH)
    //             game->door_offset = TEXWIDTH;
    //     }
    //     if (game->door_offset == TEXWIDTH && game->map->map[door_x][door_y] == 'D')
    //     {
    //         game->map->map[door_x][door_y] = 'O'; // Состояние "открыто"
    //     }
    // }
    // else
    // {
    //     if (game->door_offset > 0)
    //     {
    //         game->door_offset -= DOOR_SPEED;
    //         if (game->door_offset < 0)
    //             game->door_offset = 0;
    //     }
    //     if (game->door_offset == 0 && game->map->map[door_x][door_y] == 'O')
    //     {
    //         game->map->map[door_x][door_y] = 'D'; // Состояние "закрыто"
    //     }
    // }
	
	// if (game->door_open)
    // {
    //     if (game->door_offset < TEXWIDTH)
    //     {
    //         game->door_offset += DOOR_SPEED;
    //         if (game->door_offset > TEXWIDTH)
    //             game->door_offset = TEXWIDTH;
    //     }
    // }
    // else
    // {
    //     if (game->door_offset > 0)
    //     {
    //         game->door_offset -= DOOR_SPEED;
    //         if (game->door_offset < 0)
    //             game->door_offset = 0;
    //     }
    // }

    // // Обновление состояния двери на карте
    // int door_x = game->door_x;
    // int door_y = game->door_y;
    // if (game->door_offset == TEXWIDTH && game->map->map[door_x][door_y] == 'D')
    // {
    //     game->map->map[door_x][door_y] = 'O';
    // }
    // else if (game->door_offset == 0 && game->map->map[door_x][door_y] == 'O')
    // {
    //     game->map->map[door_x][door_y] = 'D';
    // }

	
	// if (game->door_open)
    // {
    //     if (game->door_offset < TEXWIDTH)
    //     {
    //         game->door_offset += DOOR_SPEED;
    //         if (game->door_offset >= TEXWIDTH)
    //         {
    //             game->door_offset = TEXWIDTH;
    //             // Нет необходимости обновлять карту здесь
    //         }
    //     }
    // }
    // else
    // {
    //     if (game->door_offset > 0)
    //     {
    //         game->door_offset -= DOOR_SPEED;
    //         if (game->door_offset <= 0)
    //         {
    //             game->door_offset = 0;
    //             // Нет необходимости обновлять карту здесь
    //         }
    //     }
    // }
}

void render_door_open(t_game *game, int x, int y)
{
	int				texture_x;
	int				texture_y;
	unsigned int	color;

 texture_x = (int)(game->rc.wall_x * TEXWIDTH);
    texture_y = (int)game->rc.tex_pos & (TEXHEIGHT - 1);
	// texture_y = (int)game->rc.tex_pos & (TEXHEIGHT - 1);
	// game->rc.tex_pos += game->rc.step;
	// // Учет смещения двери
	// if (game->rc.side == 0)
	// 	game->rc.wall_x = game->player.pos_y + game->rc.perp_wall_dist
	// 		* game->rc.raydir_y;
	// else
	// 	game->rc.wall_x = game->player.pos_x + game->rc.perp_wall_dist
	// 		* game->rc.raydir_x;
	// game->rc.wall_x -= floor(game->rc.wall_x);
	// texture_x = (int)(game->rc.wall_x * (double)TEXWIDTH);
	// if (game->rc.side == 0 && game->rc.raydir_x > 0)
	// 	texture_x = TEXWIDTH - texture_x - 1;
	// if (game->rc.side == 1 && game->rc.raydir_y < 0)
	// 	texture_x = TEXWIDTH - texture_x - 1;
	// // Применение смещения двери
	// texture_x = texture_x + game->door_offset;
	// if (texture_x >= TEXWIDTH)
	// 	texture_x = TEXWIDTH - 1;
	color = get_texture_pixel(game->open_door, texture_x, texture_y);
	if (color != WHITE)
	// Учитываем прозрачный цвет (если черный цвет считается прозрачным)
	{
		my_mlx_pixel_put(game->back, x, y, color);
		// color = get_texture_pixel(get_texture_directions(game), x, y);
	}
}
void	render_door(t_game *game, int x, int y)
{
    int texture_x;
    int texture_y;
    int color;

    // Рассчитываем координаты текстуры с учетом смещения двери
    texture_x = (int)(game->rc.wall_x * TEXWIDTH) - game->door_offset;
    if (texture_x < 0)
        texture_x += TEXWIDTH;
    texture_y = (int)game->rc.tex_pos & (TEXHEIGHT - 1);

    // Получаем цвет пикселя из текстуры двери
    color = get_texture_pixel(game->door, texture_x, texture_y);

    // Отладочная информация
    // printf("Render door at (%d, %d) with texture coordinates (%d, %d) and color %X\n", x, y, texture_x, texture_y, color);

    // Проверка прозрачности цвета
    // Важно проверить, что цвет не является прозрачным (например, цвет ключевого цвета)
    if (color != 0x00000000) {
        my_mlx_pixel_put(game->back, x, y, color);
    }
    
	// int texture_x;
    // int texture_y;
    // int color;

    // // Рассчитываем координаты текстуры с учетом смещения двери
    // texture_x = (int)(game->rc.wall_x * TEXWIDTH) - game->door_offset;
    // if (texture_x < 0)
    //     texture_x += TEXWIDTH;
    // texture_y = (int)game->rc.tex_pos & (TEXHEIGHT - 1);

    // color = get_texture_pixel(game->door, texture_x, texture_y);

    // // Отладочная информация
    // // printf("Render door at (%d, %d) with texture coordinates (%d, %d) and color %X\n", x, y, texture_x, texture_y, color);

    // // Проверка прозрачности цвета
    //     my_mlx_pixel_put(game->back, x, y, color);
    // if ((color & 0x00FFFFFF) != 0)
    // {
    // }
    // else
    // {
        // printf("Transparent pixel at (%d, %d)\n", x, y);
    // }
	
	// int texture_x;
    // int texture_y;
    // int color;

    // // Рассчитываем координаты текстуры с учетом смещения двери
    // texture_x = (int)(game->rc.wall_x * TEXWIDTH) - game->door_offset;
    // if (texture_x < 0)
    //     texture_x += TEXWIDTH;
    // texture_y = (int)game->rc.tex_pos & (TEXHEIGHT - 1);

    // color = get_texture_pixel(game->door, texture_x, texture_y);
    
    // // Проверка прозрачности цвета
    // if ((color & 0x00FFFFFF) != 0)
    // {
    //     my_mlx_pixel_put(game->back, x, y, color);
    // }
	//not normal
	//  int texture_x;
    // int texture_y;
    // int color;

    // if (game->map->map[game->rc.map_x][game->rc.map_y] == 'D' || game->map->map[game->rc.map_x][game->rc.map_y] == 'O')
    // {
    //     texture_x = (int)(game->rc.wall_x * TEXWIDTH) - game->door_offset;
    //     if (texture_x < 0)
    //         texture_x += TEXWIDTH;

    //     texture_y = (int)game->rc.tex_pos & (TEXHEIGHT - 1);
    //     color = get_texture_pixel(game->door, texture_x, texture_y);

    //     if (game->rc.tex_x >= game->door_offset)
    //     {
    //         my_mlx_pixel_put(game->back, x, y, color);
    //     }
    // }

	
	// (void)x;
	// (void)y;
	// int texture_x;
    // int texture_y;
    // int color;

    // texture_x = (int)(game->rc.wall_x * TEXWIDTH);
    // texture_y = (int)game->rc.tex_pos & (TEXHEIGHT - 1);
    // game->rc.tex_pos += game->rc.step;

    // if (game->map->map[game->rc.map_x][game->rc.map_y] == 'O')
    // {
    //     // Открытая дверь - отображение заднего фона
    //     color = get_texture_pixel(game->back, texture_x, texture_y);
    // }
    // else
    // {
    //     // Закрытая дверь
    //     color = get_texture_pixel(game->door, texture_x, texture_y);
    // }

}
