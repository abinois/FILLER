/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinois <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:59:14 by abinois           #+#    #+#             */
/*   Updated: 2019/06/24 18:05:15 by abinois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char **s, unsigned int strt, size_t ln, int o)
{
	char	*new;
	size_t	i;

	i = 0;
	if (!*s || !(new = ft_strnew(ln)))
		return (NULL);
	while (ln--)
		new[i++] = (*s)[strt++];
	if (o == 1)
		ft_memdel((void**)s);
	return (new);
}
