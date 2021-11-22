/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcanon <hugo@frogames.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 22:05:38 by hcanon            #+#    #+#             */
/*   Updated: 2019/11/18 04:52:25 by hcanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		change_pos(int type, int max_pos, t_pack *pack)
{
	if (type == 0)
	{
		if (pack->map.big_map[pack->charac.y][max_pos] != '1')
			pack->charac.x = max_pos;
		else
			return (2);
	}
	else if (type == 1)
	{
		if (pack->map.big_map[max_pos][pack->charac.x] != '1')
			pack->charac.y = max_pos;
		else
			return (2);
	}
	return (0);
}

int		ft_move(t_pack *pack, int type)
{
	int		x;
	int		y;
	int		loss_hp;

	if (type == 0 || type == 1)
	{
		x = round(8.0 * cos(pack->charac.angle * M_PI / 180));
		y = round(8.0 * -sin(pack->charac.angle * M_PI / 180));
	}
	else
	{
		x = round(8.0 * cos((pack->charac.angle + 90) * M_PI / 180));
		y = round(8.0 * -sin((pack->charac.angle + 90) * M_PI / 180));
	}
	x = pack->charac.x + ((type == 1 || type == 3) ? x : -x);
	y = pack->charac.y + ((type == 1 || type == 3) ? y : -y);
	loss_hp = change_pos(0, x, pack);
	loss_hp += change_pos(1, y, pack);
	return (loss_hp);
}

int		ft_premove(t_pack *pack, int key)
{
	if (key == 122)
		pack->charac.hp -= ft_move(pack, 1);
	else if (key == 115)
		pack->charac.hp -= ft_move(pack, 0);
	else if (key == 113)
		pack->charac.hp -= ft_move(pack, 3);
	else if (key == 100)
		pack->charac.hp -= ft_move(pack, 2);
	return (0);
}

int		deal_key(int key, void *param)
{
	t_pack	*pack;

	pack = (t_pack *)param;
	if (pack->charac.hp == -100 && key != 65307)
		return (0);
	if (key == 65307 || pack->charac.hp <= 0)
	{
		pt_image(pack);
		(pack->charac.hp <= 0 && pack->charac.hp != -100) ? sleep(2) : 0;
		ft_exit(pack);
	}
	else if (key == 65361)
		pack->charac.angle += 4;
	else if (key == 65363)
		pack->charac.angle -= 4;
	else if (key == 113 || key == 115 || key == 122 || key == 100)
		ft_premove(pack, key);
	else
		return (0);
	pack->nb_moves++;
	pt_image(pack);
	if (pack->map.big_map[pack->charac.y][pack->charac.x] == '2')
		ft_end(pack);
	return (0);
}
