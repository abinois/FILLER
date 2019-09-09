/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 14:43:50 by abinois           #+#    #+#             */
/*   Updated: 2019/07/08 14:37:59 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"
#include "libft/libft.h"
#include <stdlib.h>

void	get_players(char *line, t_map *map)
{
	if (ft_strstr(line, "abinois"))
	{
		if (ft_strstr(line, "p1"))
			map->me = 'O';
		else
			map->me = 'X';
		map->enemy = (map->me == 'O') ? 'X' : 'O';
	}
}

int		get_board_or_form_size(char *line, t_map *map, int i, int o)
{
	if (o == 1)
	{
		while (!(ft_isdigit(line[i])))
			i++;
		map->nl = ft_atoi(line + i);
		while (ft_isdigit(line[i]))
			i++;
		map->nc = ft_atoi(line + i + 1);
		if (map->nl <= 0 || !(map->b = (int**)malloc(sizeof(int*) * map->nl)))
			return (-1);
		map->d = map->nc > map->nl ? map->nc + 1 : map->nl + 1;
	}
	if (o == 2)
	{
		while (!(ft_isdigit(line[i])))
			i++;
		map->h_f = ft_atoi(line + i);
		while (ft_isdigit(line[i]))
			i++;
		map->l_f = ft_atoi(line + i + 1);
		if (map->h_f <= 0 || map->l_f <= 0
			|| !(map->form = (char**)malloc(sizeof(char*) * map->h_f)))
			return (-1);
	}
	return (map->nc <= 0 ? -1 : 0);
}

int		get_board_line(char *line, t_map *map, int lb)
{
	if (map->rnd == 1)
	{
		if (!(map->b[lb] = (int*)malloc(sizeof(int) * map->nc)))
		{
			while (--lb >= 0)
				ft_memdel((void**)map->b + lb);
			free_map(map, 0);
			return (-1);
		}
	}
	return (fill_board_line(line, map, lb));
}

int		get_form_line(char *line, t_map *map, int lf)
{
	if (!(map->form[lf] = ft_strsub((const char**)&line, 0, map->l_f, 0)))
	{
		while (--lf >= 0)
			ft_memdel((void**)map->form + lf);
		free_map(map, 4);
		return (-1);
	}
	return (0);
}

int		get_struct(t_map *map, int r, int *lblf, char *line)
{
	while ((r = ft_get_next_line(0, &line, 0) > 0)
		&& (r = problem(line, map)))
	{
		if (*line == '$' && map->rnd == 1)
			get_players(line, map);
		if (ft_strnstr(line, "Plateau", 7) && !(map->b))
			if (get_board_or_form_size(line, map, 0, 1) == -1)
				return (free_map(map, 0));
		if (ft_isdigit(*line) && map->nc && ((map->rnd == 1 && map->line > 3)
			|| (map->rnd > 1 && map->line > 2)))
			if (get_board_line(line, map, ++(lblf[0])) == -1)
				return (-1);
		if (ft_strnstr(line, "Piece", 5))
			if (get_board_or_form_size(line, map, 0, 2) == -1)
				return (free_map(map, 1));
		if ((*line == '.' || *line == '*') && map->l_f)
			if (get_form_line(line, map, ++(lblf[1])) == -1)
				return (free_map(map, 1));
		if (map->h_f != 0 && lblf[1] == map->h_f - 1 && lblf[0] == map->nl - 1)
			break ;
		ft_memdel((void**)&line);
	}
	ft_memdel((void**)&line);
	return (r <= 0 ? -1 : 0);
}
