/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:18:50 by fl-hote           #+#    #+#             */
/*   Updated: 2022/11/22 17:18:50 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static t_mpt	**ft_create_map(t_var *fdf)
{
	int		i;
	t_mpt	**map;

	map = malloc(fdf->nb_col * sizeof(t_mpt *));
	if (!(map))
		return (NULL);
	i = -1;
	while (++i < fdf->nb_col)
	{
		map[i] = malloc(fdf->nb_lig * sizeof(t_mpt));
		if (!map[i])
			return (ft_free_map(map, i));
	}
	return (map);
}

static int	ft_fill_map(char *argv, t_var *fdf, t_mpt **map)
{
	char	**str;
	char	*line;
	t_mpt	p;

	fdf->fd = (open(argv, O_RDONLY));
	p.y = -1;
	while (++(p.y) < fdf->nb_lig)
	{
		line = get_next_line(fdf->fd);
		str = ft_split(line, ' ');
		free (line);
		p.x = -1;
		while (++(p.x) < fdf->nb_col)
		{
			p.z = ft_atoi(str[p.x]);
			if (!(p.z) && str[p.x][0] != '0')
				return (ft_free_splited(str));
			map[p.x][p.y].x = p.x;
			map[p.x][p.y].y = p.y;
			map[p.x][p.y].z = p.z;
		}
		ft_free_splited(str);
	}
	close(fdf->fd);
	return (1);
}

static int	ft_check_line(char *argv, t_var *fdf)
{
	int		fd;
	char	*line;

	fd = (open(argv, O_RDONLY));
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	fdf->nb_col = ft_count_w(line, ' ');
	while (1)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (fdf->nb_col != ft_count_w(line, ' ') || !(fdf->nb_col))
		{
			free(line);
			return (ft_putendl_fd("Wrong line length. Check map file.", 2, 0));
		}
	}
	if ((close(fd)) == -1)
		return (0);
	return (1);
}

/* Check if file exists, can be opened, not empty, no error on close */
static int	ft_check_file(char *argv, t_var *fdf)
{
	int		fd;
	char	*line;

	fd = (open(argv, O_RDONLY));
	if (fd == -1)
		return (ft_putendl_fd("Error opening file, or no file", 2, 0));
	if (ft_strncmp(ft_substr(argv, ft_strlen(argv) - 4, 4), ".fdf", 4))
		return (ft_putendl_fd("Wrong file extention (.fdf)", 2, 0));
	line = get_next_line(fd);
	if (!line)
		return (ft_putendl_fd("Empty map", 2, 0));
	fdf->nb_lig = 1;
	while (1)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		fdf->nb_lig += 1;
	}
	if ((close(fd)) == -1)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_var	*fdf;

	if (argc != 2)
		return (ft_putendl_fd
			("Wrong arguments count. Usage : ./fdf <filename>", 2, 1));
	fdf = malloc(sizeof(t_var));
	if (!fdf)
		return (1);
	if (!ft_check_file(argv[1], fdf))
		return (1);
	if (!ft_check_line(argv[1], fdf))
		return (1);
	if (fdf->nb_lig < 2 || fdf->nb_col < 2)
		return (ft_putendl_fd("Map too small (mini 2 x 2)", 2, 1));
	fdf->map = ft_create_map(fdf);
	if (!fdf->map)
		return (ft_putendl_fd("Unable to malloc map. Exiting...", 2, 1));
	ft_init_var(fdf);
	if (!ft_fill_map(argv[1], fdf, fdf->map))
		return (ft_putendl_fd("Wrong values in map (non numeric?).", 2, 1));
	return (ft_fdf(fdf));
}
