/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjones <BJones033@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 02:08:07 by bjones            #+#    #+#             */
/*   Updated: 2017/10/18 02:10:04 by bjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int	keydown_hooks(int keycode, t_mlx *data)
{
	if (keycode == KEY_LEFT)
		data->keys.left = 1;
	if (keycode == KEY_RIGHT)
		data->keys.right = 1;
	if (keycode == KEY_A)
		data->keys.a = 1;
	if (keycode == KEY_W)
		data->keys.w = 1;
	if (keycode == KEY_UP)
		data->keys.up = 1;
	if (keycode == KEY_D)
		data->keys.d = 1;
	if (keycode == KEY_S)
		data->keys.s = 1;
	if (keycode == KEY_DOWN)
		data->keys.down = 1;
	if (keycode == KEY_SHIFT)
		data->keys.shift = 1;
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	return (0);
}

int	keyrelease_hooks(int keycode, t_keys *keys)
{
	if (keycode == KEY_LEFT)
		keys->left = 0;
	if (keycode == KEY_RIGHT)
		keys->right = 0;
	if (keycode == KEY_A)
		keys->a = 0;
	if (keycode == KEY_W)
		keys->w = 0;
	if (keycode == KEY_UP)
		keys->up = 0;
	if (keycode == KEY_D)
		keys->d = 0;
	if (keycode == KEY_S)
		keys->s = 0;
	if (keycode == KEY_DOWN)
		keys->down = 0;
	if (keycode == KEY_SHIFT)
		keys->shift = 0;
	return (0);
}

int	exit_hook(t_mlx *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}
