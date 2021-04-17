/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:18 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/17 14:19:32 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void ft_sync_env_exp(char ***exp, char ***env)
// {
// int count[2];
// char **new_exp;
// 	//if (ft_strstrlen(*env) == ft_strstrlen(*exp))
// 	//return;
// 	count[0] = 0;
// 	while (*env[0])
// 	{
// 		if (!exp_in_it(*exp, *env[0]))
// 		{
// 			new_exp = malloc(sizeof(char **) * (ft_strstrlen(exp) + 1)); // need to protect the malloc
// 			*exp = new_exp;
// 		}
// 		count[0]++;
// 	}

// }

int main(int argc, char **argv, char **envp)
{
	int quit;
	int id;
	int status;
	int pipefd[2];
	char **environment;

	if (__APPLE__)
	{
		printf("\033[33mYou are using minishell on an Apple platform, some features may be unreliable.\033[0m\n");
	}
	(void)argc;
	(void)argv;
	environment = ft_strarrdup(envp);
	export_list = ft_strarrdup(envp);
	quit = 0;
	while (!quit)
	{
		pipe(pipefd);
		pipe(pipexport);
		id = fork();
		if (id)
		{
			signal(SIGINT, nothing);
			wait(&status);
			close(pipefd[1]);
			close(pipexport[1]);
			if (WEXITSTATUS(status) == S_SIGQUITSH)
				quit = 1;
			else if (WEXITSTATUS(status) == S_SIGUPENV)
			{
				ft_update_env(pipefd, &environment);
				ft_update_env(pipexport, &export_list);
			}
			signal(SIGINT, SIG_DFL);
			close(pipefd[0]);
			close(pipexport[0]);
		}
		else
		{
			close(pipefd[0]);
			close(pipexport[0]);
			if (ft_prompt(&quit, environment, pipefd) == -1)
				return (1);
			close(pipefd[1]);
			close(pipexport[1]);
			exit(0);
		}
	}
	return (0);
}
