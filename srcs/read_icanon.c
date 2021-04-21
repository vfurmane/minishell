/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_icanon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 09:07:52 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/21 10:26:31 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ctrl_d(int write_pipe, t_icanon *icanon)
{
	if (icanon->line_i == 0)
	{
		write(1, "exit\n", 5);
		write(write_pipe, EXIT_SHELL, 3);
		write(write_pipe, "\x1F\x1E", 2);
		return (0);
	}
	else if (icanon->column < icanon->line_i)
	{
		icanon->line_i = ft_delete_char(icanon->line, icanon->column + 1);
		tputs(clr_eol, 1, ft_putchar);
		return (1);
	}
	else
		tputs(bell, 1, ft_putchar);
	return (1);
}

int	ft_backspace(t_icanon *icanon)
{
	icanon->line_i = ft_delete_char(icanon->line, (icanon->column)--);
	tputs(tgoto(cursor_left, 0, 0), 1, ft_putchar);
	tputs(clr_eol, 1, ft_putchar);
	return (0);
}

int	ft_ctrl_l(char *line)
{
	tputs(save_cursor, 1, ft_putchar);
	tputs(clear_screen, 1, ft_putchar);
	write(1, "$ ", 2);
	write(1, line, ft_strlen(line));
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tgoto(row_address, 0, 0), 1, ft_putchar);
	return (0);
}

int	ft_escape_code(t_icanon *icanon)
{
	if (icanon->buffer[2] == 'D' && icanon->column > 0)
	{
		tputs(tgoto(cursor_left, 0, 0), 1, ft_putchar);
		(icanon->column)--;
	}
	else if (icanon->buffer[2] == 'C' && icanon->column < icanon->line_i)
	{
		tputs(tgoto(cursor_right, 0, 0), 1, ft_putchar);
		(icanon->column)++;
	}
	return (0);
}

int	ft_read_icanon(t_config *shell_c, t_icanon *icanon)
{
	int			ret;

	ret = 1;
	while (ret > 0 && icanon->line_i < ARG_MAX)
	{
		ret = read(0, icanon->buffer, 3);
		if (icanon->buffer[0] == 4)
			ret = ft_ctrl_d(shell_c->fd[1], icanon);
		else if (icanon->buffer[0] >= 32 && icanon->buffer[0] <= 126)
			icanon->line_i = ft_insert_char(icanon);
		else if (icanon->buffer[0] == 127 && icanon->column > 0)
			ft_backspace(icanon);
		else if (icanon->buffer[0] == '\f')
			ft_ctrl_l(icanon->line);
		else if (icanon->buffer[0] == '\n')
			ret = ft_putchar('\n') * 0;
		else if (icanon->buffer[0] == 27 && icanon->buffer[1] == 91)
			ft_escape_code(icanon);
		else
			tputs(bell, 1, ft_putchar);
		if (icanon->buffer[0] != '\n')
			ft_rewrite_line(icanon);
	}
	icanon->line[icanon->line_i] = '\0';
	return (0);
}
