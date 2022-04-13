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

void	add_redirect(t_link *new, char *temp, char operator)
{
	dup2(g_data->save_stdin, STDIN);
	if (operator == '<')
	{
		if (new->file_in != NULL)
		{
			free (new->file_in);
			close(new->fdin);
		}
		new->file_in = temp;
		open_file_input(new);
	}
	if (operator == '>')
	{
		if (new->file_out != NULL)
		{
			free (new->file_out);
			close(new->fdout);
		}
		new->file_out = temp;
		open_file_output(new);
	}
}

int	parse_variables(char *cmd, char **line)
{
	int		i;
	int		start;
	char	*var;

	i = 1;
	start = 1;
	if (cmd[1] == '?')
	{
		var = ft_itoa(g_data->exit_code);
		*line = ft_my_strjoin(*line, var);
		free (var);
		return (2);
	}
	if (ft_isdigit(cmd[1]))
		return (2);
	while (ft_isalnum(cmd[i]))
		i++;
	var = ft_substr(cmd, start, i - start);
	if (var != NULL)
	{
		if (find_env(var) != NULL && find_env(var)[0] != '\0')
			*line = ft_my_strjoin(*line, find_env(var));
		free (var);
	}
	return (i);
}

int	parse_quotes(char *cmd, char **line, char quote)
{
	int	i;

	i = 1;
	*line = ft_my_charjoin(*line, cmd[0]);
	while (cmd[i] != '\0')
	{
		if (quote == '\"' && cmd[i] == '$' && (ft_isalnum(cmd[i + 1]) || \
		cmd[i + 1] == '?'))
			i += parse_variables(cmd + i, &(*line));
		if (cmd[i] == quote)
		{
			*line = ft_my_charjoin(*line, cmd[i++]);
			return (i);
		}
		if (cmd[i] != '\0')
			*line = ft_my_charjoin(*line, cmd[i++]);
	}
	write (STDERR, "Error: unclosed quotes\n", 24);
	g_data->error = 1;
	g_data->exit_code = 1;
	return (i);
}

int	parse_redirects(char *cmd, t_link *new, char operator)
{
	int		start;
	int		i;
	char	*temp;

	i = 0;
	while (cmd[i] == ' ' || (cmd[i] == operator && i < 2))
		i++;
	start = i;
	while (cmd[i] != ' ' && cmd[i] != '\0' && cmd[i] != '|' && cmd[i] != '&' \
		&& cmd[i] != ';' && cmd[i] != '(' \
		&& cmd[i] != ')' && cmd[i] != '<' && cmd[i] != '>')
		i++;
	if (i == start)
		check_redirect_error(cmd + i);
	if (cmd[0] == '<' && cmd[1] == '<')
		new->delimiter = 1;
	else if (cmd[0] == '>' && cmd[1] == '>')
		new->append = 1;
	temp = ft_substr(cmd, start, i - start);
	check_directory_error(temp);
	if (operator == '<')
		add_redirect(new, temp, operator);
	else if (operator == '>')
		add_redirect(new, temp, operator);
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
	if (*line != NULL)
		(*new)->cmd = cmd_split(*line);
	free (*line);
	add_list(list, *new);
	temp = (t_link *) malloc (sizeof(t_link));
	init_list_element(temp);
	*new = temp;
	*line = NULL;
	return (i);
}
