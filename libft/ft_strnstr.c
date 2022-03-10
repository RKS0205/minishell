/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:14:26 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/02/03 20:14:26 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	a;
	size_t	b;

	a = 0;
	if (to_find[0] == '\0')
		return ((char *) str);
	while (a < len && str[a] != '\0')
	{
		b = 0;
		while (str[a + b] == to_find[b] && a + b < len)
		{
			if (to_find[b + 1] == '\0')
				return ((char *) str + a);
			b++;
		}
		a++;
	}
	return (NULL);
}
