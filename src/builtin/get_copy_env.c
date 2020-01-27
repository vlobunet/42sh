/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_copy_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:18:43 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 15:18:46 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static void	print_warning(int warning, char *needle)
{
	if (warning != MUTE)
	{
		ft_putstr_fd("42sh: Environement element not found: ",
			STDERR_FILENO);
		ft_putendl_fd(needle, STDERR_FILENO);
	}
}

char		*get_copy_env(char *needle, int warning)
{
	char	*res;
	size_t	len;
	int		i;

	res = NULL;
	i = 0;
	len = ft_strlen(needle);
	while (g_sel.m_env[i] != NULL)
	{
		if (ft_strnequ(needle, g_sel.m_env[i], len) &&
			g_sel.m_env[i][len] == '=')
		{
			res = g_sel.m_env[i] + (len + 1);
			return (res);
		}
		++i;
	}
	if (!res)
	{
		print_warning(warning, needle);
		return (NULL);
	}
	return (res);
}
