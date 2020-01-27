/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:00:14 by vlobunet          #+#    #+#             */
/*   Updated: 2019/06/02 15:00:17 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*realloc_str(char *str, int i, char *t, int size)
{
	char	*ret;
	int		p;

	t ? t++ : 0;
	p = -1;
	ret = ft_strnew((int)ft_strlen(str) - size + (int)ft_strlen(t));
	while (++p != i)
		ret[p] = str[p];
	while (t && *t)
		ret[p++] = *t++;
	i = i + size;
	while (str[i])
		ret[p++] = str[i++];
	ft_strdel(&str);
	str = ft_strdup(ret);
	ft_strdel(&ret);
	return (str);
}
