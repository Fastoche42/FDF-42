/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:11:07 by fl-hote           #+#    #+#             */
/*   Updated: 2022/11/22 17:11:07 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// 'Encodes' four individual bytes into an int.
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// Get the red channel.
int	get_r(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

// Get the green channel.
int	get_g(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

// Get the blue channel.
int	get_b(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

// Get the alpha channel.
int	get_a(int rgba)
{
	return (rgba & 0xFF);
}
