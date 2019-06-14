/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjones <BJones033@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 01:26:58 by bjones            #+#    #+#             */
/*   Updated: 2017/10/18 01:28:52 by bjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void	rotation_hooks(t_mlx *e)
{
	double olddir_x;
	double oldplane_x;
	double rs;

	rs = e->timer.rot_speed;
	if (e->keys.left)
	{
		olddir_x = e->v.dir_x;
		e->v.dir_x = e->v.dir_x * cos(rs) - e->v.dir_y * sin(rs);
		e->v.dir_y = olddir_x * sin(rs) + e->v.dir_y * cos(rs);
		oldplane_x = e->v.plane_x;
		e->v.plane_x = e->v.plane_x * cos(rs) - e->v.plane_y * sin(rs);
		e->v.plane_y = oldplane_x * sin(rs) + e->v.plane_y * cos(rs);
	}
	if (e->keys.right)
	{
		olddir_x = e->v.dir_x;
		e->v.dir_x = e->v.dir_x * cos(-rs) - e->v.dir_y * sin(-rs);
		e->v.dir_y = olddir_x * sin(-rs) + e->v.dir_y * cos(-rs);
		oldplane_x = e->v.plane_x;
		e->v.plane_x = e->v.plane_x * cos(-rs) - e->v.plane_y * sin(-rs);
		e->v.plane_y = oldplane_x * sin(-rs) + e->v.plane_y * cos(-rs);
	}
}

static void	strafe_hooks(t_mlx *e)
{
	double ms;

	ms = e->timer.move_speed;
	if (e->keys.a)
	{
		if (!e->map[(int)(e->v.pos_x - e->v.dir_y * ms)][(int)e->v.pos_y])
			e->v.pos_x -= e->v.dir_y * ms;
		if (!e->map[(int)e->v.pos_x][(int)(e->v.pos_y + e->v.dir_x * ms)])
			e->v.pos_y += e->v.dir_x * ms;
	}
	if (e->keys.d)
	{
		if (!e->map[(int)(e->v.pos_x + e->v.dir_y * ms)][(int)e->v.pos_y])
			e->v.pos_x += e->v.dir_y * ms;
		if (!e->map[(int)e->v.pos_x][(int)(e->v.pos_y - e->v.dir_x * ms)])
			e->v.pos_y -= e->v.dir_x * ms;
	}
}

static void	move_hooks(t_mlx *e)
{
	double ms;

	ms = e->timer.move_speed;
	if (e->keys.w || e->keys.up)
	{
		if (!e->map[(int)(e->v.pos_x + e->v.dir_x * ms)][(int)e->v.pos_y])
			e->v.pos_x += e->v.dir_x * ms;
		if (!e->map[(int)e->v.pos_x][(int)(e->v.pos_y + e->v.dir_y * ms)])
			e->v.pos_y += e->v.dir_y * ms;
	}
	if (e->keys.s || e->keys.down)
	{
		if (!e->map[(int)(e->v.pos_x - e->v.dir_x * ms)][(int)(e->v.pos_y)])
			e->v.pos_x -= e->v.dir_x * ms;
		if (!e->map[(int)(e->v.pos_x)][(int)(e->v.pos_y - e->v.dir_y * ms)])
			e->v.pos_y -= e->v.dir_y * ms;
	}
}

int			loop_hooks(t_mlx *e)
{
	if (e->keys.shift)
		e->timer.move_speed *= 2;
	if (e->keys.left ^ e->keys.right)
		rotation_hooks(e);
	if (e->keys.a ^ e->keys.d)
		strafe_hooks(e);
	if ((e->keys.w || e->keys.up) ^ (e->keys.s || e->keys.down))
		move_hooks(e);
	redraw(e);
	return (0);
}
