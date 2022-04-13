/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 19:21:30 by rkenji-s          #+#    #+#             */
/*   Updated: 2021/12/19 19:21:30 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_path_join(char const *s1, char const *s2)
{
	char	*s;
	int		count;
	int		count2;

	count = 0;
	count2 = 0;
	s = malloc ((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (s == NULL)
		return (NULL);
	while (s1[count] != '\0')
	{
		s[count] = s1[count];
		count++;
	}
	s[count++] = '/';
	while (s2[count2] != '\0')
		s[count++] = s2[count2++];
	s[count] = '\0';
	return (s);
}

int	check_dir(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

char	*check_relative_absolute_paths(char *cmd)
{
	char	*rel_path;

	if (cmd[0] == '\0')
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0 && check_dir(cmd) == 0)
		return (cmd);
	if (find_env("PWD") == NULL)
		return (NULL);
	rel_path = ft_strjoin(find_env("PWD"), cmd);
	if (access(rel_path, F_OK | X_OK) == 0 && check_dir(rel_path) == 0)
		return (rel_path);
	check_directory_error(cmd);
	check_directory_error(rel_path);
	if (g_data->error == 1)
	{
		free (rel_path);
		free_all();
		exit (126);
	}
	free (rel_path);
	return (NULL);
}

char	*get_path(t_link *list)
{
	int		i;
	char	**check;
	char	*path;

	i = -1;
	path = check_relative_absolute_paths(list->cmd[0]);
	if (path != NULL)
		return (path);
	if (find_env("PATH") == NULL || list->cmd[0][0] == '\0')
		exit_error_path(NULL, list);
	check = ft_split(find_env("PATH"), ':');
	while (check[++i] != NULL)
	{
		path = my_path_join(check[i], list->cmd[0]);
		if (access(path, F_OK | X_OK) == 0 && check_dir(path) == 0)
		{
			free_split(check);
			return (path);
		}
		free(path);
	}
	exit_error_path(check, list);
	exit (127);
}
