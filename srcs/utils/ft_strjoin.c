/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:10:43 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/30 16:20:42 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Minishell.h"

char *ft_strjoin(char const *s1, char const *s2)
{
	char *result;

	if (!(result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
		return (0);
	ft_strlcpy(result, s1, ft_strlen(s1) + 1);
	ft_strlcpy(result + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (result);
}