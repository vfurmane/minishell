/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:08:49 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/09 11:52:43 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int ft_unset(t_config *shell_c, char **args, int output_fd)
{
	int		i;

	(void)output_fd;
	i = 0;
	while (args[i])
		ft_write_pipe(DEL_ENV, args[i++], NULL, shell_c->fd[1]);
	return (0);
}
