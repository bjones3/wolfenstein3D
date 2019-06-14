/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjones <BJones033@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 16:31:22 by bjones            #+#    #+#             */
/*   Updated: 2017/10/18 17:08:25 by bjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	map_err(void)
{
	ft_putendl("invalid map");
	exit(-1);
}

void	check_map_bounds(t_mlx *data)
{
	int x;

	x = 0;
	while (x < data->map_w)
	{
		if (!data->map[0][x] || !data->map[data->map_h - 1][x])
			map_err();
		x++;
	}
	x = 0;
	while (x < data->map_h)
	{
		if (!data->map[x][0] || !data->map[x][data->map_w - 1])
			map_err();
		x++;
	}
}
