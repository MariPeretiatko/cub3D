/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperetia <mperetia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:49:33 by mperetia          #+#    #+#             */
/*   Updated: 2024/07/27 14:39:29 by mperetia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int ac, char *av[])
{
	printf("bonus\n");
	if (ac != 2)
		error_exit("Problems with arguments");
	if (!check_map_name(av[1]))
		error_exit("Can't open file. The format is not supported!");
	init_game(check_init_map(av[1]));
	return (0);
}
