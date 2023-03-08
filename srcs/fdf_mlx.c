/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:20:50 by fl-hote           #+#    #+#             */
/*   Updated: 2022/11/23 18:00:19 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	ft_hook2(t_var *fdf, int ok)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_F))
		ok = 1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_0))
	{
		fdf->rotx = 0;
		fdf->roty = 0;
		fdf->rotz = 0;
		ok = 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_5))
	{
		fdf->isom = 1;
		fdf->rotx = -M_PI / 4;
		fdf->roty = M_PI / 4;
		fdf->rotz = atan(1 / sqrt(3));
		ok = 1;
	}
	if (ok)
	{
		ft_find_lim(fdf, fdf->map);
		ft_fit_image(fdf);
		ft_redraw(fdf);
	}
}

static void	ft_hook(void *param)
{
	t_var	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_MULTIPLY))
	{
		fdf->deflat += INC_FLAT;
		ft_redraw(fdf);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_DIVIDE))
	{
		fdf->deflat -= INC_FLAT;
		ft_redraw(fdf);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_SUBTRACT))
	{
		fdf->zoom /= 1 + 0.01 * INC_ZOOM;
		ft_redraw(fdf);
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_ADD))
	{
		fdf->zoom *= 1 + 0.01 * INC_ZOOM;
		ft_redraw(fdf);
	}
	ft_hook2(fdf, 0);
}

static void	ft_scrollhook(double xdelta, double ydelta, void *param)
{
	t_var	*fdf;

	fdf = param;
	if (ydelta > 0)
	{
		fdf->zoom /= 1 + 0.01 * INC_ZOOM;
		ft_redraw(fdf);
	}
	else if (ydelta < 0)
	{
		fdf->zoom *= 1 + 0.01 * INC_ZOOM;
		ft_redraw(fdf);
	}
	(void)xdelta;
}

static void	ft_put_menu(t_var *fdf)
{
	mlx_put_string(fdf->mlx, "PAD + - (or WHEEL): ZOOM", 20, 20);
	mlx_put_string(fdf->mlx, "PAD 2-4 6-8 7-9   : ROTATE", 20, 40);
	mlx_put_string(fdf->mlx, "ARROWS   : MOVE", 20, 60);
	mlx_put_string(fdf->mlx, "PAD / *  : SCALE Z", 20, 80);
	mlx_put_string(fdf->mlx, "F1 - F8  : COLOR/BRIGHTNESS", 20, 100);
	mlx_put_string(fdf->mlx, "PAD 5    : ISOMETRIC", 20, 120);
	mlx_put_string(fdf->mlx, "PAD 0    : FLAT", 20, 140);
	mlx_put_string(fdf->mlx, "F        : FIT IN WINDOW", 20, 160);
	mlx_put_string(fdf->mlx, "C        : CAVAL PERSP", 20, 180);
}

int	ft_fdf(t_var *fdf)
{
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "42 Iron Wire, by Fastoche", false);
	if (!fdf->mlx)
		ft_error();
	fdf->img = mlx_new_image(fdf->mlx, WIDTH - 20, HEIGHT - 20);
	ft_put_menu(fdf);
	ft_fill_proj(fdf, fdf->map);
	ft_find_lim(fdf, fdf->map);
	ft_fit_image(fdf);
	ft_fill_proj(fdf, fdf->map);
	ft_find_lim(fdf, fdf->map);
	ft_fit_image(fdf);
	ft_draw_map(fdf, fdf->map);
	if (!fdf->img || (mlx_image_to_window(fdf->mlx, fdf->img, 10, 10) < 0))
		ft_error();
	mlx_loop_hook(fdf->mlx, ft_hook_mov, fdf);
	mlx_loop_hook(fdf->mlx, ft_hook_color, fdf);
	mlx_loop_hook(fdf->mlx, ft_hook_rotate, fdf);
	mlx_loop_hook(fdf->mlx, ft_hook, fdf);
	mlx_scroll_hook(fdf->mlx, &ft_scrollhook, fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	ft_free_map(fdf->map, fdf->nb_col);
	free(fdf);
	return (0);
}
