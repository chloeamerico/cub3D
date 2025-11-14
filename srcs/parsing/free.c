/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:45:14 by camerico          #+#    #+#             */
/*   Updated: 2025/11/14 14:49:03 by lleichtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_char_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free (tab);
}

void	free_int_tab(int **tab, int h)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (i < h)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}