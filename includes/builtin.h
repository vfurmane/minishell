/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:25:10 by earnaud           #+#    #+#             */
/*   Updated: 2021/04/01 14:59:02 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"

int ft_echo(char **args, int fd);
int ft_cd(char **args, int fd);
int ft_pwd(char **args, int fd);
int ft_export(char **args, int fd);
int ft_unset(char **args, int fd);
int ft_env(char **args, int fd);
int ft_exit(char **args, int fd);
char *ft_convert_env(char *source);

#endif
