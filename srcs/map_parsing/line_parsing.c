/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <hugo@frogames.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 21:36:19 by hcanon            #+#    #+#             */
/*   Updated: 2020/06/10 10:12:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_resol(char *line, t_map *map)
{
	(map->resol_x != -1) ? ft_error(1) : 0;
	while (*line == ' ' || *line == 'R')
		line++;
	map->resol_x = ft_atoi(line);
	while (*line >= '0' && *line <= '9')
		line++;
	map->resol_y = ft_atoi(line);
	while (*line == ' ')
		line++;
	(*line == 0) ? ft_error(3) : 0;
	while (*line >= '0' && *line <= '9')
		line++;
	(*line != 0) ? ft_error(3) : 0;
	if (map->resol_x < 150)
		ft_error(7);
	if (map->resol_y < 100)
		ft_error(7);
	return (0);
}

int		ft_sprite(char *line, t_pack *pack)
{
	int		i;
	char	letter;

	i = 0;
	while (line[i] == ' ')
		i++;
	letter = line[i + ((line[i] == 'S') ? 1 : 0)];
	i += 2;
	while (line[i] == ' ')
		i++;
	if (letter == 'N')
		ft_north_texture(pack, line, i);
	else if (letter == 'O')
		ft_south_texture(pack, line, i);
	else if (letter == 'W')
		ft_west_texture(pack, line, i);
	else if (letter == 'E')
		ft_east_texture(pack, line, i);
	else if (letter == ' ')
		ft_sprite_texture(pack, line, i);
	else
		ft_error(4);
	return (0);
}

void	ft_color_parsing(char *line, t_map *map)
{
	int		i;
	char	letter;

	i = 0;
	while (line[i] == ' ')
		i++;
	(line[i] == 0) ? ft_error(6) : 0;
	letter = line[i++];
	(line[i] == 0) ? ft_error(6) : 0;
	(letter == 'F' ? map->f_color : map->c_color)[0] = ft_atoi(line + i);
	while (line[++i] != ',')
		(line[i] == 0) ? ft_error(6) : 0;
	i++;
	(letter == 'F' ? map->f_color : map->c_color)[1] = ft_atoi(line + i);
	while (line[++i] != ',')
		(line[i] == 0) ? ft_error(6) : 0;
	i++;
	(letter == 'F' ? map->f_color : map->c_color)[2] = ft_atoi(line + i);
	while (line[i] == ' ')
		i++;
	(line[i] == 0) ? ft_error(6) : 0;
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	(line[i] != 0) ? ft_error(6) : 0;
	map->test[0] += (letter == 'F') ? 1 : 10;
}

int		line_test(char *line, t_pack *pack)
{
	int	i;

	i = 0;
	if (line[i] != 0)
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == 0)
			return (0);
		else if (line[i] == 'R')
			ft_resol(line, &pack->map);
		else if (line[i] == 'S' || (line[i] == 'N' && line[i + 1] == 'O') ||
				(line[i] == 'S' && line[i + 1] == 'O') ||
				(line[i] == 'W' && line[i + 1] == 'E') ||
				(line[i] == 'E' && line[i + 1] == 'A'))
			ft_sprite(line, pack);
		else if (line[i] == 'F' || line[i] == 'C')
			ft_color_parsing(line, &pack->map);
		else if (line[i] == '1' || line[i] == '2')
			return (1);
		else
			ft_error(1);
	}
	free(line);
	return (0);
}
