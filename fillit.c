/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpasqual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 08:39:27 by tpasqual          #+#    #+#             */
/*   Updated: 2016/12/16 17:53:27 by tpasqual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <fcntl.h>
#include "fillit.h"
#include "libft.h"


// Checks if we have 6 or 8 connections to validate the tetrimino

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

// Check characters counter to validate the piece.

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
	if (count == 21 && str[20] != '\n')
		return (-1);
	if (!check_contigous(str))
		return (-1);
	return (0);
}

t_point	*ft_memo_tetra(char *str, char letter) 
{
	int			i;
	int			nbcar;
	int			mx;
	int			my;
	int			x;	
	int			y;
	t_point		*points;
	//	t_listf		*listf;

	i = 0;
	y = 0;
	my = 0;
	nbcar = 1;
	points = malloc(sizeof(t_point));
	while (i < 21)		
	{  
		if (str[i] == '#')
		{
			if (nbcar == 1)
			{
				points->x1 = 0;
				points->y1 = 0;
				mx = i % 5;
				my = y;
			}
			if (nbcar == 2)
			{
				points->x2 = (i % 5) - mx;
				points->y2 = y - my;
			}			
			if (nbcar == 3)
			{
				points->x3 = (i % 5) - mx;
				points->y3 = y - my;
			}			
			if (nbcar == 4)
			{
				points->x4 = (i % 5) - mx;
				points->y4 = y - my;
			}			
			nbcar++;
		}
		else if (str[i] == '\n')
			y++;
		i++;
	}
	points->next = NULL;
	points->letter = letter ;
	return (points);
}

int		ft_sqrt(float a)
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

void	ft_lstadd_point(t_point *point, t_point *debut)
{
	while (debut->next != NULL)
	{
		debut = debut->next;
	}
	debut->next = point;
}

// Read tetriminos and fill in  a list.

t_point	*read_tetri(int fd)
{
	char		*buf;
	int			count;
	int			res_count;
	int			letter;
	t_point		*debut;
	t_point		*point;

	debut = NULL;
	letter = 65;
	buf = ft_strnew(21);
	count = read(fd, buf, 21);
	while (count >= 20)
	{
		if (check_counts(buf, count) != 0)
			return (NULL);
		//On a ici un tetraminos valide a stocker dans une liste 
		point = ft_memo_tetra(buf, letter);	
		if (debut == NULL)
			debut = point;
		else
			ft_lstadd_point(point, debut);
		count = read(fd, buf, 21);
		letter++;
	}
	return (debut);
}

void	ft_print_list(t_point *tmp)
{
	t_point	*point;

	while (tmp->next != NULL)
	{
		point = tmp;
		ft_putchar(point->letter);
		ft_putchar('\n');
		ft_putnbr(point->x1);
		ft_putchar(',');
		ft_putnbr(point->y1);
		ft_putchar('\n');
		ft_putnbr(point->x2);
		ft_putchar(',');
		ft_putnbr(point->y2);
		ft_putchar('\n');
		ft_putnbr(point->x3);
		ft_putchar(',');
		ft_putnbr(point->y3);
		ft_putchar('\n');
		ft_putnbr(point->x4);
		ft_putchar(',');
		ft_putnbr(point->y4);
		ft_putchar('\n');
		tmp = tmp->next;
	}
	point = tmp;
	ft_putchar(point->letter);
	ft_putchar('\n');
	ft_putnbr(point->x1);
	ft_putchar(',');
	ft_putnbr(point->y1);
	ft_putchar('\n');
	ft_putnbr(point->x2);
	ft_putchar(',');
	ft_putnbr(point->y2);
	ft_putchar('\n');
	ft_putnbr(point->x3);
	ft_putchar(',');
	ft_putnbr(point->y3);
	ft_putchar('\n');
	ft_putnbr(point->x4);
	ft_putchar(',');
	ft_putnbr(point->y4);
	ft_putchar('\n');
}

int		ft_dim_grid(int list_size)
{
	return(ft_sqrt(list_size * 4) + 1);
}

char	**ft_create_grid(int dim)
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

void	ft_print_grid(char **grid, int dim)
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

char 	**ft_greater_grid(char **grid, int dim)
{
	char	**new_grid;
	int i;

	i = 0;
	new_grid = (char **)malloc(sizeof(char *) * dim);
	while (i < dim)
	{
		new_grid[i] = (char *)malloc(sizeof(char) * dim);
		ft_memset(new_grid[i], 46, dim);
		i++;
	}
	i = 0;	
	while (i < dim -1)
	{
		ft_memcpy(new_grid[i], grid[i], dim - 1);
		i++;
	}
	return(new_grid);
}

int		ft_check_borders(t_point *debut, int col, int lig, int dim)
{
	int		ret;

	//ft_putchar('@');ft_putnbr(col);ft_putnbr(lig);ft_putchar('\n');
	if (col + debut->x2 < 0 || col + debut->x3 < 0 || col + debut->x4 < 0)
		return (1);
	if (col + debut->x2 > dim || col + debut->x3 > dim || col + debut->x4 > dim)
		return (2);
	if (lig + debut->y2 > dim || lig + debut->y3 > dim || lig + debut->y4 > dim)
		return (3);
	//return (0):  les coordonnees de la piece sont dans les limites de grid
	return (0);
}

int 	ft_insert_part(char **grid, t_point *debut, int dim)
{
	int		col;
	int		lig;
	int		ret;

	col = 0;
	lig = 0;
	ret = 1;
	while (lig < dim)
	{
		while (col < dim)
		{
			//ft_putchar('=');ft_putnbr(col);ft_putnbr(lig);ft_putchar('\n');
			if(grid[lig][col] == '.')
			{
				ret = ft_check_borders(debut, col, lig, dim);
	//			ft_putstr("Retour check_border: ");ft_putnbr(ret);ft_putchar('\n');
				// si ret = 0 : on peut tester si les cases de la grid correspondant au xi, yj sont libres.
				if (ret == 0)
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
			}
			col++;
		}
		col = 0;
		lig++;
	}	
	return (1);
}

void 	ft_place_parts(char **grid, t_point *debut, int dim)
{
	int		ret;
	char	**new_grid;

	while (debut->next != NULL)	
	{	
		ret = ft_insert_part(grid, debut, dim);

		debut = debut->next;
	}
	ret = ft_insert_part(grid, debut, dim);
	if (ret == 1)
	{
		new_grid = ft_greater_grid(grid, dim + 1);
		free(*grid);
		*grid = *new_grid;
		ret = ft_insert_part(grid, debut, dim + 1);
	}
}

int		main(int argc, char **argv)
{
	int			list_size;
	int			fd;
	t_point		*debut;
	char		**grid;
	int			dim;

	debut = NULL;
	list_size = 0;
	
	if (argc != 2)
	{
		ft_putstr("usage: fillit input_file\n");
		return (1);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_putstr("error\n");
		return (1);
	}
	debut = read_tetri(fd);
	if (debut == NULL)
	{
		ft_putstr("error\n");
		return (1);
	}
	//ft_print_list(debut);
	list_size = ft_list_size(debut);
	dim = ft_dim_grid(list_size);
	grid = ft_create_grid(dim);
	dim--;
	ft_putnbr_bn(dim);
	ft_place_parts(grid, debut, dim);
	ft_putchar('\n');
	ft_print_grid(grid, dim + 1);
	return (0);
}
