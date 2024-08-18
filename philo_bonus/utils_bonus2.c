/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:44:06 by ymassiou          #+#    #+#             */
/*   Updated: 2024/08/17 22:57:48 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	ft_strcpy(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcpy(join + ft_strlen(s1), s2);
	return (join);
}
