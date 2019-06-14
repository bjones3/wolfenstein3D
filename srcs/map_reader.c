/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjones <BJones033@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 18:25:21 by bjones            #+#    #+#             */
/*   Updated: 2017/10/18 17:22:05 by bjones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int	**malloc_world_map(int width, int height)
{
	int **world_map;
	int i;

	world_map = (int **)malloc(sizeof(int *) * height);
	i = -1;
	while (++i < height)
		*(world_map + i) = (int *)malloc(sizeof(int) * width);
	return (world_map);
}

int			**init_world_map(int width, int height, int fd)
{
	int		**world_map;
	int		i;
	int		j;
	char	*line;
	char	**s;

	world_map = malloc_world_map(width, height);
	i = 0;
	while (get_next_line(fd, &line))
	{
		s = ft_strsplit(line, ' ');
		ft_strdel(&line);
		j = -1;
		while (s[++j] != NULL)
		{
			if (!(*(s[j]) >= '0' && *(s[j]) <= '8' && ft_strlen(s[j]) == 1))
				map_err();
			world_map[i][j] = ft_atoi(s[j]);
		}
		if (j != width)
			map_err();
		ft_strarrdel(&s);
		i++;
	}
	return (world_map);
}

int			get_map_width(char *filename)
{
	int		fd;
	int		ret;
	char	*line;
	int		width;

	line = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (-1);
	width = ft_wordct(line, ' ');
	ft_strdel(&line);
	if (width <= 2)
	{
		ft_putendl("invalid map");
		exit(-1);
	}
	return (width);
}

int			fd_linecount(char *filename)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	while (get_next_line(fd, &line))
	{
		ft_strdel(&line);
		count++;
	}
	close(fd);
	if (count <= 2)
	{
		ft_putendl("invalid map");
		exit(-1);
	}
	return (count);
}
