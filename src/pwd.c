/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:36:12 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/03/15 15:36:12 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_built_in(void)
{
	char	*str;

	g_data->exit_code = 0;
	str = malloc (1024);
	ft_putstr_fd(getcwd(str, 1024), STDOUT);
	write (1, "\n", 1);
	free (str);
	return ;
}
