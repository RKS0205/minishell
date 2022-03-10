#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_link
{
	int				fdout;
	char			*file_out;
	int				fdin;
	char			*file_in;
	char			**cmd;
	struct s_link	*next;
}	t_link;

char	**cmd_split(char *s);

#endif