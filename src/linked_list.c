/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpasqual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 08:39:27 by tpasqual          #+#    #+#             */
/*   Updated: 2016/12/21 10:46:52 by tpasqual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			ft_sqrt(float a)
{
	float	c;
	int		n;
	int		compteur;

	compteur = 1;
	c = 1;
	n = 15;
	while (compteur <= n)
	{
		c = 0.5 * (c + a / c);
		compteur++;
	}
	compteur = c;
	return (compteur);
}

int		ft_list_size(t_point *debut)
{
	int	i;

	i = 1;
	while (debut->next != NULL)
	{
		debut = debut->next;
		i++;
	}
	return (i);
}

void		ft_lstadd_point(t_point *point, t_point *debut)
{
	t_point	*temp;

	temp = debut;
	while (debut->next != NULL)
	{
		debut = debut->next;
		temp = debut;
	}
	debut->next = point;
	point->prev = temp;
}

t_point			*ft_process_a_tetra(int fd, int count, char *buf)
{
	int			letter;
	t_point		*debut;
	t_point		*point;

	debut = NULL;
	letter = 65;
	while (count >= 20)
	{
		if (check_counts(buf, count) != 0)
			return (NULL);
		point = ft_memo_tetra(buf, letter);
		if (debut == NULL)
		{
			debut = point;
			debut->prev = NULL;
			debut->next = NULL;
		}
		else
			ft_lstadd_point(point, debut);
		count = read(fd, buf, 21);
		letter++;
	}
	return (debut);
}

t_point			*read_tetri(int fd)
{
	char		*buf;
	int			count;
	t_point		*debut;

	debut = NULL;
	buf = ft_strnew(21);
	count = read(fd, buf, 21);
	debut = ft_process_a_tetra(fd, count, buf);
	return (debut);
}
