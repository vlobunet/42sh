/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipeline_help.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:12:23 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/06 16:12:25 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		count_words(t_token **tkn)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = *tkn;
	while (tmp && (tmp->type == CMD || tmp->type == ARG ||
		tmp->type == P_SUBST))
	{
		if (tmp && tmp->type == P_SUBST)
		{
			while (tmp && tmp->type != P_SUBST_END)
				tmp = tmp->next;
		}
		tmp ? tmp = tmp->next : 0;
		++count;
	}
	return (count);
}
