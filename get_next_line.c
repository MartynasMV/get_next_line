/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoldema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:37:44 by mvoldema          #+#    #+#             */
/*   Updated: 2022/11/16 11:37:46 by mvoldema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char	*make_stash_smaller_v2(char *stash, int j)
{
	int		i;
	char	*temp_stash;

	i = 0;
	if (!stash[i] || ft_strlen(stash) == (size_t)j)
	{
		free(stash);
		return (NULL);
	}
	temp_stash = malloc(ft_strlen(stash) - j + 1);
	if (!temp_stash)
	{
		free(temp_stash);
		return (NULL);
	}
	while (stash[j])
	{
		temp_stash[i] = stash[j];
		j++;
		i++;
	}
	temp_stash[i] = '\0';
	free(stash);
	stash = temp_stash;
	return (stash);
}

static char	*return_new_line(char *stash)
{
	int		i;
	char	*new_line;

	i = 0;
	if (!stash || !stash[0] || stash == NULL)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	new_line = malloc(sizeof(char) * (i + 1 + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		new_line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		new_line[i] = stash[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

static char	*get_stash(int fd, char *stash)
{
	char	*buf;
	ssize_t	rd;

	rd = 1;
	buf = malloc((BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (!stash)
	{
		stash = malloc(sizeof(char) * (1));
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	while (enhanced_ft_strchr(stash) == 0 && rd != 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
			return (NULL);
		buf[rd] = '\0';
		if (rd > 0)
			stash = ft_strjoin(stash, buf);
	}
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*new_line;
	int			j;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = get_stash(fd, stash);
	if (stash[0] == '\0')
	{
		free(stash);
		return (stash = NULL);
	}
	new_line = return_new_line(stash);
	j = ft_strlen(new_line);
	stash = make_stash_smaller_v2(stash, j);
	return (new_line);
}

 int	main(void)
{
	int fd;
	char *willy;
	int i = 4;
	//fd = open("g.txt", O_RDONLY);
	//fd = open("big_line_no_nl", O_RDONLY);
	fd = open("c", O_RDONLY);
	if (fd == -1)
	{
		printf("open() error\n");
		return (1);
	}
	while (i > 0)
	{
		willy = get_next_line(fd);
		printf("%s", willy);
		i--;
		free(willy);
	}
}
