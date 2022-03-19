/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 13:23:52 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/03/11 13:23:52 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_link
{
	char			*file_out;
	char			*file_in;
	int				fdin;
	int				fdout;
	char			**cmd;
	char			*path;
	int				delimiter;
	int				append;
	int				pipefd[2];
	struct s_link	*next;
}	t_link;

typedef struct s_data
{
	int		exit_code;
	int		exit;
	int		error;
	int		in_exec;
	int		exec_pid;
	int		save_stdin;
	int		save_stdout;
	char	*line;
	char	**env;
	t_link	*list;
}	t_data;

extern t_data	*g_data;
char	**cmd_split(char *s);
void	init_list_element(t_link *new);
void	add_list(t_link *list, t_link *new);
int		parse_quotes(char *cmd, char **line, char quote);
int		parse_redirects(char *cmd, t_link *new, char operator);
int		parse_variables(char *cmd, char **line);
void	exec_command(t_link *list, char **env);
char	*get_path(t_link *list);
void	open_file_output(t_link *list);
void	open_file_input(t_link *list);
char	*ft_gnl_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
void	readline_loop(char **env);
void	kill_loop(int signum);
void	free_list(t_link *list);
void	exit_error_path(char **check, char **cmd);
void	open_delimiter(t_link *list);
void	open_file_input(t_link *list);
void	open_file_output(t_link *list);
void	kill_loop(int signum);
void	do_nothing(int signum);
int		parse_split(char *cmd, char **line, t_link *list, t_link **new);
void	exit_built_in(char **cmd);
void	echo_built_in(char **cmd);
void	free_all(void);
char	**copy_env(char **env);
char	*find_env(char *var);
void	env_built_in(char **cmd);
void	pwd_built_in(void);
void	export_built_in(char **cmd);
char	**get_sorted_env(void);
void	unset_built_in(char	**cmd);
void	cd_built_in(char **cmd);
void	remove_from_env(char *var);
void	export_add(char *var);
void	parse_line(char *cmd, t_link *list);
void	invalid_syntax_error(char *cmd);
void	do_export(char *var);

#endif