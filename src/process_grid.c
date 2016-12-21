/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpasqual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 08:39:27 by tpasqual          #+#    #+#             */
/*   Updated: 2016/12/21 10:37:45 by tpasqual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			ft_dim_grid(int list_size)
{
	int		i;

	i = ft_sqrt(list_size * 4);
	if (i * i < list_size * 4)
		i = i + 1;
	return (i);
}

char		**ft_create_grid(int dim)
{
	char	**grid;
	int		i;
	int		j;

	i = 0;
	grid = (char **)malloc(sizeof(char *) * dim);
	while (i < dim)
	{
		grid[i] = (char *)malloc(sizeof(char) * dim);
		i++;
	}
	i = 0;
	while (i < dim)
	{
		j = 0;
		while (j < dim)
		{
			grid[i][j] = '.';
			j++;
		}
		i++;
	}
	return (grid);
}

void		ft_print_grid(char **grid, int dim)
{
	int		i;

	i = 0;
	while (i < dim)
	{
		write(1, grid[i], dim);
		ft_putchar('\n');
		i++;
	}
}

void		ft_greater_grid(char ***grid, int dim)
{
	char	**new_grid;
	int		i;

	i = 0;
	new_grid = (char **)malloc(sizeof(char *) * dim);
	while (i < dim)
	{
		new_grid[i] = (char *)malloc(sizeof(char) * dim);
		ft_memset(new_grid[i], 46, dim);
		i++;
	}
	i = 0;
	while (i < dim - 1)
	{
		free((*grid)[i]);
		i++;
	}
	*grid = new_grid;
}
