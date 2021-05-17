/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:18 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/17 16:12:21 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_shell(t_config *shell_c)
{
	void		*temp;
	int			i;

	i = 0;
	while (shell_c->envp[i])
		free(shell_c->envp[i++]);
	free(shell_c->envp);
	while (shell_c->envp_list)
	{
		temp = shell_c->envp_list->next;
		free(shell_c->envp_list->value);
		free(shell_c->envp_list->key);
		free(shell_c->envp_list);
		shell_c->envp_list = temp;
	}
	close(shell_c->fd[0]);
	close(shell_c->fd[1]);
	while (shell_c->history)
	{
		temp = shell_c->history->next;
		free(shell_c->history->content);
		free(shell_c->history);
		shell_c->history = temp;
	}
	//free(shell_c->prompt); maybe yes?
}

int			main(int argc, char **argv, char **envp)
{
	int			ret;
	int			status;
	t_config	shell_c;

	(void)argc; /* ===== DELETE ===== */
	(void)argv; /* ===== DELETE ===== */
	if (__APPLE__)
	{
		printf("\033[33mYou are using minishell on an Apple platform, "
				"some features may be unreliable.\033[0m\n");
	}
	if (tgetent(NULL, getenv("TERM")) == -1)
	{
		printf("\033[31mA very unforutnate error made the shell unusuable. "
				"Aborting...\033[0m\n");
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ft_parse_envp(envp, &shell_c);
	shell_c.quit = 0;
	shell_c.prompt = "$ ";
	shell_c.history = NULL;
	shell_c.exit_code = 0;
	while (!shell_c.quit)
	{
		tcgetattr(0, &shell_c.termios_backup);
		pipe(shell_c.fd);
		if (fork() != CHILD_PROCESS)
		{
			wait(&status);
			tcsetattr(0, 0, &shell_c.termios_backup);
			if (WEXITSTATUS(status) != S_SIGINT_PROMPT && WEXITSTATUS(status) != S_SIGIGN)
				shell_c.exit_code = WEXITSTATUS(status);
			ft_update_shell(&shell_c);
			if (WTERMSIG(status) == SIGINT)
			{
				write(STDOUT_FILENO, "^C", 2);
				write(1, "\n", 1);
			}
			else if (WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)\n", 19);
		}
		else
		{
			signal(SIGINT, SIG_DFL);
			ret = ft_prompt(&shell_c, shell_c.fd);
			if (ret == -1)
				return (1);
			exit(ret);
		}
	}
	ret = (int)shell_c.exit_code;
	free_shell(&shell_c);
	return (ret);
}