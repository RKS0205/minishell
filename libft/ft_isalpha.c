/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:11:59 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/02/03 20:11:59 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if (!((c <= 'z' && c >= 'a')
			|| (c <= 'Z' && c >= 'A')))
		return (0);
	return (1);
}