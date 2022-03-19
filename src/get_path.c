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

char	*check_relative_absolute_paths(char *cmd)
{
	char	*rel_path;

	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	rel_path = ft_strjoin(find_env("PWD"), cmd);
	if (access(rel_path, F_OK | X_OK) == 0)
		return (rel_path);
	free (rel_path);
	return (NULL);
}

char	*get_path(t_link *list)
{
	int		i;
	char	*line;
	char	**check;
	char	*path;

	line = getenv("PATH");
	check = ft_split(line, ':');
	if (ft_str_check(list->cmd[0], ".") || ft_str_check(list->cmd[0], "/"))
		exit_error_path(check, list->cmd);
	i = -1;
	path = check_relative_absolute_paths(list->cmd[0]);
	if (path != NULL)
		return (path);
	while (check[++i] != NULL)
	{
		path = my_path_join(check[i], list->cmd[0]);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_split(check);
			return (path);
		}
		free(path);
	}
	exit_error_path(check, list->cmd);
	exit (127);
}
