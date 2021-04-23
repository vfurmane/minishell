/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:12:43 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/23 12:13:38 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int	ft_insert_char(t_icanon *icanon)
{
	int	i;

	i = ft_strlen(&icanon->line[icanon->column]) + 1;
	while (--i >= 0)
		icanon->line[icanon->column + i + 1] = icanon->line[icanon->column + i];
	icanon->line[(icanon->column)++] = icanon->buffer[0];
	ft_putchar(icanon->buffer[0]);
	return (ft_strlen(icanon->line));
}

int	ft_delete_char(char *str, int column)
{
	int	i;
	int	len;

	len = ft_strlen(&str[column]) + 1;
	column--;
	i = -1;
	while (++i < len)
		str[column + i] = str[column + i + 1];
	return (ft_strlen(str));
}

int	ft_backspace(t_icanon *icanon)
{
	icanon->line_i = ft_delete_char(icanon->line, (icanon->column)--);
	tputs(tgoto(cursor_left, 0, 0), 1, ft_putchar);
	tputs(clr_eol, 1, ft_putchar);
	return (0);
}

int	ft_rewrite_line(t_icanon *icanon, int move_cursor)
{
	int	i;

	i = icanon->column;
	tputs(save_cursor, 1, ft_putchar);
	while (i < icanon->line_i)
		ft_putchar(icanon->line[i++]);
	if (!move_cursor)
		tputs(restore_cursor, 1, ft_putchar);
	return (0);
}