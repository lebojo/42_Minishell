/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourgue <abourgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:21:35 by jordan            #+#    #+#             */
/*   Updated: 2023/09/06 10:32:12 by abourgue         ###   ########.fr       */
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

/*===================================SOURCES====================================*/

/*	MAIN					*/
void	create_prompt(char **prompt);
void 	print_cmds(t_cmds cmds);
int 	main(int ac, char **av, char **envp);

/*	FREE					*/
void	free_cmds(t_cmds *cmds);
void	free_tube(t_exec *exec);
void    close_fd(t_exec *exec);
void	close_pipe(int *fd);

/*	PARSE					*/
void	sep_counter(t_cmds *cmds, char *input);
void	sep_parse(t_cmds *cmds, char *input);
void	parse(t_cmds *cmds, char *input);

/*	UTILS					*/
int		char_in_str(char c, char *str);

/*---------------------EXEC---------------------*/

/*--------------------NEW-EXEC-----------------*/
char	*heredoc(char *str);

/*	CMD_PIPE				*/
void	cmd_pipe(t_cmd *cmd, t_exec *exec, char ***envp, int x);

/*	CMD_RDR_D				*/
void	cmd_rdr_d_r(t_cmds *cmds, t_exec *exec, char ***envp, int x);
void	cmd_rdr_d_l(t_cmds *cmds, t_exec *exec, char ***envp, int x);
void	push_to_fd(t_exec *exec ,char *res,int x);

/*	CMD_RDR					*/
void	cmd_rdr_r(t_cmds *cmds, t_exec *exec, char ***envp, int x);
void	cmd_rdr_l(t_cmds *cmds, t_exec *exec, char ***envp, int x);
void	exec_rdr(t_cmd *cmd, t_exec *exec, char ***envp, int x);

/*	EXEC_CMD				*/
void	exec_cmd(t_cmd *cmd, t_exec *exec, char **env);
char	**split_cmd(t_cmd cmd);
int		arg_counter(char *s);
int		strlen_to_char(char *s, int i, char c);
char    *str_extractor(char *s);

/*	UTILS_EXEC				*/
char	*find_path(char **envp, char *s, int x);
char	*get_cmd(char **paths, char *cmd);

/*	GET_CMD					*/
int		is_builtins(t_cmd *cmd, char ***envp);
void	exec_line(t_cmds *cmds, char ***envp);
void	select_cmd_type(t_cmd *cmd, t_exec *exec, char ***envp);
void	exec_multiple(t_cmds *cmds, t_exec *exec, char ***envp);
void	setup_exec_var(t_cmds *cmds, t_exec *exec);

/*	UTILS_EXEC				*/
char	*find_path(char **envp, char *s, int x);
char	*get_cmd(char **paths, char *cmd);

/*	PIPE					*/
void	first_pipe(int *fd, char ***envp, int *pid);
void	mid_pipe(int *pipe_fd1, int *pipe_fd2, char ***envp, int *pid);
void	last_pipe(int *fd, char ***envp, int *pid);
int		**open_pipes(int nb_pipe);

/*---------------------BUILTINS---------------------*/

/*	CD				*/
void	ft_cd(char *new_path);

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
char	**emptyEnv(char *s);
void	ft_export(t_cmd *cmd, char ***env);

/*	HASHMAP			*/
char	*hm_get_value(char **map, char *key);

/*	PWD				*/
char	*actual_folder(void);
void	ft_pwd(void);

/*	UNSET			*/
void	ft_unset(t_cmd *cmd, char ***env);

#endif