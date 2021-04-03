/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:18 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/03 14:26:39 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	int		quit;

	quit = 0;
	signal(SIGINT, nothing);
	while (!quit)
	{
		if (ft_prompt(&quit) == -1)
			return (1);
	}
	return (0);
}
