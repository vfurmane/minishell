/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 14:05:14 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/26 14:17:37 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strndup(const char *str, int len)
{
	int		str_len;
	char	*new_str;

	str_len = ft_strlen(str);
	if (len > str_len)
		len = str_len;
	new_str = malloc(sizeof(*new_str) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	new_str = ft_memcpy(new_str, str, sizeof(*new_str) * len);
	new_str[len] = '\0';
	return (new_str);
}
