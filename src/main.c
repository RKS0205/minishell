#include "../minishell.h"

void	parse_line(char *cmd)
{
	int		i;
	int		start;
	char	temp;
	char	*file;
	char	*file2;
	char	*line;

	i = 0;
	(void)file;
	(void)file2;
	line = NULL;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			i++;
			temp = cmd[i - 1];
			while (cmd[i] != temp && cmd[i] != '\0')
				line = ft_my_charjoin(line, cmd[i++]);
		}
		else if (cmd[i] == '<')
		{
			if (line == NULL)
				line = ft_substr(cmd, 0, i);
			i++;
			while (cmd[i] == ' ')
				i++;
			start = i;
			while (cmd[i] != ' ' && cmd[i] != '\0')
				i++;
			file2 = ft_substr(cmd, start, i - start);
		}
		else if (cmd[i] == '>')
		{
			if (line == NULL)
				line = ft_substr(cmd, 0, i);
			i++;
			while (cmd[i] == ' ')
				i++;
			start = i;
			while (cmd[i] != ' ' && cmd[i] != '\0')
				i++;
			file = ft_substr(cmd, start, i - start);
		}
		if (cmd[i] != '\0')
		{
			line = ft_my_charjoin(line, cmd[i]);
			i++;
		}
	}
	printf ("%s\n%s\n%s\n", file, file2, line);
}

void	do_command(char *line)
{
	int		i;
	char	**cmds;

	cmds = ft_split(line, '|');
	i = 0;
	while (cmds[i] != NULL)
		parse_line(cmds[i++]);
}

int main(void)
{
	char *line;

	while (1)
	{
		line = readline("MINISHELL> ");
		do_command(line);
		free (line);
	}
}
