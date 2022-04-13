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

void	exit_error_path(char **check, t_link *list)
{
	if (check != NULL)
		free_split(check);
	write (STDERR, list->cmd[0], ft_strlen(list->cmd[0]));
	write (STDERR, ": command not found\n", 20);
	close (list->pipefd[1]);
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
	g_data->exit_code = 2;
	g_data->error = 1;
}

void	check_redirect_error(char *file)
{
	char	temp;

	if (file[0] == '\0')
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", STDERR);
		g_data->error = 1;
		g_data->exit_code = 2;
	}
	else
	{
		temp = file[0];
		if (temp == '|' || temp == '&' || temp == ';' || temp == '(' \
		|| temp == ')' || temp == '<' || temp == '>')
		{
			ft_putstr_fd("syntax error near unexpected token `", STDERR);
			ft_putchar_fd(temp, STDERR);
			ft_putstr_fd("'\n", STDERR);
			g_data->error = 1;
			g_data->exit_code = 2;
		}
	}
}

void	check_directory_error(char *file)
{
	if (file == NULL)
		return ;
	if (check_dir(file) == 1 && g_data->error == 0)
	{
		ft_putstr_fd(file, STDERR);
		ft_putstr_fd(": Is a directory\n", STDERR);
		g_data->error = 1;
		g_data->exit_code = 1;
	}
}
