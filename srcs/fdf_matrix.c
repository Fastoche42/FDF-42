/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:20:31 by fl-hote           #+#    #+#             */
/*   Updated: 2022/11/22 17:20:31 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_pt	ft_matrix(t_var *fdf, int x, int y, int z)
{
	t_pt	pproj;

	pproj.x = (int)(fdf->zoom * (x * fdf->mtx[0][0] + y * fdf->mtx[1][0]
				+ z * fdf->mtx[2][0]));
	pproj.y = (int)(fdf->zoom * (x * fdf->mtx[0][1] + y * fdf->mtx[1][1]
				+ z * fdf->mtx[2][1]));
	return (pproj);
}

// isom 1 = isometric ; isom 0 = cavaliere
static void	ft_update_matrix(t_var *fdf)
{
	float	a;
	float	b;
	float	c;

	a = fdf->rotz;
	b = fdf->roty;
	c = fdf->rotx;
	if (fdf->isom)
	{
		fdf->mtx[0][0] = cos(b) * cos(a);
		fdf->mtx[1][0] = sin(c) * sin(b) * cos(a) - cos(c) * sin(a);
		fdf->mtx[2][0] = cos(c) * sin(b) * cos(a) + sin(c) * sin(a);
		fdf->mtx[0][1] = cos(b) * sin(a);
		fdf->mtx[1][1] = sin(c) * sin(b) * sin(a) + cos(c) * cos(a);
		fdf->mtx[2][1] = cos(c) * sin(b) * sin(a) - sin(c) * cos(a);
	}
	else
	{
		fdf->mtx[0][0] = 1;
		fdf->mtx[1][0] = -0.424264;
		fdf->mtx[2][0] = 0;
		fdf->mtx[0][1] = 0;
		fdf->mtx[1][1] = 0.424264;
		fdf->mtx[2][1] = 1;
	}
}

void	ft_fit_image(t_var *fdf)
{
	float	dx;
	float	dy;
	int		img_w;
	int		img_h;

	img_w = fdf->img->width;
	img_h = fdf->img->height;
	dx = (float)(fdf->draw_max.x - fdf->draw_min.x) / (float)img_w;
	dy = (float)(fdf->draw_max.y - fdf->draw_min.y) / (float)img_h;
	if (dx > dy)
		fdf->zoom /= dx;
	else
		fdf->zoom /= dy;
	fdf->zoom *= 0.9;
	fdf->offset.x = (img_w - fdf->draw_max.x - fdf->draw_min.x) / 2 ;
	fdf->offset.y = (img_h - fdf->draw_max.y - fdf->draw_min.y) / 2 ;
}

void	ft_find_lim(t_var *fdf, t_mpt **map)
{
	int		i;
	int		j;

	fdf->draw_min.x = INT_MAX;
	fdf->draw_min.y = INT_MAX;
	fdf->draw_max.x = INT_MIN;
	fdf->draw_max.y = INT_MIN;
	j = -1;
	while (++j < fdf->nb_lig)
	{
		i = -1;
		while (++i < fdf->nb_col)
		{
			if (map[i][j].x < fdf->draw_min.x)
				fdf->draw_min.x = map[i][j].x;
			if (map[i][j].x > fdf->draw_max.x)
				fdf->draw_max.x = map[i][j].x;
			if (map[i][j].y < fdf->draw_min.y)
				fdf->draw_min.y = map[i][j].y;
			if (map[i][j].y > fdf->draw_max.y)
				fdf->draw_max.y = map[i][j].y;
		}
	}
}

void	ft_fill_proj(t_var *fdf, t_mpt **map)
{
	int		x;
	int		y;
	int		z;
	t_pt	pproj;

	ft_update_matrix(fdf);
	y = -1;
	while (++y < fdf->nb_lig)
	{
		x = -1;
		while (++x < fdf->nb_col)
		{
			z = -fdf->deflat * map[x][y].z;
			pproj = ft_matrix(fdf, x, y, z);
			map[x][y].x = pproj.x;
			map[x][y].y = pproj.y;
		}
	}
}
