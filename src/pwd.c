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

	str = find_env("PWD");
	ft_putstr_fd(str, 1);
	write (1, "\n", 1);
	g_data->exit_code = 0;
	return ;
}
