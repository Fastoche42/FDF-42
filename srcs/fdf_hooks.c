/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:20:50 by fl-hote           #+#    #+#             */
/*   Updated: 2022/11/22 21:45:05 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_hook_mov(void *param)
{
	t_var	*fdf;
	int		inc_mx;
	int		inc_my;

	fdf = param;
	inc_mx = 0;
	inc_my = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_C))
		fdf->isom = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		inc_mx = -INC_MOVE;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		inc_mx = INC_MOVE;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		inc_my = -INC_MOVE;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		inc_my = INC_MOVE;
	if (inc_mx || inc_my)
	{
		fdf->offset.x += inc_mx;
		fdf->offset.y += inc_my;
		ft_redraw(fdf);
	}
}

static void	ft_set_color(t_var *fdf, int new)
{
	fdf->color += new;
	ft_redraw(fdf);
}

void	ft_hook_color(void *param)
{
	t_var	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_F1))
		ft_set_color(fdf, 1 << 24);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_F2))
		ft_set_color(fdf, -(1 << 24));
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_F3))
		ft_set_color(fdf, 1 << 16);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_F4))
		ft_set_color(fdf, -(1 << 16));
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_F5))
		ft_set_color(fdf, 1 << 8);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_F6))
		ft_set_color(fdf, -(1 << 8));
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_F7))
		ft_set_color(fdf, 1);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_F8))
		ft_set_color(fdf, -1);
}

void	ft_hook_rotate(void *param)
{
	t_var	*fdf;

	fdf = param;
	fdf->inc_x = 0;
	fdf->inc_y = 0;
	fdf->inc_z = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_4))
		fdf->inc_y = M_PI / 360 * INC_ROT;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_6))
		fdf->inc_y = -M_PI / 360 * INC_ROT;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_2))
		fdf->inc_x = -M_PI / 360 * INC_ROT;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_8))
		fdf->inc_x = M_PI / 360 * INC_ROT;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_7))
		fdf->inc_z = -M_PI / 360 * INC_ROT;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_9))
		fdf->inc_z = M_PI / 360 * INC_ROT;
	if (fdf->inc_x || fdf->inc_y || fdf->inc_z)
	{
		fdf->rotx += fdf->inc_x;
		fdf->roty += fdf->inc_y;
		fdf->rotz += fdf->inc_z;
		ft_redraw(fdf);
	}
}

// Exit the program as failure.
void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}
