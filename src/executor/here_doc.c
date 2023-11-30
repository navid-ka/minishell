/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- <nkeyani-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:39:01 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/11/30 14:39:03 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	fill_here_doc_file(int *pipefd, char *limiter)
{
	char	*line;

	// signal(SIGINT, set_up_signals_here_doc);
	line = get_next_line(STDIN_FILENO);
	if (ft_strncmp(limiter, line, ft_strlen(limiter)) == 0
		&& line[ft_strlen(limiter)] == '\n')
	{
		if (line != NULL)
			free(line);
		return (0);
	}
	while (line != NULL)
	{
		if (ft_strncmp(limiter, line, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
			break ;
		else
			ft_putstr_fd(line, pipefd[1]);
		if (line != NULL)
			free(line);
		line = get_next_line(STDIN_FILENO);
	}
	// set_up_signals_parent();
	return (0);
}

int	manage_here_doc(t_redir *word, int pid)
{
	int		pipefd[2];

	if (word != NULL)
	{
		if (word->type == HERE_DOC)
		{
			pipe(pipefd);
			fill_here_doc_file(pipefd, word->file);
			close(pipefd[1]);
			if (pid != 1)
				dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
	}
	return (0);
}
