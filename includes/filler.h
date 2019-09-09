/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:08:15 by abinois           #+#    #+#             */
/*   Updated: 2019/07/08 14:17:59 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "ft_printf.h"

typedef struct	s_map
{
	int		nc;
	int		nl;
	int		**b;
	int		l_f;
	int		h_f;
	char	**form;
	char	me;
	char	enemy;
	int		d;
	int		rnd;
	int		line;
	int		start1;
	int		start2;
}				t_map;

void			reset_map(t_map *map, int o);
int				free_map(t_map *map, int option);
int				errors(int	option, char **line);
int				player(t_map *map);

void			get_players(char *line, t_map *map);
int				get_board_or_form_size(char *line, t_map *map, int i, int o);
int				get_board_line(char *line, t_map *map, int nl);
int				get_form_line(char *line, t_map *map, int hf);
int				get_struct(t_map *map, int r, int *lblf, char *line);

int				fill_board_line(char *line, t_map *map, int lb);
int				heat_map(t_map *map, int h);
int				put_heat(t_map *map, int l, int c, int h);
int				place_form(t_map *map, int fat, int x, int y);
int				getfat(t_map *map, int ml, int mc, int fat);

int				player_problem(char *line);
int				size_problem(char *line, t_map *map, int o);
int				line_problem(char *line, t_map *map, int o);
int				problem_round1(char *line, t_map *map);
int				problem(char *line, t_map *map);

#endif
