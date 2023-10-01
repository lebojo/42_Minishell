/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchapell <jchapell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:35 by jordan            #+#    #+#             */
/*   Updated: 2023/10/02 01:47:54 by jchapell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

/*===================================INCLUDES====================================*/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "struct.h"
# include "libft/libft.h"

# define MS "\e[0;32mMinishell 2\e[0m"

/*===================================SOURCES====================================*/

/*	MAIN					*/
void	create_prompt(char **prompt);
void 	print_cmds(t_cmds cmds);
int 	main(int ac, char **av, char **envp);

/*	EXPANDER				*/
char	*expand(char *src, char ***envp);
t_cmd	create_cmd(char *name, char *arg, int which_pipe);

/*	FREE					*/
void	free_cmds(t_cmds *cmds);
void	free_cmd(t_cmd *cmd);
void	close_pipe(int *fd);

/*	PARSE					*/
void	sep_counter(t_cmds *cmds, char *input);
void	sep_parse(t_cmds *cmds, char *input);
void	parse(t_cmds *cmds, char *input, char ***envp);

/*	UTILS					*/
int		char_in_str(char c, char *str);

/*	START					*/
void	start(int ac, char **av, char ***envp);

/*	SIGNAL					*/
void	sigint_handler(int sig);

/*--------------------EXEC-----------------*/
char	*heredoc(char *str);
void	read_file(char *name, t_cmd *cmd, char ***env);
void	write_in_file(char *str, char *name, t_cmd *cmd, char ***env);
void	append_to_file(char *str, char *name, t_cmd *cmd, char ***env);
void	exec_in_fork(int entry, int *tab, t_cmd *cmd, char **env);
int		exec_inpipe_builtins(int entry, int fd, t_cmd *cmd, char ***env);

/*	EXEC_CMD				*/
void	exec_cmd(t_cmd *cmd, char **env);
char	**split_cmd(t_cmd cmd);
int		arg_counter(char *s);
int		strlen_to_char(char *s, int i, char c);
char    *str_extractor(char *s);
void	exec_inpipe(t_cmds *cmds, t_pipe *pipe, int which_pipe, char ***envp);
void	exec_sep(t_cmds *cmds, char ***envp, int *fd);

/*	UTILS_EXEC				*/
char	*find_path(char **envp, char *s, int x);
char	*get_cmd(char **paths, char *cmd);
void	update_last_exit(int status, char ***envp);

/*	GET_CMD					*/
int		is_builtins(t_cmd *cmd, char ***envp);
void	exec_line(t_cmds *cmds, char ***envp);

/*	PIPE					*/
void 	first_pipe(t_cmds *cmd, t_pipe *pipes, char ***envp);
void	mid_pipe(t_cmds *cmd, t_pipe *pipes, int i, char ***envp);
void	last_pipe(t_cmds *cmd, t_pipe *pipes, int i, char ***envp);
int		**open_pipes(int nb_pipe);

/*---------------------BUILTINS---------------------*/

/*	CD				*/
void	ft_cd(char *new_path, char ***envp);

/*	ECHO			*/
void	print_echo(char *arg, char ***envp);
void	ft_echo(t_cmd *cmd, char ***envp);

/*	ENV				*/
void	ft_env(char **env);

/*	EXIT			*/
void	ft_exit(void);

/*	EXPORT			*/
int		strdiff(const char *s1, const char *s2);
char	**copy_tab(char **tab);
void	print_sorted_env(char **env);
void	add_env(char **arg, char ***env);
void	update_env(char *key, char *arg, char *new_env, char ***env);
char	**empty_env(char *s);
void	ft_export(t_cmd *cmd, char ***env);

/*	HASHMAP			*/
char	*hm_get_value(char **map, char *key);

/*	PWD				*/
char	*actual_folder(void);
void	ft_pwd(void);

/*	UNSET			*/
void	ft_unset(t_cmd *cmd, char ***env);

#endif