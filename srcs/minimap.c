/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:41:55 by camerico          #+#    #+#             */
/*   Updated: 2025/11/04 16:45:29 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//a appeler 1 fois au debut
void init_struct_minimap(t_game *game)
{
	game->mini = malloc(sizeof(t_minimap));
	if(!game->mini)
		return(1);
	game->mini->case_size = 10; //-> chaque case = 10px
	game->mini->width = game->data->map_width * game->mini->case_size;
	game->mini->height = game->data->map_height * game->mini->case_size;
	game->mini->location_x = 20;
	game->mini->location_y = 20;
	// game->mini->scale = 5;
}


void final_minimap(t_game *game)
{
	t_data_mini	img;

	if(!create_minimap_img(game, &img))
}

//dessine le fond de la minimap avec un fond semi transparent


