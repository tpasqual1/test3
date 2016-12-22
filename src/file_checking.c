/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpasqual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 08:39:27 by tpasqual          #+#    #+#             */
/*   Updated: 2016/12/22 11:43:54 by tpasqual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			check_contigous(char *str)
{
	int		block;
	int		i;

	block = 0;
	i = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			if ((i + 1) < 20 && str[i + 1] == '#')
				block++;
			if ((i - 1) >= 0 && str[i - 1] == '#')
				block++;
			if ((i + 5) < 20 && str[i + 5] == '#')
				block++;
			if ((i - 5) >= 0 && str[i - 5] == '#')
				block++;
		}
		i++;
	}
	return (block == 6 || block == 8);
}

int			check_counts(char *str, int count)
{
	int		i;
	int		carok;

	i = 0;
	carok = 0;
	while (i < 20)
	{
		if (i % 5 < 4)
		{
			if (str[i] != '#' && str[i] != '.')
				return (-1);
			if (str[i] == '#')
			{
				carok++;
				if (carok > 4)
					return (-1);
			}
		}
		else if (str[i] != '\n')
			return (-1);
		i++;
	}
	if ((count == 21 && str[20] != '\n') || !check_contigous(str))
		return (-1);
	return (0);
}

void		ft_set_tetra(t_point *points, int nbcar, int i, int y)
{
	if (nbcar == 1)
	{
		points->x1 = i % 5;
		points->y1 = y;
	}
	if (nbcar == 2)
	{
		points->x2 = (i % 5) - points->x1;
		points->y2 = y - points->y1;
	}
	if (nbcar == 3)
	{
		points->x3 = (i % 5) - points->x1;
		points->y3 = y - points->y1;
	}
	if (nbcar == 4)
	{
		points->x4 = (i % 5) - points->x1;
		points->y4 = y - points->y1;
		points->x1 = 0;
		points->y1 = 0;
	}
}

t_point		*ft_memo_tetra(char *str, char letter)
{
	int		i;
	int		nbcar;
	int		y;
	t_point	*points;

	i = 0;
	y = 0;
	nbcar = 1;
	points = malloc(sizeof(t_point));
	while (i < 21)
	{
		if (str[i] == '#')
			ft_set_tetra(points, nbcar, i, y);
		nbcar = nbcar + ((str[i] == '#') ? 1 : 0);
		if (str[i] == '\n')
			y++;
		i++;
	}
	points->prev = NULL;
	points->next = NULL;
	points->letter = letter;
	return (points);
}
