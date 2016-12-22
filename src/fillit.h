/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpasqual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 08:39:27 by tpasqual          #+#    #+#             */
/*   Updated: 2016/12/22 09:23:24 by tpasqual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

typedef struct		s_point
{
	char			letter;
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	int				x3;
	int				y3;
	int				x4;
	int				y4;
	struct s_point	*prev;
	struct s_point	*next;
}					t_point;
t_point				*read_tetri(int fd);
int					ft_dim_grid(int list_size);
char				**ft_create_grid(int dim);
void				ft_print_grid(char **grid, int dim);
void				ft_greater_grid(char ***grid, int dim);
int					check_contigous(char *str);
int					check_counts(char *str, int count);
void				ft_set_tetra(t_point *points, int nbcar, int i, int y);
t_point				*ft_memo_tetra(char *str, char letter);
int					ft_sqrt(float a);
int					ft_list_size(t_point *debut);
void				ft_lstadd_point(t_point *point, t_point *debut);
t_point				*ft_process_a_tetra(int fd, int count, char *buf);
t_point				*read_tetri(int fd);
int					ft_check_borders(t_point *debut, int col, int lig, int dim);
int					ft_copy_part(char **grid, t_point *debut, int col, int lig);
int					ft_del_part(char **grid, t_point *debut, int col, int lig);
int					ft_insert_part(char **grid, t_point *debut, int dim);
int					ft_place_parts(char ***grid, t_point *debut, int dim);
void				ft_error_exit(char *str);
#endif
