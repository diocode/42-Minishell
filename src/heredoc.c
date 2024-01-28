/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: digoncal <digoncal@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 23:22:17 by digoncal          #+#    #+#             */
/*   Updated: 2024/01/27 23:22:17 by digoncal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

static char	*gen_new_input(char *str, char *key, char *value)
{
	char	*new_str;
	size_t	size;

	size = ft_strlen(value) + ft_strlen(str + ft_strlen(key)) + 1;
	new_str = ft_calloc(size, sizeof(char));
	if (!new_str)
		return (ms_error(1), NULL);
	ft_strcpy(new_str, str);
	ft_strcat(new_str, value);
	ft_strcat(new_str, str + ft_strlen(key));
	free(str);
	return (new_str);
}

static char	*handle_value(char *input, char *key, size_t key_len)
{
	char	*value;

	value = NULL;
	if (!ft_strncmp(key, "?", 2))
		value = ft_itoa(g_exit_code);
	else
		value = ms_getenv(key);
	if (value)
	{
		if ((ft_strlen(value) + ft_strlen(input) - ft_strlen(key) - 1)
			> ft_strlen(input))
			input = gen_new_input(input, key, value);
		else
		{
			ft_memmove(input, value, ft_strlen(value));
			ft_memmove(input + ft_strlen(value),
				input + key_len, ft_strlen(input + key_len) + 1);
		}
		free(value);
	}
	else
		ft_memmove(input, input + key_len, ft_strlen(input + key_len) + 1);
	return (input);
}

static char	*expand_input(char *input, int key_len)
{
	char	*new_input;
	char	*key;
	int 	i;

	new_input = NULL;
	key = ft_calloc(key_len + 1, sizeof(char));
	if (!key)
		return (ms_error(1), ms_exit(NULL), NULL);
	ft_strlcpy(key, input, key_len);
	i = 0;
	while (i < key_len && isdigit(key[i]))
		i++;
	if (i > 0)
	{
		ft_memmove(key, key + 1, key_len - 1);
		ft_memmove(input + i, key, ft_strlen(key));
		ft_memmove(input + i + ft_strlen(key),
			input + i + key_len, ft_strlen(input + i + key_len) + 1);
	}
	else
		new_input = handle_value(input, key, key_len);
	free(key);
	return (new_input);
}

static int	key_len(char *input)
{
	int	len;

	if (ft_strlen(input) < 2)
		return (1);
	len = 0;
	while (input[len] && (isalnum(input[len])
		||input[len] == '_' || input[len] == '?'))
	{
		len++;
		if (input[len - 1] == '?')
			break ;
	}
	return (len);
}

static char *expand_heredoc(char *input)
{
	char	*new_input;
	char	*tmp;
	int		key_length;
	int		i;

	new_input = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	i = -1;
	if (!new_input)
		return (ms_error(1), ms_exit(NULL), NULL);
	while (input[++i])
	{
		if (input[i] == '$')
		{
			tmp = new_input;
			key_length = key_len(input + i + 1);
			new_input = expand_input(input + i + 1, key_length);
			if (tmp)
				free(tmp);
			i += key_length;
		}
		else
			new_input[i] = input[i];
	}
	free(input);
	return (new_input);
}

static int	create_heredoc(t_token *redir, char *hd_file)
{
	int		fd;
	char	*input;

	fd = open(hd_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	input = readline("> ");
	while (input && ft_strncmp(redir->content, input,
			ft_strlen(redir->content) + 1) && g_exit_code != 2)
	{
		if (input[0])
			input = expand_heredoc(input);
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
		input = readline("> ");
	}
	free(input);
	if (g_exit_code == 2)
		return (1);
	close(fd);
	return (0);
}

static int	setup_heredoc(t_process *process, t_token *redirct, char *hd_file)
{
	int		flg;

	flg = create_heredoc(redirct, hd_file);
	if (process && process->builtin && ft_strncmp(process->builtin, "echo", 5))
		ms()->heredoc = true;
	return (flg);
}

static char	*gen_hd_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin(".tmp_file", num);
	free(num);
	return (file_name);
}

int	send_heredoc(t_process *process)
{
	t_token	*redir;

	redir = process->redirect;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			if (process->hd_file)
				free(process->hd_file);
			process->hd_file = gen_hd_filename();
			if (setup_heredoc(process, redir, process->hd_file))
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}
