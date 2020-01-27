/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbudnik <vbudnik@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 17:25:47 by vbudnik           #+#    #+#             */
/*   Updated: 2019/06/01 17:27:18 by vbudnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <stdio.h>

/*
** функция для начала определяет можно ли печатать символ на экран
** а после определяет нужно ли переводить курсор в начало новой строки
** эта функция так же и печатает символ переноса строки если встречает его
** раньше чем размер ширины экрана
*/

void	print_key(char key, int flag)
{
	struct winsize	s;

	tputs(tgetstr("cd", NULL), 1, printnbr);
	if (ioctl(0, TIOCGWINSZ, (char *)&s) < 0 || key == 0)
		return ;
	if (g_sel.pos[0] + 1 == s.ws_col || key == '\n')
	{
		while (g_sel.pos[0] != 0)
		{
			g_sel.pos[0]--;
			ft_putchar_fd('\b', 1);
		}
		tputs(tgetstr("do", NULL), 1, printnbr);
		g_sel.pos[1]++;
	}
	key != '\n' ? ft_putchar_fd(key, 1) : 0;
	key != '\n' ? g_sel.pos[0]++ : 0;
	flag == 1 ? g_sel.pos[2]++ : 0;
}

void	ft_printf(char key, char *str, int size_mess)
{
	struct winsize	s;
	int				i;

	i = 0;
	if (ioctl(0, TIOCGWINSZ, (char *)&s) < 0)
		return ;
	print_key(key, 1);
	if (str && *str)
	{
		while (str[i])
			print_key(str[i++], 1);
		while (i)
		{
			go_left(1, size_mess);
			i--;
		}
	}
}

char	*del_sumb(char *s1, int size_mess, int flag, char *tmp)
{
	char	*dup;

	if ((!g_sel.pos[2]) && !tputs(tgetstr("bl", NULL), 1, printnbr))
		return (s1);
	s1 ? dup = ft_strndup(s1, g_sel.pos[2] - 1) : 0;
	tmp = ((s1 && g_sel.pos[2] < (int)ft_strlen(s1)) ?\
	ft_strjoin(dup, s1 + g_sel.pos[2]) : ft_strdup(dup));
	ft_strdel(&dup);
	go_left(1, size_mess);
	g_sel.pos[2] == 0 ? flag = 1 : 0;
	g_sel.pos[2] == 0 ? g_sel.pos[2]++ : 0;
	flag == 1 ? ft_printf(0, s1 + g_sel.pos[2], size_mess) :\
	ft_printf(0, s1 + g_sel.pos[2] + 1, size_mess);
	ft_strdel(&s1);
	flag == 1 ? g_sel.pos[2]-- : 0;
	!ft_strlen(tmp) ? ft_strdel(&tmp) : 0;
	return (tmp);
}

/*
** смысл следующий:
** разделить строку на до и после курсора
** добавить новый символ в часть после курсора
** очистить все после курсора
** напечатать сохраненную и бновленную часть строки после курсора
*/

char	*print_sumb(char buff, char *cmd, int size_mess)
{
	char	*src[3];
	char	sumb[2];

	src[0] = (cmd ? ft_strndup(cmd, g_sel.pos[2]) : NULL);
	src[1] = (cmd ? ft_strdup(cmd + g_sel.pos[2]) : NULL);
	ft_printf(buff, src[1], size_mess);
	sumb[0] = buff;
	sumb[1] = 0;
	src[2] = (src[0] ? ft_strjoin(src[0], sumb) : ft_strdup(sumb));
	ft_strdel(&src[0]);
	src[0] = (src[1] ? ft_strjoin(src[2], src[1]) : ft_strdup(src[2]));
	ft_strdel(&cmd);
	ft_strdel(&src[2]);
	ft_strdel(&src[1]);
	return (src[0]);
}
