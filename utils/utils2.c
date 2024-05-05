/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpenalba <tpenalba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:07:07 by tpenalba          #+#    #+#             */
/*   Updated: 2024/05/03 19:07:23 by tpenalba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof (char) * (s1_len + s2_len + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcat(str + (s1_len), s2, s2_len + 1);
	return (str);
}

char	*ft_strdup(char *src)
{
	int		size;
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	if (!src)
    {
        return (NULL);
    }
	size = ft_strlen(src);
	dest = malloc((size + 1) * sizeof (char));
	if (dest == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

void ft_putstr(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		write(STDOUT_FILENO, &str[i], 1);
		i++;
	}
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if(!s1 || !s2)
		return(1);
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}