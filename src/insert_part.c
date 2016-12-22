/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpasqual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 08:39:27 by tpasqual          #+#    #+#             */
/*   Updated: 2016/12/22 11:46:23 by tpasqual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			ft_check_borders(t_point *debut, int col, int lig, int dim)
{
	if (col + debut->x2 < 0 || col + debut->x3 < 0 || col + debut->x4 < 0)
		return (1);
	if (col + debut->x2 > dim || col + debut->x3 > dim || col + debut->x4 > dim)
		return (2);
	if (lig + debut->y2 > dim - 1 || lig + debut->y3 > dim - 1 ||
			lig + debut->y4 > dim - 1)
		return (3);
	return (0);
}

int			ft_copy_part(char **grid, t_point *debut, int col, int lig)
{
	if (grid[lig][col] == '.')
	{
		if (grid[lig + debut->y2][col + debut->x2] == '.' &&
				grid[lig + debut->y3][col + debut->x3] == '.' &&
				grid[lig + debut->y4][col + debut->x4] == '.')
		{
			grid[lig][col] = debut->letter;
			grid[lig + debut->y2][col + debut->x2] = debut->letter;
			grid[lig + debut->y3][col + debut->x3] = debut->letter;
			grid[lig + debut->y4][col + debut->x4] = debut->letter;
			return (0);
		}
	}
	return (1);
}

int			ft_del_part(char **grid, t_point *debut, int col, int lig)
{
	grid[lig][col] = '.';
	grid[lig + debut->y2][col + debut->x2] = '.';
	grid[lig + debut->y3][col + debut->x3] = '.';
	grid[lig + debut->y4][col + debut->x4] = '.';
	return (0);
}

int			ft_insert_part(char **grid, t_point *debut, int dim)
{
	int		col;
	int		lig;

	col = 0;
	lig = 0;
	if (debut == NULL)
		return (0);
	while (lig < dim)
	{
		while (col < dim)
		{
			if (ft_check_borders(debut, col, lig, dim) == 0)
				if (ft_copy_part(grid, debut, col, lig) == 0)
				{
					if (ft_insert_part(grid, debut->next, dim) == 0)
						return (0);
					else
						ft_del_part(grid, debut, col, lig);
				}
			col++;
		}
		col = 0;
		lig++;
	}
	return (1);
}

int			ft_place_parts(char ***grid, t_point *debut, int dim)
{
	int		ret;
	int		dm;

	dm = dim;
	ret = ft_insert_part(*grid, debut, dm);
	while (ret != 0)
	{
		dm++;
		ft_greater_grid(grid, dm);
		ret = ft_insert_part(*grid, debut, dm);
	}
	return (dm);
}
