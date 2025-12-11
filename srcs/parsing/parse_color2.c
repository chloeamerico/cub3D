/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:34:00 by camerico          #+#    #+#             */
/*   Updated: 2025/12/11 15:06:41 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_empty_or_whitespace(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	return (s[i] == '\0');
}

int	has_invalid_chars(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] < '0' || s[i] > '9') && s[i] != ' ' && s[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_cub_strlen(char *str)
{
	size_t	index;

	index = 0;
	if (!str)
		return (0);
	while (str[index] == ' ')
		index++;
	index = 0;
	while (str[index])
		index++;
	return (index);
}
