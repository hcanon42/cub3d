/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <hugo@frogames.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:09:29 by hcanon            #+#    #+#             */
/*   Updated: 2019/12/04 21:15:23 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		structs_malloc(t_map *map)
{
	if (!(map->f_color = (int *)malloc(sizeof(int) * 3)) ||
		!(map->c_color = (int *)malloc(sizeof(int) * 3)) ||
		!(map->test = (int *)malloc(sizeof(int) * 6)) ||
		!(map->map = (char **)malloc(sizeof(char *) * 100)))
		ft_error(0);
	map->test[0] = 0;
	map->test[1] = 0;
	map->test[2] = 0;
	map->test[3] = 0;
	map->test[4] = 0;
	map->test[5] = 0;
	map->f_color[0] = -1;
	map->c_color[0] = -1;
	map->map_y = 0;
	return (0);
}

int		init_charac(t_charac *charac, t_map *map, int i, int j)
{
	charac->x = i + 32;
	charac->y = j + 32;
	charac->hp = 100;
	if (map->map[j / 64][i / 64] == 'N')
		charac->angle = 90;
	else if (map->map[j / 64][i / 64] == 'W')
		charac->angle = 180;
	else if (map->map[j / 64][i / 64] == 'S')
		charac->angle = 270;
	else if (map->map[j / 64][i / 64] == 'E')
		charac->angle = 0;
	else
		ft_error(4);
	map->big_map[j][i] = '0';
	return (0);
}

int		big_mapping(t_map *map, t_charac *charac)
{
	int		i;
	int		j;

	j = 0;
	if (!(map->big_map = malloc(sizeof(char *) * 64 * map->map_y)))
		ft_error(0);
	while (j < map->map_y * 64)
	{
		i = -1;
		if (!(map->big_map[j] = malloc(64 * ft_strlen(map->map[j / 64]) + 1)))
			ft_error(0);
		while (++i < ft_strlen(map->map[j / 64]) * 64)
		{
			if (map->map[j / 64][i / 64] <= '2')
				map->big_map[j][i] = map->map[j / 64][i / 64];
			else
				(charac->x == 0) ? init_charac(charac, map, i, j) :
				(map->big_map[j][i] = '0');
			check_map(map, j / 64, i / 64, 1);
			if (map->big_map[j][i] == ' ')
				map->big_map[j][i] = '1';
		}
		j++;
	}
	return (0);
}

int		newline_map(t_map *map, int *i, char *line)
{
	int		j;
	int		k;

	k = -1;
	j = -1;
	if (!(map->map[*i] = malloc(sizeof(char) * (ft_strlen(line) + 1))))
		ft_error(0);
	while (line[++j])
		if (line[j] != '0' && line[j] != '1' && line[j] != '2'
			&& line[j] != 'N' && line[j] != 'S' && line[j] != 'E'
			&& line[j] != 'W' && line[j] != ' ')
			ft_error(1);
	j = -1;
	while (line[++k])
	{
		map->map[*i][++j] = line[k];
		if (line[k] == '0' || line[k] >= 'A')
			check_map(map, *i, j, 0);
	}
	map->map[(*i)++][++j] = 0;
	map->map_y++;
	free(line);
	return (0);
}

int		map_parsing(char *file, t_pack *pack)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error(2);
	while (get_next_line(fd, &line) != 0)
	{
		if (line_test(line, pack) == 1)
		{
			i = 0;
			newline_map(&pack->map, &i, line);
			while (get_next_line(fd, &line) != 0)
				newline_map(&pack->map, &i, line);
		}
	}
	return (0);
}
