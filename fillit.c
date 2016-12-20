/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpasqual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 08:39:27 by tpasqual          #+#    #+#             */
/*   Updated: 2016/12/20 16:55:35 by tpasqual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "fillit.h"
#include "libft.h"

void	ft_putnbr_bn(int i)
{
	ft_putchar('\n');
	ft_putnbr(i);
	ft_putchar('\n');
}

int		check_contigous(char *str)
{
	int block;
	int i;

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

int		check_counts(char *str, int count)
{
	int i;
	int carok;

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

void			ft_set_tetra(t_point *points, int nblk, int i, int y)
{
	int			mx;
	int			my;
	t_point		*ppoints;

	mx = 0;
	my = 0;
	ppoints = points;
	ppoints->x1 = (nblk == 1) ? 0 : ppoints->x1;
	ppoints->y1 = (nblk == 1) ? 0 : ppoints->y1;
	mx = (nblk == 1) ? i % 5 : mx;
	my = (nblk == 1) ? y : my;
	ppoints->x2 = (nblk == 2) ? (i % 5) - mx : ppoints->x2;
	ppoints->y2 = (nblk == 2) ? y - my : ppoints->y2;
	ppoints->x3 = (nblk == 3) ? (i % 5) - mx : ppoints->x3;
	ppoints->y3 = (nblk == 3) ? y - my : ppoints->y3;
	ppoints->x4 = (nblk == 4) ? (i % 5) - mx : ppoints->x4;
	ppoints->y4 = (nblk == 4) ? y - my : ppoints->y4;
}

t_point				*ft_memo_tetra(char *str, char letter)
{
	int				i;
	int				nbcar;
	int				x;
	int				y;
	t_point			*points;

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

int			ft_check_borders(t_point *debut, int col, int lig, int dim)
{
	int		ret;

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

int		ft_del_part(char **grid, t_point *debut, int col, int lig)
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
	if (ret != 0)
	{
		dm++;
		ft_greater_grid(grid, dm);
		ft_place_parts(grid, debut, dim);
	}
	return (dm);
}

void	ft_error_exit(char *str)
{
	ft_putstr(str);
	exit(1);
}

int				main(int argc, char **argv)
{
	int			list_size;
	int			fd;
	t_point		*debut;
	char		**grid;
	int			dim;

	debut = NULL;
	list_size = 0;
	if (argc != 2)
		ft_error_exit("usage: fillit input_file\n");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		ft_error_exit("error\n");
	debut = read_tetri(fd);
	if (debut == NULL)
		ft_error_exit("error\n");
	list_size = ft_list_size(debut);
	dim = ft_dim_grid(list_size);
	grid = ft_create_grid(dim);
	dim = ft_place_parts(&grid, debut, dim);
	ft_print_grid(grid, dim);
	return (0);
}
