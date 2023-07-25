/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebojo <lebojo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/25 19:27:04 by lebojo           ###   ########.fr       */
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
	res = 2;
	while (s[++i])
	{
		if (s[i] == ' ' )
			res++;
		if (s[i] == '"')
		{
			while (s[++i] && s[i] != '"')
				;
			if (!s[i])
				return (-1);
		}
		else if (s[i] == '\'')
		{
			while (s[++i] && s[i] != '\'')
				;
			if (!s[i])
				return (-1);
		}
	}
	return (res);
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
	char **res;
	int i;
	int j;
	int k;
	
	i = -1;
	j = 0;
	k = 0;
	res = ft_calloc(arg_counter(cmd.arg) + 1, sizeof(char *));
	while (cmd.arg[++i])
	{
		if (cmd.arg[i] == ' ')
		{
			res[j++] = ft_substr(cmd.arg, k, i - k);
			k = i + 1;
		}
		if (cmd.arg[i] == '"')
		{
			if (!(res[j++] = str_extractor(&cmd.arg[i])))
				return (NULL);
			while (cmd.arg[++i] && cmd.arg[i] != '"')
				;
			if (!cmd.arg[i])
				return (NULL);
			k = i + 1;
		}
		else if (cmd.arg[i] == '\'')
		{
			if (!(res[j++] = str_extractor(&cmd.arg[i])))
				return (NULL);
			while (cmd.arg[++i] && cmd.arg[i] != '\'')
				;
			if (!cmd.arg[i])
				return (NULL);
			k = i + 1;
		}
	}
	return (res);
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
			//print_cmds(cmds);
			if (cmds.cmd[0].name)
				exec_line(&cmds, &envp);
			else
				printf("unknown error");
			add_history(input);
			free(input);
			free_cmds(&cmds);
		}
	}
	return 0;
}

