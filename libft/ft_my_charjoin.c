#include "libft.h"

char	*ft_my_charjoin(char *s1, char s2)
{
	char	*s;
	int		count;

	count = 0;
	if (s1 == NULL)
	{
		s = malloc (2 * sizeof(char));
		s[0] = s2;
		s[1] = 0;
	}
	else
	{
		s = malloc ((ft_strlen(s1) + 2) * sizeof(char));
		if (s == NULL)
			return (NULL);
		while (s1[count] != '\0')
		{
			s[count] = s1[count];
			count++;
		}
		s[count++] = s2;
		s[count] = '\0';
	}
	free (s1);
	return (s);
}