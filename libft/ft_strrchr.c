/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:14:31 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/02/03 20:14:31 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	a;

	a = 0;
	while (c > 255)
		c -= 256;
	while (*s != '\0')
	{
		s++;
		a++;
	}
	while (a >= 0)
	{
		if (*s == c)
			return ((char *) s);
		s--;
		a--;
	}
	return (NULL);
}
