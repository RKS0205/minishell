/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:40:01 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/03/14 18:40:01 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_built_in(t_link *list)
{
	if (ft_str_check(list->cmd[0], "echo"))
		return (1);
	else if (ft_str_check(list->cmd[0], "pwd"))
		return (1);
	else if (ft_str_check(list->cmd[0], "export"))
		return (1);
	else if (ft_str_check(list->cmd[0], "env"))
		return (1);
	else if (ft_str_check(list->cmd[0], "exit"))
		return (1);
	else if (ft_str_check(list->cmd[0], "unset"))
		return (1);
	else if (ft_str_check(list->cmd[0], "cd"))
		return (1);
	else
		return (0);
}

void	exec_built_in(t_link *list)
{
	open_file_input(list);
	open_file_output(list);
	if (ft_str_check(list->cmd[0], "echo"))
		echo_built_in(list->cmd);
	else if (ft_str_check(list->cmd[0], "pwd"))
		pwd_built_in();
	else if (ft_str_check(list->cmd[0], "export"))
		export_built_in(list->cmd);
	else if (ft_str_check(list->cmd[0], "env"))
		env_built_in(list->cmd);
	else if (ft_str_check(list->cmd[0], "exit"))
		exit_built_in(list->cmd);
	else if (ft_str_check(list->cmd[0], "unset"))
		unset_built_in(list->cmd);
	else if (ft_str_check(list->cmd[0], "cd"))
		cd_built_in(list->cmd);
	dup2(list->pipefd[0], STDIN);
	dup2(g_data->save_stdout, STDOUT);
	close(list->pipefd[0]);
	close(list->pipefd[1]);
}

void	child_command(t_link *list, char **env)
{
	close(list->pipefd[0]);
	open_file_input(list);
	open_file_output(list);
	list->path = get_path(list);
	execve(list->path, list->cmd, env);
	close(list->pipefd[1]);
	ft_putstr_fd("Error while executing\n", STDERR);
	free_all();
	exit (1);
}

void	parent_command(t_link *list)
{
	int	status;

	close(list->pipefd[1]);
	if (list->next != NULL)
	{
		dup2(list->pipefd[0], STDIN);
		waitpid(g_data->exec_pid, &status, 0);
		g_data->exit_code = WEXITSTATUS(status);
	}
	else
	{
		waitpid(g_data->exec_pid, &status, 0);
		g_data->exit_code = WEXITSTATUS(status);
	}
	close (list->pipefd[0]);
}

void	exec_command(t_link *list, char **env)
{
	if (pipe(list->pipefd) == -1)
		exit (-1);
	if (check_if_built_in(list))
		exec_built_in(list);
	else
	{
		g_data->exec_pid = fork();
		if (g_data->exec_pid == 0)
			child_command(list, env);
		else
			parent_command(list);
	}
}
