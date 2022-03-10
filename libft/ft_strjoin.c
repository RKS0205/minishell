/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:13:59 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/02/03 20:13:59 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		count;
	int		count2;

	count = 0;
	count2 = 0;
	s = malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	while (s1[count] != '\0')
	{
		s[count] = s1[count];
		count++;
	}
	while (s2[count2] != '\0')
	{
		s[count] = s2[count2];
		count++;
		count2++;
	}
	s[count] = '\0';
	return (s);
}
