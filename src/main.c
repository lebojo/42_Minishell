/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/26 12:46:17 by lebojo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/proto.h"

void	create_prompt(char **prompt)
{
	*prompt = add_str("💻 \e[0;32m➜ \e[0;36m", actual_folder(), 2);
	*prompt = add_str(*prompt, "\e[0;32m > \e[0m", 1);
}

void print_cmds(t_cmds cmds)
{
	int i = 0;
	int j = 0;
	while (i < cmds.nb_cmd)
	{
		printf("cmd[%d] = %s\n", i, cmds.cmd[i].name);
		printf("arg[%d] = %s\n", i, cmds.cmd[i].arg);
		if (cmds.nb_cmd > 1)
			printf("sep[%d] = %d\n", i, cmds.sep[i]);
		i++;
	}	
}

int arg_counter(char *s)
{
	int i;
	int res;

	i = -1;
	if (!s)
		return (2);
	res = 3;
	while (s && s[++i])
	{
		if (s[i] == ' ' )
			res++;
		if (s[i] == '"')
		{
			while (s[++i] && s[i] != '"')
				;
			if (!s[i] && s[i - 1] != '"')
				return (-1);
		}
		else if (s[i] == '\'')
		{
			while (s[++i] && s[i] != '\'')
				;
			if (!s[i] && s[i - 1] != '\'')
				return (-1);
		}
	}
	return (res);
}

int	strlen_to_char(char *s, int i, char c)
{
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	*str_extractor(char *s)
{
	int i;
	char *res;

	i = 0;
	res = ft_calloc(ft_strlen(s) - 2, sizeof(char));
	if (s[i] == '"')
	{
		while (s[++i] && s[i] != '"')
			res[i - 1] = s[i];
		if (!s[i])
			return (NULL);
	}
	else if (s[i] == '\'')
	{
		while (s[++i] && s[i] != '\'')
			res[i - 1] = s[i];
		if (!s[i])
			return (NULL);
	}
	return (res);
}

char **split_cmd(t_cmd cmd)
{
	char	**res;
	int		i;
	int		j;
	int		k;
	int		nb_arg;

	i = 0;
	j = 0;
	k = 0;
	nb_arg = arg_counter(cmd.arg);
	res = ft_calloc(nb_arg + 1, sizeof(char *));
	res[i++] = ft_strdup(cmd.name);
	printf("nb d'args: %i\n", nb_arg);
	if (!cmd.arg)
		return (res);
	while (--nb_arg - 1)
	{
		k = 0;
		if (cmd.arg[j] == '"')
		{
			res[i] = ft_calloc(strlen_to_char(cmd.arg, j, '"') + 1, sizeof(char));
			j++;
			while (cmd.arg[j] && cmd.arg[j] != '"')
				res[i][k++] = cmd.arg[j++];
		}
		else if (cmd.arg[j] == '\'')
		{
			res[i] = ft_calloc(strlen_to_char(cmd.arg, j, '\'') + 1, sizeof(char));
			j++;
			while (cmd.arg[j] && cmd.arg[j] != '\'')
				res[i][k++] = cmd.arg[j++];
		}
		else
		{
			res[i] = ft_calloc(strlen_to_char(cmd.arg, j, ' ') + 1, sizeof(char));
			while (cmd.arg[j] && cmd.arg[j] != ' ')
				res[i][k++] = cmd.arg[j++];
		}
		i++;
		j++;
	}
	return (res);
}

void omg(t_cmd cmd)
{
	int i = 0, as = arg_counter(cmd.arg);
	char **r = split_cmd(cmd);

	while (i < arg_counter(cmd.arg))
		printf("%s\n", r[i++]);
}

int main(int ac, char **av, char **envp) 
{
	char	*input;
	char	*prompt;
	t_cmds	cmds;

	(void)ac;
	(void)av;
	while (1) {
		create_prompt(&prompt);
		input = readline(prompt);
		if (input[0])
		{
			parse(&cmds, input);
			omg(cmds.cmd[0]);
			// //print_cmds(cmds);
			// if (cmds.cmd[0].name)
			// 	exec_line(&cmds, &envp);
			// else
			// 	printf("unknown error");
			// add_history(input);
			// free(input);
			// free_cmds(&cmds);
		}
	}
	return 0;
}

