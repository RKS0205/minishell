/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:37:57 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/03/23 15:37:57 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_cmd_count(char *s, int n, int count)
{
	char	quote;

	while (s[n] != '\0')
	{
		while (s[n] == ' ')
			n++;
		while (s[n] != ' ' && s[n] != '\0')
		{
			if (s[n] == '\"' || s[n] == '\'')
			{
				quote = s[n];
				n++;
				while (s[n] != quote && s[n] != '\0')
					n++;
				if (s[n] == quote)
					n++;
			}
			else
				n++;
		}
		count++;
	}
	return (count);
}

static void	do_cmd_split(char	*s, char **matriz, int n, int strcount)
{
	char	quote;

	while (s[n] != '\0')
	{
		while (s[n] == ' ')
			n++;
		matriz[strcount] = ft_strdup("\0");
		while (s[n] != ' ' && s[n] != '\0')
		{
			if (s[n] == '\"' || s[n] == '\'')
			{
				quote = s[n];
				n++;
				while (s[n] != quote && s[n] != '\0')
					matriz[strcount] = ft_my_charjoin(matriz[strcount], s[n++]);
				if (s[n] == quote)
					n++;
			}
			else
				matriz[strcount] = ft_my_charjoin(matriz[strcount], s[n++]);
		}
		strcount++;
	}
}

char	**cmd_split(char *s)
{
	char	**ret;
	char	*str;
	int		size;

	str = ft_strtrim(s, " ");
	if (str == NULL)
		return (NULL);
	size = get_cmd_count(str, 0, 0);
	ret = (char **) malloc (sizeof(char *) * (size + 1));
	if (ret == NULL)
		return (NULL);
	do_cmd_split(str, ret, 0, 0);
	if (ret[0] == NULL)
		return (NULL);
	ret[get_cmd_count(str, 0, 0)] = NULL;
	free (str);
	return (ret);
}
