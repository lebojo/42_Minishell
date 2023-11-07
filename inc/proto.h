/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:35 by jordan            #+#    #+#             */
/*   Updated: 2023/11/07 15:13:12 by abourgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

/*=================================INCLUDES==================================*/

# include "struct.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MS "\e[0;32mMinishell\e[0m"

/*=================================SOURCES==================================*/

/*	MAIN					*/
void	create_prompt(char **prompt, char **env);
void	print_cmds(t_cmds cmds);
int		main(int ac, char **av, char **envp);

/*	EXPANDER				*/
char	*expand(char *src, char ***envp);
t_cmd	create_cmd(char *name, char *arg, int which_pipe, int fred);

/*	FREE					*/
void	free_cmds(t_cmds *cmds);
void	free_cmd(t_cmd *cmd);
void	close_pipe(int *fd);
void	free_all(t_cmds *cmds, char ***env);
void	free_tab(char **tab);

/*	PARSE					*/
int		parse(t_cmds *cmds, char *input, char ***envp);
void	reverse_cmd(t_cmds *cmds, int i);

/*	SUB_PROCESS_PARSE		*/
int		sub_process_parse_fls(t_cmds *cmds, t_inc *inc, char **split);
int		sub_process_parse_true(t_cmds *cmds, t_inc *inc,
			char **split, char ***envp);

/*	SEP_PARSE				*/
void	sep_parse(t_cmds *cmds, char *input);

/*	UTILS					*/
int		char_in_str(char c, char *str);

/*	START					*/
void	start(char ***env);

/*	SIGNAL					*/
void	sig_handler(int sig);

/*	SPACER					*/
char	*format_input(char *str);
int		only_space(char *str);

/*QUOTE						*/
void	rev_quote(enum e_quote *q, char c);
char	*ask_quote(enum e_quote q, char *str);
void	quote_parse(t_cmds *cmds, char **split, t_inc *inc, char ***envp);

/*--------------------EXEC-----------------*/
int		heredoc(t_cmds *cmds, char ***env);
void	read_file(char *name, t_cmd *cmd, char ***env);
void	exec_cmd_heredoc(char *res, t_cmd *cmd, int fd, char ***env);
void	write_in_file(t_cmds *cmd, int x, char ***env, int out);
void	write_in_here(t_cmds *cmd, int i, char ***env, char *hereRes);
void	write_in_file_here(t_cmds *cmds, int x, int in);
void	append_to_file(t_cmds *c, int x, char ***env);
void	exec_in_fork(int entry, int *tab, t_cmd *cmd, char **env);
int		exec_inpipe_builtins(int entry, int fd, t_cmd *cmd, char ***env);

/*	EXEC_CMD				*/
void	exec_cmd(t_cmd *cmd, char **env);
char	**split_cmd(t_cmd cmd);
int		arg_counter(char *s);
int		strlen_to_char(char *s, int i, char c);
char	*str_extractor(char *s);
void	exec_inpipe(t_cmds *cmds, t_pipe *pipe, int which_pipe, char ***envp);
int		exec_sep(t_cmds *cmds, char ***envp);

/*	UTILS_EXEC				*/
char	*find_path(char **envp, char *s, int x);
char	*get_cmd(char **paths, char *cmd);
void	update_last_exit(int status, char ***envp);

/*	GET_CMD					*/
int		is_builtins(t_cmd *cmd, char ***envp);
void	exec_line(t_cmds *cmds, char ***envp);

/*	PIPE					*/
void	first_pipe(t_cmds *cmd, t_pipe *pipes, char ***envp);
void	mid_pipe(t_cmds *cmd, t_pipe *pipes, int i, char ***envp);
void	last_pipe(t_cmds *cmd, t_pipe *pipes, int i, char ***envp);
int		**open_pipes(int nb_pipe);
void	init_pipe(t_pipe *pipes, t_cmds *cmds);

/*	PARSE_CMDS				*/
t_cmds	parse_cmds(t_cmds src, int which_pipe);
int		create_cmds(t_cmds *cmds);
t_cmd	parse_cmd(char *str);

/*---------------------BUILTINS---------------------*/

/*	CD				*/
void	ft_cd(char *new_path, char ***envp);

/*	ECHO			*/
void	ft_echo(t_cmd *cmd);

/*	ENV				*/
void	ft_env(char **env);

/*	EXIT			*/
void	ft_exit(int status, char ***envp);
void	ft_exit_cmd(t_cmds *cmds, t_cmd *cmd, char ***env);

/*	EXPORT			*/
int		strdiff(const char *s1, const char *s2);
char	**copy_tab(char **tab);
void	print_sorted_env(char **env);
void	add_env(char **arg, char ***env);
char	**empty_env(char *s);
void	ft_export(t_cmd *cmd, char ***env);

/*	HASHMAP			*/
char	*hm_get_value(char **map, char *key);
int		hm_set_value(char ***map, char *key, char *new_val);

/*	PWD				*/
char	*actual_folder(void);
void	ft_pwd(void);

/*	UNSET			*/
void	ft_unset(t_cmd *cmd, char ***env);

#endif