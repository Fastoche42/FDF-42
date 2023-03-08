/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:11:26 by fl-hote           #+#    #+#             */
/*   Updated: 2022/11/22 17:11:26 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	ft_put_pixel(t_var *fdf, int x, int y, int rev)
{
	if (rev)
	{
		if (y >= 0 && x >= 0 && y < (int)fdf->img->width
			&& x < (int)fdf->img->height)
			mlx_put_pixel(fdf->img, y, x, fdf->color);
	}
	else
	{
		if (x >= 0 && y >= 0 && x < (int)fdf->img->width
			&& y < (int)fdf->img->height)
			mlx_put_pixel(fdf->img, x, y, fdf->color);
	}
}

static int	ft_check_reverse(t_pt *e, t_pt *p1, t_pt *p2)
{
	int	rev;
	int	buffer;

	rev = (e->x < e->y);
	if (rev)
	{
		buffer = e->x;
		e->x = e->y;
		e->y = buffer;
		buffer = p1->x;
		p1->x = p1->y;
		p1->y = buffer;
		buffer = p2->x;
		p2->x = p2->y;
		p2->y = buffer;
	}
	return (rev);
}

static void	ft_draw_line(t_var *fdf, t_pt p1, t_pt p2)
{
	t_pt	e;
	t_pt	delta;
	int		i;
	t_pt	incr;
	int		rev;

	e.x = abs(p2.x - p1.x);
	e.y = abs(p2.y - p1.y);
	rev = ft_check_reverse(&e, &p1, &p2);
	delta = e;
	incr.x = 1 - 2 * (p1.x > p2.x);
	incr.y = 1 - 2 * (p1.y > p2.y);
	i = -1;
	while (++i <= delta.x)
	{
		ft_put_pixel(fdf, p1.x, p1.y, rev);
		p1.x += incr.x;
		e.x -= 2 * delta.y;
		if (e.x < 0)
		{
			p1.y += incr.y;
			e.x += 2 * delta.x;
		}
	}
}

/* draw all lines and all columns */
void	ft_draw_map(t_var *fdf, t_mpt **map)
{
	int		i;
	int		j;
	t_pt	p1;
	t_pt	p2;

	j = -1;
	while (++j < fdf->nb_lig)
	{
		i = -1;
		while (++i < fdf->nb_col)
		{
			p1 = ft_mpt_to_pt(map[i][j], fdf->offset);
			if (i < fdf->nb_col - 1)
			{
				p2 = ft_mpt_to_pt(map[i + 1][j], fdf->offset);
				ft_draw_line(fdf, p1, p2);
			}
			if (j < fdf->nb_lig - 1)
			{
				p2 = ft_mpt_to_pt(map[i][j + 1], fdf->offset);
				ft_draw_line(fdf, p1, p2);
			}
		}
	}
}
