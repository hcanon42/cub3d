/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <hugo@frogames.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 19:09:50 by hcanon            #+#    #+#             */
/*   Updated: 2019/12/04 21:18:16 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture(t_wall wall, t_pack *pack)
{
	if (wall.type == 'F')
		return (pack->map.sprite_texture);
	else if (wall.texture == 'N')
		return (pack->map.north_texture);
	else if (wall.texture == 'S')
		return (pack->map.south_texture);
	else if (wall.texture == 'W')
		return (pack->map.west_texture);
	else
		return (pack->map.east_texture);
}

int		overwall(t_wall wall, t_map map, double *pixel)
{
	double	j;
	int		ret;

	ret = 4 * wall.purcentage;
	*pixel = 0.0;
	if (wall.height > map.resol_y)
	{
		j = (double)((64.0 * ((float)((wall.height - map.resol_y) / 2) /
														wall.height)));
		*pixel = (j - (int)j) * wall.heat;
		j = (int)j;
		j *= 256;
		ret += j;
	}
	return (ret);
}

void	print_wall(t_wall wall, char *str, t_map map, t_pack *pack)
{
	char	*texture;
	int		i;
	int		j;
	double	pixel;

	i = 0;
	j = overwall(wall, map, &pixel);
	wall.height *= 4 * map.resol_x;
	texture = get_texture(wall, pack);
	while (i < wall.height && i < map.resol_y * map.resol_x * 4)
	{
		str[i++] = (int)texture[j++];
		str[i++] = (int)texture[j++];
		str[i++] = (int)texture[j++];
		i += map.resol_x * 4 - 3;
		j -= 3;
		pixel++;
		while (pixel >= wall.heat)
		{
			j += 256;
			pixel -= wall.heat;
		}
	}
}

void	print_hud(t_pack *pack)
{
	int		color;
	char	*str;
	char	*hp;

	hp = ft_itoa(pack->charac.hp);
	str = ft_itoa(pack->nb_moves);
	mlx_string_put(pack->mlx_ptr, pack->win_ptr, 10, 10, WHITE, "Esc to quit.");
	color = ((pack->charac.hp < 50) ? RED : GREEN);
	mlx_string_put(pack->mlx_ptr, pack->win_ptr, 10,
					pack->map.resol_y - 50, WHITE, "Moves : ");
	mlx_string_put(pack->mlx_ptr, pack->win_ptr, 100,
						pack->map.resol_y - 50, WHITE, str);
	mlx_string_put(pack->mlx_ptr, pack->win_ptr,
					10, pack->map.resol_y - 30, WHITE, "Health : ");
	mlx_string_put(pack->mlx_ptr, pack->win_ptr,
			100, pack->map.resol_y - 30, color, hp);
	if (pack->charac.hp <= 0)
	{
		mlx_string_put(pack->mlx_ptr, pack->win_ptr, pack->map.resol_x / 2 - 20,
		pack->map.resol_y / 2, RED, "GAME OVER");
	}
	free(str);
	free(hp);
}
