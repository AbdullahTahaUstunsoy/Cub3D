/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falakus <falakus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:49:03 by austunso          #+#    #+#             */
/*   Updated: 2025/11/01 16:31:36 by falakus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	raycast(t_ray *ray, t_player *player, t_game *game)
{
	int	column;

	column = 0;
	while (column < SCREEN_WIDTH)
	{
		init_rays(ray, player, column);
		step_and_side_dist(ray, player);
		perform_dda(ray, game->map);
		calculate_wall_distance(ray);
		height_of_line_to_draw(ray);
		draw_pixels(ray, column, game, player);
		column++;
	}
}

void	render(t_game *game)
{
	raycast(game->ray, game->player, game);
	mlx_put_image_to_window(game->mlx_content.mlx,
		game->mlx_content.win, game->img.img, 0, 0);
}

int	game_loop(t_game *game)
{
	move(game);
	render(game);
	return (0);
}
