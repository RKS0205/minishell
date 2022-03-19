/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 23:05:41 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/03/13 23:05:41 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_delimiter(t_link *list)
{
	int		fd;
	char	*line;

	if (access(".here_doc", F_OK))
		unlink(".here_doc");
	fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = readline(">");
		if (line == NULL || ft_str_check(line, list->file_in) == 1)
		{
			if (line != NULL)
				free (line);
			if (line == NULL)
				write (1, "\n", 1);
			close(fd);
			list->fdin = open(".here_doc", O_RDONLY);
			unlink(".here_doc");
			return ;
		}
		write (fd, line, ft_strlen(line));
		write (fd, "\n", 1);
		free(line);
	}
}

void	open_file_input(t_link *list)
{
	if (list->file_in != NULL)
	{
		if (access(list->file_in, F_OK | R_OK) == -1 && list->delimiter == 0)
		{
			write (2, list->file_in, ft_strlen(list->file_in));
			write (2, ": No such file or directory\n", 28);
			exit(1);
		}
		else if (access(list->file_in, F_OK | R_OK) == 0 \
					&& list->delimiter == 0)
			list->fdin = open (list->file_in, O_RDONLY);
		else if (list->delimiter == 1)
			open_delimiter(list);
		dup2 (list->fdin, STDIN);
	}
}

void	open_file_output(t_link *list)
{
	if (list->file_out != NULL)
	{
		if (access(list->file_out, F_OK) == -1 && list->append == 0)
			list->fdout = open(list->file_out, O_CREAT | O_WRONLY);
		else if (access(list->file_out, F_OK) == -1 && list->append == 1)
			list->fdout = open(list->file_out, O_CREAT | \
				O_WRONLY | O_APPEND, 0644);
		else if (access(list->file_out, F_OK) == 0 && list->append == 0)
			list->fdout = open(list->file_out, O_WRONLY | O_TRUNC);
		else if (access(list->file_out, F_OK) == 0 && list->append == 1)
			list->fdout = open(list->file_out, O_WRONLY | O_APPEND);
		dup2 (list->fdout, STDOUT);
	}
	else if (list->file_out == NULL && list->next != NULL)
		dup2(list->pipefd[1], STDOUT);
}
