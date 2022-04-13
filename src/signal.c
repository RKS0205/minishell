/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:36:02 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/03/15 15:36:02 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	kill_loop(int signum)
{
	(void)signum;
	if (g_data->here_doc == 1)
	{
		close (STDIN);
		g_data->error = 1;
	}
	if (g_data->exec_pid != 0 && g_data->in_exec == 1)
	{
		kill(g_data->exec_pid, SIGKILL);
		write (1, "\n", 1);
	}
	if (g_data->in_exec == 0)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_data->exit_code = 130;
}

void	quit_core(int signum)
{
	(void)signum;
	if (g_data->exec_pid != 0 && g_data->in_exec == 1)
	{
		kill(g_data->exec_pid, SIGKILL);
		ft_putstr_fd("Quit (Core dumped)\n", 1);
	}
}
