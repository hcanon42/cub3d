/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <hugo@frogames.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 19:09:50 by hcanon            #+#    #+#             */
/*   Updated: 2020/01/20 16:16:15 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_tang(double angle)
{
	double	new_angle;

	new_angle = 0;
	if (angle < 90)
		new_angle = tan(angle * M_PI / 180);
	else if (angle < 180)
		new_angle = tan(-(180.0 - angle) * M_PI / 180);
	else if (angle < 270)
		new_angle = tan((180.0 + angle) * M_PI / 180);
	else
		new_angle = tan(-(360.0 - angle) * M_PI / 180);
	return (new_angle);
}

t_point	fill_pt(t_point a, t_pack *pack, double angle, int type)
{
	if (type == 1)
	{
		a.distance = sqrt(a.distance) * cos((angle - pack->charac.angle)
			* M_PI / 180);
		a.texture = (angle < 180) ? 'S' : 'N';
		if (a.x > 0 && a.x < ft_strlen(pack->map.big_map[(int)a.y]))
			a.type = (pack->map.big_map[(int)a.y][(int)a.x] == '2') ? 'F' : 0;
	}
	else
		a.x = pack->charac.x / 64 * 64 + ((angle >= 90 && angle < 270)
				? -0.000001 : 64);
	return (a);
}

t_point	find_final_inter(t_pack *pack, double angle, t_point b)
{
	t_point	a;
	double	new_angle;

	new_angle = get_tang(angle);
	a.column = b.column;
	a.y = pack->charac.y / 64 * 64 + ((angle < 180) ? -0.000001 : 64);
	a.x = pack->charac.x + (pack->charac.y - a.y) / new_angle;
	while (a.x > 0 && a.x < ft_strlen(pack->map.big_map[(int)a.y]) &&
			pack->map.big_map[(int)a.y][(int)a.x] < '1')
	{
		a.y += (angle < 180) ? -64 : 64;
		a.x += (angle < 180) ? 64 / new_angle : -64 / new_angle;
	}
	a.distance = pow(pack->charac.x - a.x, 2) + pow(pack->charac.y - a.y, 2);
	if (a.x < 0 || a.x >= ft_strlen(pack->map.big_map[(int)a.y]))
		a.distance = b.distance + 1;
	if (a.distance < b.distance || b.distance == -1)
	{
		a = fill_pt(a, pack, angle, 1);
		return (a);
	}
	b.distance = sqrt(b.distance) * cos((angle - pack->charac.angle)
				* M_PI / 180);
	return (b);
}

t_point	find_inter(t_pack *pack, double angle, int column)
{
	t_point		a;
	double		new_angle;

	while (angle < 0 || angle >= 360)
	{
		angle -= (angle >= 360) ? 360 : 0;
		angle += (angle < 0) ? 360 : 0;
	}
	a.column = column;
	new_angle = get_tang(angle);
	a = fill_pt(a, pack, angle, 0);
	a.y = pack->charac.y + (pack->charac.x - a.x) * new_angle;
	while (a.y > 0 && a.y < pack->map.map_y * 64 &&
			pack->map.big_map[(int)a.y][(int)a.x] < '1')
	{
		a.x += (angle >= 90 && angle < 270) ? -64 : 64;
		a.y -= (angle >= 90 && angle < 270) ? -64 * new_angle : 64 * new_angle;
	}
	a.distance = pow(pack->charac.x - a.x, 2) + pow(pack->charac.y - a.y, 2);
	if (a.y < 0 || a.y > pack->map.map_y * 64)
		a.distance = -1;
	else
		a.type = (pack->map.big_map[(int)a.y][(int)a.x] == '2') ? 'F' : 0;
	a.texture = ((angle >= 90 && angle < 270) ? 'E' : 'W');
	return (find_final_inter(pack, angle, a));
}

t_wall	init_wall(t_map map, t_plane plane, t_point inter, int column)
{
	t_wall	wall;

	wall.type = inter.type;
	if ((double)inter.distance > 0.01)
		wall.height = ceil(64.0 *
			(double)plane.distance_char / (double)inter.distance);
	else
		wall.height = 500000;
	wall.x = column;
	wall.y = (map.resol_y - wall.height) / 2;
	wall.texture = inter.texture;
	wall.heat = wall.height / 64.0;
	if (inter.texture == 'N' || inter.texture == 'S')
		wall.purcentage = (int)inter.x % 64;
	else
		wall.purcentage = (int)inter.y % 64;
	return (wall);
}
