/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpasqual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 08:39:27 by tpasqual          #+#    #+#             */
/*   Updated: 2016/12/22 11:46:52 by tpasqual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void			ft_error_exit(char *str)
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
	if (list_size > 26)
		ft_error_exit("error\n");
	grid = ft_create_grid(dim);
	dim = ft_place_parts(&grid, debut, dim);
	ft_print_grid(grid, dim);
	return (0);
}
