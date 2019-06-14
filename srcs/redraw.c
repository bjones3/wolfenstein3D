/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjones <BJones033@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 01:12:52 by bjones            #+#    #+#             */
/*   Updated: 2017/10/18 19:05:13 by bjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		tex_calc(t_mlx *data, t_ray *r)
{
	double wall_x;

	if (r->side == 0)
		wall_x = data->v.pos_y + r->perp_wall_dist * r->raydir_y;
	else
		wall_x = data->v.pos_x + r->perp_wall_dist * r->raydir_x;
	wall_x -= floor((wall_x));
	r->tex_x = (int)(wall_x * (double)(TEX_WIDTH));
	if (r->side == 0 && r->raydir_x > 0)
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
	if (r->side == 1 && r->raydir_y < 0)
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
}

static void	ceiling_floor(t_ray *r, t_image *buf, int x)
{
	int y;

	y = -1;
	while (++y < r->draw_start)
		*(unsigned int *)(buf->image_data + (SCREEN_WIDTH *
			y + x) * (buf->bpp / 8)) = 0x80DCFF;
	y = SCREEN_HEIGHT;
	while (--y >= r->draw_end)
		*(unsigned int *)(buf->image_data + (SCREEN_WIDTH *
			y + x) * (buf->bpp / 8)) = 0x464645;
}

void		buf_calc(t_mlx *data, t_ray *r, t_image *buf, int x)
{
	int tex_num;
	int d;
	int tex_y;
	int color;

	ceiling_floor(r, buf, x);
	tex_num = data->map[r->map_x][r->map_y] - 1;
	while (r->draw_start < r->draw_end)
	{
		d = r->draw_start * 256 - SCREEN_HEIGHT * 128 + r->line_height * 128;
		tex_y = ((d * TEX_HEIGHT) / r->line_height) / 256;
		color = *(unsigned int *)(data->tex[tex_num].image_data +
			(TEX_HEIGHT * tex_y + r->tex_x) * (data->tex[tex_num].bpp / 8));
		if (r->side == 1)
			color = (color >> 1) & 8355711;
		*(unsigned int *)(buf->image_data + (SCREEN_WIDTH *
			r->draw_start + x) * (buf->bpp / 8)) = color;
		r->draw_start++;
	}
}

void		redraw(t_mlx *data)
{
	t_image	buf;
	t_ray	r;
	int		x;

	buf.image = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	buf.image_data = mlx_get_data_addr(buf.image, &buf.bpp,
		&buf.size_line, &buf.endian);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_calc(data, &r, x);
		dist_calc(data, &r);
		dda_calc(data, &r);
		line_calc(data, &r);
		tex_calc(data, &r);
		buf_calc(data, &r, &buf, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, buf.image, 0, 0);
	mlx_destroy_image(data->mlx, buf.image);
	frame_timer(data);
}
