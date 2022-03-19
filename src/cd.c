/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:34:03 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/03/16 16:34:03 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_to_oldpwd(void)
{
	chdir(find_env("OLDPWD"));
	ft_putstr_fd(find_env("OLDPWD"), STDOUT);
	write (1, "\n", 1);
}

void	change_pwd(char *cmd)
{
	char	*buf;
	char	*old_pwd;
	char	*cwd;

	buf = ft_my_strjoin(ft_strdup(find_env("PATH")), cmd);
	old_pwd = ft_my_strjoin(ft_strdup("OLDPWD="), find_env("PWD"));
	getcwd(buf, ft_strlen(buf));
	cwd = ft_my_strjoin(ft_strdup("PWD="), buf);
	do_export(cwd);
	do_export(old_pwd);
	free (cwd);
	free (old_pwd);
	free (buf);
}

void	cd_built_in(char **cmd)
{
	if (cmd[1] == NULL || ft_str_check(cmd[1], "~"))
	{
		chdir (find_env("HOME"));
		change_pwd(find_env("HOME"));
		return ;
	}
	else if (cmd[2] != NULL)
		ft_putstr_fd("cd: too many arguments\n", STDERR);
	else
	{
		if (ft_str_check(cmd[1], "-"))
			cd_to_oldpwd();
		else if (ft_str_check(cmd[1], ".."))
			chdir(cmd[1]);
		else if (access(cmd[1], F_OK) == 0)
			chdir(cmd[1]);
		else
		{
			ft_putstr_fd("cd: ", STDERR);
			ft_putstr_fd(cmd[1], STDERR);
			ft_putstr_fd(": No such file or directory\n", STDERR);
		}
		change_pwd(cmd[1]);
		return ;
	}
}
