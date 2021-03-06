/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 11:21:53 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/28 13:37:12 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_route_argchr(t_config *shell_c, t_cmd_arg *arg, const char *cmd)
{
	int		i;
	int		ret;
	char	*env_variable;

	i = 0;
	if (arg->backslash)
		(arg->i)++;
	else if (cmd[0] == '\'' || cmd[0] == '"')
		arg->quote = ft_set_quote(arg, cmd[0]);
	else if (cmd[0] == '$')
	{
		ret = ft_replace_dollar(shell_c, &env_variable, &cmd[1]);
		if (ret == -1)
			return (-1);
		i += ret;
		arg->i += ft_strlen(env_variable);
	}
	else
		(arg->i)++;
	return (i);
}

int	ft_arglen(t_config *shell_c, const char *cmd)
{
	int			i;
	int			ret;
	t_cmd_arg	arg;

	i = 0;
	ft_bzero(&arg, sizeof(arg));
	while (cmd[i] && (cmd[i] != ' ' || arg.quote != '\0'))
	{
		if (!arg.backslash && cmd[i] == '\\' && (arg.quote == '\0'
				|| (cmd[i + 1] != '\0' && arg.quote == cmd[i + 1])))
		{
			arg.backslash = cmd[i++] == '\\';
			continue ;
		}
		ret = ft_route_argchr(shell_c, &arg, &cmd[i]);
		if (ret == -1)
			return (-1);
		i += ret;
		i++;
		arg.backslash = 0;
	}
	return (arg.i);
}
