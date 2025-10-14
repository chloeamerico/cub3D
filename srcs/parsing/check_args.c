/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:59:25 by camerico          #+#    #+#             */
/*   Updated: 2025/10/14 14:22:23 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//verifie que ce n'est pas seulement .cub
static int	check_extension(char *arg)
{
	int	len;
	
	len = ft_strlen(arg);
	if(len < 5)
	{
		printf("Error : map sould have type <map.cub>\n");
		return(1);
	}
	if (ft_strcmp(arg + len - 4, ".cub") != 0)
	{
		printf("Error : map doesn't finish with a '.cub'\n");
		return(1);
	}
	return (0);
}

static int	check_file_exist(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if(fd == -1)
	{
		ft_printf("Error : opening the file %s\n", name);
		return (1);
	}
	close(fd);
	return (0);
}

int check_arg(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Error : number of arguments invalid\n");
		return (1);
	}
	if (check_extension(argv[1]))
		return (1);
	if (check_file_exist(argv[1]))
		return (1);
	return (0);
}