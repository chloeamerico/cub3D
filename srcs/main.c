/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:59:37 by camerico          #+#    #+#             */
/*   Updated: 2025/10/21 17:11:14 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv, char **envp)
{
	t_game	game;
	
	if (!envp || !*envp)
		return (ft_printf("Error : There is no environment\n"), 1);
	if(check_arg(argc, argv))
		return(1);
	if(init_struct(&game, argv))
		return(1);
	if (divide_map_config(&game))
		return(free_tab(game.file_map), free(game.config), 1);
	if(parsing_map(&game))
		return(free_tab(game.file_map), free(game.config), free_tab(game.map), free(game.data), 1);
	free_tab(game.file_map);
	free(game.config);
	free_tab(game.map);
	free(game.data);
	return(0);
}