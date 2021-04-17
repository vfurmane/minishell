/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:06:11 by earnaud           #+#    #+#             */
/*   Updated: 2021/04/17 14:17:48 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *str)
{
	char *result;

	result = malloc(sizeof(*str) * (ft_strlen(str) + 1));
	ft_strlcpy(result, str, ft_strlen(str) + 1);
	return (result);
}
