/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 18:39:45 by gvynogra          #+#    #+#             */
/*   Updated: 2019/06/02 18:39:46 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "jobs.h"

static	size_t	word_len(char const *s, int start)
{
	size_t		len;

	len = 0;
	while (s[start] && ft_iswhitespace(s[start]))
		start++;
	while (s[start] && !ft_iswhitespace(s[start]))
	{
		len++;
		start++;
	}
	return (len);
}

static	size_t	words_count(char const *s)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((!ft_iswhitespace(s[i]) && ft_iswhitespace(s[i + 1]))
			|| (!ft_iswhitespace(s[i]) && !s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

char			**ft_split_whitespaces(char const *s)
{
	char		**arr;
	size_t		i;
	size_t		counter;

	i = 0;
	counter = 0;
	if (s)
	{
		arr = (char**)malloc(sizeof(char*) * (words_count(s) + 1));
		if (!arr)
			return (NULL);
		while (i < words_count(s) && s[counter])
		{
			while (ft_iswhitespace(s[counter]))
				counter++;
			arr[i] = ft_strsub(s, counter, word_len(s, counter));
			counter += word_len(s, counter);
			counter++;
			i++;
		}
		arr[i] = NULL;
		return (arr);
	}
	return (NULL);
}

static char		*read_buf(int *pipefd)
{
	char	buf[BUFSIZ + 1];
	char	*str;
	char	*tmp;
	ssize_t	ret;

	str = NULL;
	str = NULL;
	ft_memset(buf, 0, BUFSIZ);
	while ((ret = read(pipefd[0], buf, BUFSIZ)) > 0)
	{
		buf[ret] = 0;
		tmp = str;
		str = ft_strjoin(tmp, buf);
		ft_strdel(&tmp);
		ft_memset(buf, 0, BUFSIZ);
	}
	if (ret == -1)
		ft_putstr_fd("42sh: read() error\n", STDERR_FILENO);
	return (str);
}

char			**substitute_command(t_token **tokens)
{
	int		pipefd[2];
	t_tree	*tree;
	char	**arr;
	char	*str;

	tree = (t_tree*)ft_memalloc(sizeof(t_tree));
	tree->command = get_subtree_as_cmd(tokens, C_SUBST);
	tree->token = CMD;
	if (pipe(pipefd) == -1)
		ft_putstr_fd("42sh: pipe() error\n", STDERR_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	run_tree(tree, 0, 0);
	reset_fd();
	destruction_tree(tree);
	str = read_buf(pipefd);
	close(pipefd[0]);
	arr = ft_split_whitespaces(str);
	ft_strdel(&str);
	return (arr);
}
