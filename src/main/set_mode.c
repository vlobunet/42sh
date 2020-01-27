/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlobunet <vlobunet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 11:00:25 by vlobunet          #+#    #+#             */
/*   Updated: 2018/08/12 16:01:22 by vlobunet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char			*set_cmd(char *s)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (s[i] && s[i + 1])
	{
		j = i;
		if ((s[j] == 32 && s[j + 1] == 32) || s[0] == 32)
		{
			while (s[j + 1])
			{
				s[j] = s[j + 1];
				j++;
			}
			s[j] = 0;
			i = 0;
		}
		else
			i++;
	}
	(s[(int)ft_strlen(s) - 1] == ' ') ? s[(int)ft_strlen(s) - 1] = 0 : 0;
	tmp = ft_strdup(s);
	ft_strdel(&s);
	return (tmp);
}

int				printnbr(int i)
{
	return (write(0, &i, 1));
}

struct termios	get_default_settings(void)
{
	char			buf[1024];
	struct termios	savetty;
	struct termios	tty;
	char			*name_t;

	((name_t = getenv("TERM")) == NULL) ? print_error_name_t() : 0;
	!isatty(0) ? print_error_term() : 0;
	((tgetent(buf, name_t)) == -1) ? print_error_data(-1) : 0;
	((tgetent(buf, name_t)) == 0) ? print_error_data(0) : 0;
	tcgetattr(0, &tty);
	savetty = tty;
	tty.c_lflag &= ~(ICANON | ECHO | ISIG);
	tty.c_cc[VMIN] = 1;
	tty.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &tty);
	return (savetty);
}

void			res_default_settings(struct termios savetty)
{
	tcsetattr(0, TCSANOW, &savetty);
}
