/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:40:04 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/03/14 18:40:04 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_first_env(char **env)
{
	char	**ret;
	int		i;
	int		n;

	i = -1;
	n = 0;
	while (env[++i] != NULL)
	{
		if (ft_strnstr(env[i], "WORKSPACE", ft_strlen(env[i])) == NULL)
			n++;
	}
	ret = (char **) malloc (sizeof(char *) * (n + 1));
	n = -1;
	i = 0;
	while (env[++n] != NULL)
	{
		if (ft_strnstr(env[n], "WORKSPACE", ft_strlen(env[n])) == NULL)
			ret[i++] = ft_strdup(env[n]);
	}
	ret[i] = NULL;
	return (ret);
}

char	**copy_env(char **env)
{
	char	**ret;
	int		i;
	int		n;

	i = 0;
	n = -1;
	while (env[i] != NULL)
		i++;
	ret = (char **) malloc (sizeof(char *) * (i + 1));
	while (env[++n] != NULL)
		ret[n] = ft_strdup(env[n]);
	ret[n] = NULL;
	return (ret);
}

char	*find_env(char *var)
{
	int		i;

	i = 0;
	while (g_data->env[i] != NULL)
	{
		if (ft_strncmp(var, g_data->env[i], ft_strlen(var)) == 0 \
		&& (g_data->env[i][ft_strlen(var)] == '=' \
		|| g_data->env[i][ft_strlen(var)] == '\0'))
		{
			if (g_data->env[i][ft_strlen(var)] == '=')
				return (g_data->env[i] + ft_strlen(var) + 1);
			else
				return ("\0");
		}
		i++;
	}
	return (NULL);
}

char	**get_sorted_env(void)
{
	int		env_size;
	char	**env;
	int		i;
	char	*temp;

	env = copy_env(g_data->env);
	env_size = 0;
	while (env[env_size] != NULL)
		env_size++;
	while (env_size > 0)
	{
		i = 0;
		while (i < env_size - 1)
		{
			if (ft_strncmp(env[i], env[i + 1], ft_strlen(env[i])) > 0)
			{
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
			}
			i++;
		}
		env_size--;
	}
	return (env);
}

void	env_built_in(char **cmd)
{
	int	i;

	if (cmd[1] != NULL)
	{
		ft_putstr_fd("env: too many arguments\n", STDERR);
		g_data->exit_code = 1;
		return ;
	}
	else
	{
		i = -1;
		while (g_data->env[++i] != NULL)
		{
			if (ft_strchr(g_data->env[i], '=') != NULL)
				printf ("%s\n", g_data->env[i]);
		}
		g_data->exit_code = 0;
		return ;
	}
}
