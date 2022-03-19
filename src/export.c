/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:32:52 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/03/15 15:32:52 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_list(void)
{
	char	**sorted_env;
	int		i;
	int		j;

	i = -1;
	sorted_env = get_sorted_env();
	while (sorted_env[++i] != NULL)
	{
		j = -1;
		if (ft_isalpha(sorted_env[i][0]))
		{
			ft_putstr_fd("declare -x ", STDOUT);
			while (sorted_env[i][++j] != '=' && sorted_env[i][j] != '\0')
				ft_putchar_fd(sorted_env[i][j], STDOUT);
			if (sorted_env[i][j] == '=')
			{
				ft_putchar_fd('=', STDOUT);
				ft_putchar_fd('\"', STDOUT);
				ft_putstr_fd(sorted_env[i] + j + 1, STDOUT);
				ft_putchar_fd('\"', STDOUT);
			}
			ft_putchar_fd('\n', STDOUT);
		}
	}
	free_split (sorted_env);
}

void	export_add(char *var)
{
	int		size;
	int		i;
	char	**str;

	size = 0;
	i = -1;
	while (g_data->env[size] != NULL)
		size++;
	str = (char **) malloc (sizeof (char *) * size + 2);
	while (++i < size - 1)
		str[i] = ft_strdup(g_data->env[i]);
	str[i] = ft_strdup(var);
	i++;
	str[i] = ft_strdup(g_data->env[i - 1]);
	str[++i] = NULL;
	free_split (g_data->env);
	g_data->env = str;
}

void	do_export(char *var)
{
	int		i;
	char	*temp;

	i = 0;
	while (var[i] != '=' && var[i] != '\0')
		i++;
	temp = ft_substr(var, 0, i);
	if (ft_strchr(var, '=') != NULL && find_env(temp) != NULL)
		remove_from_env(temp);
	if (find_env(temp) == NULL)
		export_add(var);
	free (temp);
}

int	check_export_var(char *var)
{
	int	i;

	if (ft_isalpha(var[0]) == 0)
		return (0);
	i = -1;
	while (var[++i] != '\0' && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (0);
	}
	return (1);
}

void	export_built_in(char **cmd)
{
	int	i;

	i = 0;
	g_data->exit_code = 0;
	if (cmd[1] == NULL)
	{
		export_list();
		return ;
	}
	while (cmd[++i] != NULL)
	{
		if (check_export_var(cmd[i]))
			do_export(cmd[i]);
		else
		{
			ft_putstr_fd("export: `", STDERR);
			ft_putstr_fd(cmd[i], STDERR);
			ft_putstr_fd("\': not a valid identifier\n", STDERR);
			g_data->exit_code = 1;
		}
	}
}
