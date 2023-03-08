/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:21:40 by fl-hote           #+#    #+#             */
/*   Updated: 2022/11/22 17:21:40 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_pt
{
	int		x;
	int		y;
}			t_pt;

typedef struct s_mpt
{
	int		x;
	int		y;
	int		z;
	int		red;
	int		green;
	int		blue;
}			t_mpt;

typedef struct s_var
{
	int			fd;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_mpt		**map;
	int			nb_lig;
	int			nb_col;
	float		rotx;
	float		roty;
	float		rotz;
	float		inc_x;
	float		inc_y;
	float		inc_z;
	int			isom;
	float		mtx[3][3];
	int			deflat;
	float		zoom;
	t_pt		offset;
	int			color;
	t_pt		draw_min;
	t_pt		draw_max;
}				t_var;

#endif
