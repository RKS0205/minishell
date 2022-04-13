/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:39:32 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/03/23 15:39:32 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_built_in(char **cmd)
{
	int	status;

	g_data->exit = 1;
	write (1, "exit\n", 5);
	if (cmd[1] != NULL && ft_str_isnum(cmd[1]) == 0)
	{
		g_data->exit_code = 2;
		ft_putstr_fd("exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putstr_fd(": numeric argument required\n", STDERR);
	}
	else if (cmd[1] != NULL && cmd[2] != NULL)
	{
		g_data->exit_code = 1;
		ft_putstr_fd("exit: too many arguments\n", STDERR);
	}
	else if (cmd[1] != NULL && ft_str_isnum(cmd[1]) == 1)
		g_data->exit_code = ft_atoi(cmd[1]);
	status = g_data->exit_code;
	free_all();
	exit(status);
}
