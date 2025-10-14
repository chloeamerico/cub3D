/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:59:37 by camerico          #+#    #+#             */
/*   Updated: 2025/10/14 14:12:07 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv, char **envp)
{
	if (!envp || !*envp)
		return (ft_printf("Error : There is no environment\n"), 1);
	if(check_arg(argc, argv))
		return(1);
	return(0);
}