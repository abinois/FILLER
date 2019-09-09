/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 19:54:41 by abinois           #+#    #+#             */
/*   Updated: 2019/07/08 11:13:20 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

int		fill_board_line(char *line, t_map *map, int lb)
{
	int		l;
	int		i;

	l = 4;
	i = 0;
	while (line[l] && l < map->nc + 4 && i < map->nc)
	{
		if (line[l] == '.')
			map->b[lb][i] = map->d;
		else if (line[l] == map->me || line[l] == map->me + 32)
			map->b[lb][i] = -1;
		else if (line[l] == map->enemy || line[l] == map->enemy + 32)
			map->b[lb][i] = 0;
		l++;
		i++;
	}
	return (l < map->nc + 3 ? -1 : 0);
}

int		put_heat(t_map *map, int l, int c, int heat)
{
	int		r;

	r = 1;
	if (l - 1 >= 0 && map->b[l - 1][c] == map->d && r++)
		map->b[l - 1][c] = heat + 1;
	if (l - 1 >= 0 && c - 1 >= 0 && map->b[l - 1][c - 1] == map->d && r++)
		map->b[l - 1][c - 1] = heat + 1;
	if (l - 1 >= 0 && c + 1 < map->nc && map->b[l - 1][c + 1] == map->d && r++)
		map->b[l - 1][c + 1] = heat + 1;
	if (l + 1 < map->nl)
	{
		if (map->b[l + 1][c] == map->d && r++)
			map->b[l + 1][c] = heat + 1;
		if (c - 1 >= 0 && map->b[l + 1][c - 1] == map->d && r++)
			map->b[l + 1][c - 1] = heat + 1;
		if (c + 1 < map->nc && map->b[l + 1][c + 1] == map->d && r++)
			map->b[l + 1][c + 1] = heat + 1;
	}
	if (c - 1 >= 0 && map->b[l][c - 1] == map->d && r++)
		map->b[l][c - 1] = heat + 1;
	if (c + 1 < map->nc && map->b[l][c + 1] == map->d && r++)
		map->b[l][c + 1] = heat + 1;
	return (r);
}

int		heat_map(t_map *map, int heat)
{
	int		l;
	int		c;
	int		r;

	r = 1;
	while (r)
	{
		r = 0;
		l = -1;
		while (++l < map->nl)
		{
			c = -1;
			while (++c < map->nc)
				if (map->b[l][c] == heat)
					r += put_heat(map, l, c, heat) > 1 ? 1 : 0;
		}
		heat++;
	}
	return (r);
}

int		getfat(t_map *map, int ml, int mc, int fat)
{
	int		fl;
	int		fc;
	int		starmatch;

	starmatch = 0;
	fl = -1;
	while (++fl < map->h_f)
	{
		fc = -1;
		while (++fc < map->l_f)
			if (map->form[fl][fc] == '*')
			{
				if (ml + fl < 0 || ml + fl >= map->nl || mc + fc >= map->nc
					|| mc + fc < 0 || map->b[ml + fl][mc + fc] == 0)
					return (0);
				if (map->b[ml + fl][mc + fc] == -1)
					if (++starmatch > 1)
						return (0);
				if (map->b[ml + fl][mc + fc] > 0)
					fat += map->b[ml + fl][mc + fc];
			}
	}
	return (starmatch == 0 ? 0 : fat);
}

int		place_form(t_map *map, int fat, int x, int y)
{
	int		ml;
	int		mc;
	int		min;

	min = 44444;
	ml = 0 - map->h_f;
	while (++ml < map->nl)
	{
		mc = 0 - map->l_f;
		while (++mc < map->nc)
			if ((fat = getfat(map, ml, mc, 0)) < min && fat > 0)
			{
				min = fat;
				x = ml;
				y = mc;
			}
	}
	if (ft_printf("%d %d\n", x, y) == -1)
		return (-2);
	return (min == 44444 ? 0 : 1);
}
