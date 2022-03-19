/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_conditionals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:47:09 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/03/16 16:47:09 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_redirect_error(char *file)
{
	char	temp;

	if (file == NULL)
		return ;
	if (file[0] == '\0')
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", STDERR);
		g_data->error = 1;
	}
	else
	{
		temp = file[0];
		if (temp == '|' || temp == '&' || temp == ';' || temp == '(' \
		|| temp == ')' || temp == '<' || temp == '>')
		{
			ft_putstr_fd("syntax error near unexpected token `", STDERR);
			ft_putchar_fd(temp, STDERR);
			ft_putstr_fd("'\n", STDERR);
			g_data->error = 1;
		}
	}
}

int	parse_variables(char *cmd, char **line)
{
	int		i;
	int		start;
	char	*var;
	char	*env;

	i = 1;
	start = 1;
	if (cmd[1] == '?')
		*line = ft_my_strjoin(*line, ft_itoa(g_data->exit_code));
	else
	{
		if (ft_isdigit(cmd[1]))
			return (2);
		while (ft_isalnum(cmd[i]))
			i++;
		var = ft_substr(cmd, start, i - start);
		if (var != NULL)
		{
			env = find_env(var);
			if (env != NULL)
				*line = ft_my_strjoin(*line, env);
		}
		return (i);
	}
	return (2);
}

int	parse_quotes(char *cmd, char **line, char quote)
{
	int	i;

	i = 1;
	*line = ft_my_charjoin(*line, cmd[0]);
	while (cmd[i] != quote && cmd[i] != '\0')
	{
		if (quote == '\"' && cmd[i] == '$' && (ft_isalnum(cmd[i + 1]) || \
		cmd[i + 1] == '?'))
			i += parse_variables(cmd + i, &(*line));
		*line = ft_my_charjoin(*line, cmd[i]);
		i++;
	}
	if (cmd[i] == '\0')
	{
		write (STDERR, "Error: unclosed quotes\n", 24);
		g_data->error = 1;
	}
	return (i);
}

int	parse_redirects(char *cmd, t_link *new, char operator)
{
	int	start;
	int	i;

	i = 0;
	while (cmd[i] == ' ' || (cmd[i] == operator && i < 2))
		i++;
	start = i;
	while (cmd[i] != ' ' && cmd[i] != '\0')
		i++;
	if (operator == '<')
	{
		new->file_in = ft_substr(cmd, start, i - start);
		check_redirect_error(new->file_in);
	}
	else if (operator == '>')
	{
		new->file_out = ft_substr(cmd, start, i - start);
		check_redirect_error(new->file_out);
	}
	if (cmd[0] == '<' && cmd[1] == '<')
		new->delimiter = 1;
	else if (cmd[0] == '>' && cmd[1] == '>')
		new->append = 1;
	return (i);
}

int	parse_split(char *cmd, char **line, t_link *list, t_link **new)
{
	int		i;
	t_link	*temp;

	i = 1;
	while (cmd[i] == ' ' && cmd[i] != '\0')
		i++;
	if (*line == NULL || cmd[i] == '|')
	{
		invalid_syntax_error("|");
		return (0);
	}
	else if (cmd[i] == '\0')
		return (i);
	(*new)->cmd = cmd_split(*line);
	free (*line);
	add_list(list, *new);
	temp = (t_link *) malloc (sizeof(t_link));
	init_list_element(temp);
	*new = temp;
	*line = NULL;
	return (i);
}
