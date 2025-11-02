/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:49:38 by austunso          #+#    #+#             */
/*   Updated: 2025/10/26 15:49:38 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return (1);
	game = init_structs();
	if (game == NULL)
		return (1);
	if (map_operations(game, av))
		return (1);
	if (set_game_components(game))
		return (1);
	if (load_textures(game))
		return (1);
	render(game);
	mlx_loop(game->mlx_content.mlx);
	return (0);
}
