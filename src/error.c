/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:40:08 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/03/14 18:40:08 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_error_path(char **check, char **cmd)
{
	free_split(check);
	write (STDERR, cmd[0], ft_strlen(cmd[0]));
	write (STDERR, ": command not found\n", 20);
	free_all();
	exit (127);
}

void	invalid_syntax_error(char *cmd)
{	
	char	temp;

	temp = cmd[0];
	ft_putstr_fd("syntax error near unexpected token `", STDERR);
	ft_putchar_fd(temp, STDERR);
	ft_putstr_fd("'\n", STDERR);
	g_data->error = 1;
}
