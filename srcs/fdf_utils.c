/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:21:05 by fl-hote           #+#    #+#             */
/*   Updated: 2022/11/23 17:35:30 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_init_var(t_var *fdf)
{
	fdf->isom = 1;
	fdf->rotx = -M_PI / 4;
	fdf->roty = M_PI / 4;
	fdf->rotz = atan(1 / sqrt(2));
	fdf->deflat = 1;
	fdf->zoom = 100;
	fdf->offset.x = 0;
	fdf->offset.y = 0;
	fdf->color = 0xFFFFFFAF;
}

t_pt	ft_mpt_to_pt(t_mpt p, t_pt offset)
{
	t_pt	p2;

	p2.x = p.x + offset.x;
	p2.y = p.y + offset.y;
	return (p2);
}

void	*ft_free_map(t_mpt **map, int i)
{
	while (--i >= 0)
		free (map[i]);
	free (map);
	return (NULL);
}

int	ft_free_splited(char **str)
{
	int	i;

	if (str)
	{
		i = -1;
		while (str[++i])
			free (str[i]);
		free (str);
	}
	return (0);
}

void	ft_redraw(t_var *fdf)
{
	mlx_delete_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH - 20, HEIGHT - 20);
	ft_fill_proj(fdf, fdf->map);
	ft_draw_map(fdf, fdf->map);
	if (!fdf->img || (mlx_image_to_window(fdf->mlx, fdf->img, 10, 10) < 0))
		ft_error();
}
