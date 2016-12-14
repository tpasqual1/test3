/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpasqual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 08:39:27 by tpasqual          #+#    #+#             */
/*   Updated: 2016/12/14 18:14:45 by tpasqual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <fcntl.h>
#include "fillit.h"
#include "libft.h"


// Checks if we have 6 or 8 connections to validate the tetrimino

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

	i = 1;
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

	if (!tmp)
		ft_putstr("kokoko");
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
			grid[i][j] = 'A';
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

int		ft_fit_place(t_point *debut, char *grid, int i, int j)
{
	if (debut->x2 + i >=0 && debut->x3 + i > 0 && debut->x4  + i > 0)
		if (debut->y2 + y <= dim  && debut->x3 + i > 0 && debut->x4  + i > 0)
		


}
                                                                                                                  	
int		ft_is_place();
{
	int		i;
	int		j;
	int		ret;

	i = 0;
	j = 0;
	while (i < dim)
	{	
		while (j < dim)
		{	   
			if (new_grid[i][j] = '.')
			{
				res = ft_fit_place(debut, new_grid, i, j);
				if (res == 0)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
void	ft_fill_grid(char **grid, t_point *debut, int dim)
{
	char	**new_grid;
	int		ret;

	while (debut->next)
	{	
		ret = ft_is_place();	
		debut = debut->next;
	}
	new_grid = ft_greater_grid(grid, dim + 1);
	ft_putstr("---------------------\n");
	ft_print_grid(new_grid, dim + 1);
		
//	}	
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
	ft_print_list(debut);
	list_size = ft_list_size(debut);
	dim = ft_dim_grid(list_size);
	grid = ft_create_grid(dim);
	ft_print_grid(grid, dim);
	ft_fill_grid(grid, debut, dim);
	return (0);
}

