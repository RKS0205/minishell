/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:11:36 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/02/03 20:11:36 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	my_math(const char *nptr, int a, int x, int n)
{
	while (nptr[a] > 47 && nptr[a] < 58)
	{
		if (n == 1)
			x = (x * 10) + (nptr[a] - 48);
		else
			x = (x * 10) - (nptr[a] - 48);
		a++;
	}
	return (x);
}

long	ft_atol(const char *nptr)
{
	int		a;
	int		n;
	long	x;

	n = 1;
	a = 0;
	x = 0;
	while ((nptr[a] > 8 && nptr[a] < 14) || nptr[a] == 32)
		a++;
	if (nptr[a] == '+' || nptr[a] == '-')
	{
		if (nptr[a] == '-')
			n *= -1;
		a++;
	}
	else if (!(nptr[a] > 47 && nptr[a] < 58))
		return (0);
	x = my_math(nptr, a, x, n);
	return (x);
}
