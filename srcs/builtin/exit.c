/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:09:19 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/26 13:32:30 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_exit(t_config *shell_c, char **args, int output_fd)
{
	(void)args;
	write(output_fd, "exit\n", 5);
	ft_write_pipe(EXIT_SHELL, NULL, NULL, shell_c->fd[1]);
	return (0);
}
