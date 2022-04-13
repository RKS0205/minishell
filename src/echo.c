/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:39:56 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/03/23 15:39:56 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_built_in(char **cmd)
{
	int	i;

	i = 1;
	if (cmd[1] == NULL)
		write (1, "\n", 1);
	else
	{
		if (ft_str_check(cmd[1], "-n"))
			i++;
		while (cmd[i] != NULL)
		{
			if (cmd[i][0] != '\0')
				ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1] != NULL)
				write (1, " ", 1);
			i++;
		}
		if ((ft_str_check(cmd[1], "-n")) == 0)
			write (1, "\n", 1);
	}
	g_data->exit_code = 0;
	return ;
}
