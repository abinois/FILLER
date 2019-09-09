/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:06:40 by abinois           #+#    #+#             */
/*   Updated: 2019/07/09 19:48:14 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"
#include "libft/libft.h"
#include <stdlib.h>

void	reset_map(t_map *map, int o)
{
	if (o == 0)
	{
		map->me = '?';
		map->enemy = '?';
		map->nc = 0;
		map->nl = 0;
		map->d = 0;
		map->b = NULL;
		map->rnd = 1;
	}
	if (o == 0 || o == 1)
	{
		map->start1 = 0;
		map->start2 = 0;
		map->line = 0;
		map->h_f = 0;
		map->l_f = 0;
		map->form = NULL;
	}
}

int		free_map(t_map *map, int option)
{
	int		i;

	i = map->nl;
	if ((option == 1 || option == 3) && map->b)
		while (--i >= 0)
			free(map->b[i]);
	i = map->h_f;
	if ((option == 2 || option == 3) && map->form)
		while (--i >= 0)
			free(map->form[i]);
	if ((option == 1 || option == 0 || option == 3) && map->b)
		free(map->b);
	if ((option == 2 || option == 4 || option == 3) && map->form)
		free(map->form);
	return (-1);
}

int		errors(int option, char **line)
{
	if (option == 0)
		ft_putstr_fd("\033[31m🆘  Map Error\n\033[0m", 2);
	if (option == 1)
		ft_putstr_fd("\033[31m🆘  Player Error\n\033[0m", 2);
	if (option == 2)
		ft_putstr_fd("\033[31m🆘  Board Size Error\n\033[0m", 2);
	if (option == 3)
		ft_putstr_fd("\033[31m🆘  Board Line Error\n\033[0m", 2);
	if (option == 4)
		ft_putstr_fd("\033[31m🆘  Piece Size Error\n\033[0m", 2);
	if (option == 5)
		ft_putstr_fd("\033[31m🆘  Piece Line Error\n\033[0m", 2);
	ft_get_next_line(0, line, 1);
	return (0);
}

int		player(t_map *map)
{
	int		p;
	int		lblf[2];
	char	*line;

	lblf[0] = -1;
	lblf[1] = -1;
	line = NULL;
	if (get_struct(map, 0, lblf, line) == -1)
		return (free_map(map, 3));
	heat_map(map, 0);
	p = place_form(map, 0, 0, 0);
	if (p == -2)
		return (free_map(map, 3));
	free_map(map, 2);
	reset_map(map, 1);
	(map->rnd)++;
	return (p);
}

int		main(void)
{
	t_map	map;
	int		r;
	char	*line;

	reset_map(&map, 0);
	while (1)
		if ((r = player(&map)) <= 0)
			break ;
	if (r == 0)
		free_map(&map, 1);
	ft_get_next_line(0, &line, 1);
	return (0);
}
