/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 10:57:45 by abinois           #+#    #+#             */
/*   Updated: 2019/07/08 14:28:24 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"
#include "libft/libft.h"

int		player_problem(char *line)
{
	int		ok;
	int		i;

	i = -1;
	ok = 0;
	while (line[++i])
	{
		if (line[i] == 'p')
		{
			if (line[i + 1] != '1' && line[i + 1] != '2')
				return (errors(1, &line));
			else
				ok++;
		}
		if (!(ft_strstr(line, "abinois")))
			return (errors(1, &line));
	}
	return (ok != 1 || *line != '$' ? errors(1, &line) : 1);
}

int		size_problem(char *line, t_map *map, int o)
{
	int		i;
	int		ok;

	i = -1;
	ok = 0;
	if (o == 1 && !(ft_strnstr(line, "Plateau", 7)))
		return (errors(2, &line));
	if (o == 2 && !(ft_strnstr(line, "Piece", 5)))
		return (errors(4, &line));
	if (o == 2 && (!map->start1 || !map->start2))
		return (errors(0, &line));
	while (line[++i])
		if (ft_isdigit(line[i]))
		{
			ok++;
			if (line[i - 1] == '-')
				return (o == 1 ? errors(2, &line) : errors(4, &line));
			while (line[i] && ft_isdigit(line[i]))
				i++;
		}
	if (ok != 2)
		o == 1 ? errors(2, &line) : errors(4, &line);
	return (ok != 2 ? 0 : 1);
}

int		line_problem(char *line, t_map *map, int o)
{
	int		i;

	i = -1;
	while (o == 1 && ++i < map->nc + 4 && line[i])
	{
		if ((i < 3 && !(ft_isdigit(line[i]))) || (i == 3 && line[i] != ' '))
			return (errors(3, &line));
		if (i > 3 && i < map->nc + 4 && (line[i] != '.' && line[i] != 'O'
			&& line[i] != 'X' && line[i] != 'o' && line[i] != 'x'))
			return (errors(3, &line));
		if (i > 3 && i < map->nc + 4 && line[i] == map->me)
			(map->start1)++;
		if (i > 3 && i < map->nc + 4 && line[i] == map->enemy)
			(map->start2)++;
	}
	while (o == 2 && ++i < map->l_f && line[i])
		if (line[i] != '*' && line[i] != '.')
			return (errors(5, &line));
	if (o == 1)
		return (i != map->nc + 4 ? errors(3, &line) : 1);
	else
		return (i != map->l_f ? errors(5, &line) : 1);
}

int		problem_round1(char *line, t_map *map)
{
	if (map->line == 1)
		return (player_problem(line));
	else if (map->line == 2)
		return (size_problem(line, map, 1));
	if (map->line > 3 && map->line <= map->nl + 3)
		return (line_problem(line, map, 1));
	if (map->line == map->nl + 4)
		return (size_problem(line, map, 2));
	if (map->line > map->nl + 4 && map->line < map->nl + map->h_f + 5)
		return (line_problem(line, map, 2));
	return (1);
}

int		problem(char *line, t_map *map)
{
	(map->line)++;
	if (map->rnd == 1)
		return (problem_round1(line, map));
	if (map->rnd > 1)
	{
		if (map->line == 1)
			return (size_problem(line, map, 1));
		if (map->line > 2 && map->line <= map->nl + 2)
			return (line_problem(line, map, 1));
		if (map->line == map->nl + 3)
			return (size_problem(line, map, 2));
		if (map->line > map->nl + 3 && map->line < map->nl + map->h_f + 4)
			return (line_problem(line, map, 2));
	}
	return (1);
}
