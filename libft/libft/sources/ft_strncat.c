/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odrinkwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:13:41 by odrinkwa          #+#    #+#             */
/*   Updated: 2019/09/06 16:36:44 by odrinkwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	start_cat;
	size_t	j;

	start_cat = ft_strlen(s1);
	j = 0;
	while (s2[j] != '\0' && j < n)
	{
		s1[start_cat + j] = s2[j];
		j++;
	}
	s1[start_cat + j] = '\0';
	return (s1);
}
