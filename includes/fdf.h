/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:21:31 by fl-hote           #+#    #+#             */
/*   Updated: 2022/11/22 17:21:31 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "struct.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define WIDTH 1024
# define HEIGHT 768
# define INC_ROT 1
# define INC_ZOOM 2
# define INC_MOVE 5
# define INC_FLAT 1
# define PREC 1000

/* colors */
int		get_rgba(int r, int g, int b, int a);
int		get_r(int rgba);
int		get_g(int rgba);
int		get_b(int rgba);
int		get_a(int rgba);

/* utils */
void	ft_init_var(t_var *fdf);
void	*ft_free_map(t_mpt **map, int i);
int		ft_free_splited(char **str);
t_pt	ft_mpt_to_pt(t_mpt p, t_pt offset);
void	ft_redraw(t_var *fdf);

/* matrix */
t_pt	ft_matrix(t_var *fdf, int x, int y, int z);
void	ft_fit_image(t_var *fdf);
void	ft_find_lim(t_var *fdf, t_mpt **map);
void	ft_fill_proj(t_var *fdf, t_mpt **map);

/* draw */
void	ft_draw_map(t_var *fdf, t_mpt **map);

/* hooks */
void	ft_hook_mov(void *param);
void	ft_hook_color(void *param);
void	ft_hook_rotate(void *param);
void	ft_error(void);

/* mlx */
int		ft_fdf(t_var *fdf);

#endif