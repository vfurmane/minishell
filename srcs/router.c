/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:52:44 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/13 17:24:44 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_command_not_found(const char *command, int fd)
{
	write(fd, "minishell: ", 12);
	write(fd, command, ft_strlen(command));
	write(fd, ": command not found\n", 21);
}

void ft_kill_child(int id)
{
	kill(id, SIGINT);
}

int ft_route_command(const char *command, char **args, int fd[2], char **line, char **environment, int pipefd[2])
{
	int ret;
	int id;

	ret = 0;

	if (ft_strcmp("echo", command) == 0)
		ret = ft_echo(args, fd[1]);
	else if (ft_strcmp("cd", command) == 0)
		ret = ft_cd(args, fd[1]);
	else if (ft_strcmp("pwd", command) == 0)
		ret = ft_pwd(args, fd[1]);
	else if (ft_strcmp("export", command) == 0)
		ret = ft_export(args, fd[1], environment, pipefd);
	else if (ft_strcmp("unset", command) == 0)
		ret = ft_unset(args, fd[1], 1, environment, pipefd);
	else if (ft_strcmp("env", command) == 0)
		ret = ft_env(args, fd[1], environment);
	else if (ft_strcmp("exit", command) == 0)
		ret = ft_exit(args, fd[1]);
	else if (ft_strchr(command, '/'))
	{
		id = fork();
		if (id)
			wait(0);
		else
			ft_execve(line[0], line, NULL);
	}
	else
	{
		id = fork();
		if (id)
			wait(0);
		else if (!ft_exec(line, environment))
		{
			ft_command_not_found(command, fd[1]);
			exit(0);
		}
	}
	return (ret);
}
