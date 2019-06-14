/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjones <BJones033@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 18:41:15 by bjones            #+#    #+#             */
/*   Updated: 2017/10/18 18:42:03 by bjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	init_calc(t_mlx *data, t_ray *r, int x)
{
	r->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	r->raydir_x = data->v.dir_x + data->v.plane_x * r->camera_x;
	r->raydir_y = data->v.dir_y + data->v.plane_y * r->camera_x;
	r->map_x = (int)data->v.pos_x;
	r->map_y = (int)data->v.pos_y;
}

void	dist_calc(t_mlx *data, t_ray *r)
{
	r->deltadist_x = sqrt(1 + (r->raydir_y * r->raydir_y)
		/ (r->raydir_x * r->raydir_x));
	r->deltadist_y = sqrt(1 + (r->raydir_x * r->raydir_x)
		/ (r->raydir_y * r->raydir_y));
	if (r->raydir_x < 0)
	{
		r->step_x = -1;
		r->sidedist_x = (data->v.pos_x - r->map_x) * r->deltadist_x;
	}
	else
	{
		r->step_x = 1;
		r->sidedist_x = (r->map_x + 1.0 - data->v.pos_x) * r->deltadist_x;
	}
	if (r->raydir_y < 0)
	{
		r->step_y = -1;
		r->sidedist_y = (data->v.pos_y - r->map_y) * r->deltadist_y;
	}
	else
	{
		r->step_y = 1;
		r->sidedist_y = (r->map_y + 1.0 - data->v.pos_y) * r->deltadist_y;
	}
}

void	dda_calc(t_mlx *data, t_ray *r)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (r->sidedist_x < r->sidedist_y)
		{
			r->sidedist_x += r->deltadist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->sidedist_y += r->deltadist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (data->map[r->map_x][r->map_y] > 0)
			hit = 1;
	}
}

void	line_calc(t_mlx *data, t_ray *r)
{
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - data->v.pos_x
			+ (1 - r->step_x) / 2) / r->raydir_x;
	else
		r->perp_wall_dist = (r->map_y - data->v.pos_y
			+ (1 - r->step_y) / 2) / r->raydir_y;
	r->line_height = (int)(SCREEN_HEIGHT / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + SCREEN_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + SCREEN_HEIGHT / 2;
	if (r->draw_end >= SCREEN_HEIGHT)
		r->draw_end = SCREEN_HEIGHT - 1;
}
