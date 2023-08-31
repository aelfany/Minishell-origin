/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:09:43 by abelfany          #+#    #+#             */
/*   Updated: 2023/08/28 22:53:50 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

extern int				g_exitstatus;

/*-------------by abelfany 1-------------*/

typedef struct s_var
{
	int				a;
	int				sv;
	int				b;
	int				count;
	char			flag;
	int				mark;
	char			*word;
	char			*join;
}	t_var;

typedef struct s_str
{
	int				b;
	char			flag;
	int				mark;
	char			*word;
	char			*join;
	char			**spl;
}	t_str;

/*-------------by abelfany 2-------------*/

// typedef struct s_vars
// {
// 	char	*line_read; ----------//line read from input
// 	char	*hrd_line; ---------- //line read from heredoc
// 	char	**builtins; -------- -//pointer to builtin names 
// 	char	**envr; -------------//holds the env variables
// 	int		*pid; ---------------//holds id of open processes
// 	int		*pipe_in;------------//holds the last rdin in each pipe
// 	int		*pipe_out;----------//holds the last rdout in each pipe
// 	int		*pipe_hrd;----------//holds the last hrd in each pipe
// 	int		p_in;---------------//holds pipes rdin
// 	int		p_out;--------------//holds pipes rdout
// 	int		p_hrd; -------------//holds pipes hrd
// 	int		failed_rd; -------- //failed redirection integer
// 	int		pipe_count; -------- //holds how many pipes are there
// 	int		cmd_count; -------- //holds the command count
// 	int		(*pipe)[2]; -------- //holds the open filedes of open pipes 
// 	int		i; -----------------//integer used as an index 
//in some cases
// 	int		redirections_bool; //boolean used to check if
// redirections exist originally set to -1
// 	int		hd_pipe[2]; -------//heredoc pipe
// 	int		og_in; ------------// holds stdin 
// 	int		og_out; ---------- //holds stdout
// 	int		in; --------------// holds redirection in fd
// 	int		out; ------------// holds redirection out fd 
// }	t_vars;

typedef struct s_vars
{
	char				*line_read;
	char				*hrd_line;
	int					*pipe_in;
	int					*pipe_out;
	int					*pipe_hrd;
	int					*pid;
	int					p_in;
	int					p_out;
	int					p_hrd;
	int					failed_rd;
	int					pipe_count;
	int					cmd_count;
	int					(*pipe)[2]; 
	int					hd_pipe[2];
	int					i;
	int					redirections_bool;
	int					og_in;
	int					og_out;
	int					in;
	int					out;
}	t_vars;

// typedef struct s_env
// {
// 	char	*value; //holds the envr elements after the = equal sign
// 	char	*name; // holds the id of the envr variable (before the equal sign)
// 	int		free_name;  //free name value 0 for ok 1 for no
// 	int		free_value; //free value flag 0 for ok 1 for no
// 	int		uninitialized; //uninitialized var flag 
// 	int		hidden_flag; // 1 hidden 0 available 
// 	char	*quoted_env; //holds the env in double quotes 
// 	char	*pwd_var; //everytime cd is used this variable gets updated 
// 	struct 	s_env *next; //pointer to the next element of the linked list
//  which is another env element
// } t_env;

typedef struct s_env
{
	char				*value;
	char				*name;
	int					uninitialized;
	int					hidden_flag;
	struct s_env		*next;
}	t_env;

typedef struct s_cmd
{
	char				*cmd;
	int					count;
	char				*token;
	int					heredoc;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_creat
{
	char				*cmd;
	char				*token;
	char				**opt;
	int					count;
	int					pipe;
	int					ex;
	struct s_creat		*next;
}	t_creat;

/*-------------by abelfany 1-------------*/

int					not(char c);
int					check_sp_ch(char c);
int					wc(char *str);
int					exist(char c);
int					not_string(char c);
int					is_wts(char c);
char				*ft_itoa(int n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					skip_space(char *str);
int					synatx_er(t_creat *res);
int					syntax_pipes(char *str);
t_creat				*new_list(t_creat *res);
int					skip_w_space(char *str);
int					ft_lenstrs(char **strs);
void				error_handler(char *str); 
int					counter_quots(char *str);
char				*ft_strdup(char *s1);
int					counter(char *str, char c);
int					check_expand_case(char c);
int					check_wts(char c, char *wts);
int					check_command(t_creat *list);
char				*_remallc(char *str, char c);
char				*quts(char *str, int *x, t_env *env);
char				**split_word(char const *s, char *c);
int					find_last(char *str, int *flag, char c);
char				*expand(t_env *env, int count, char *word);
char				*expand_word(char *str, int *x, t_env *env);
void				ft_lstadd_back(t_creat **lst, t_creat *new);
char				*quots_expand(char *str, int *x, t_env *env);
char				*insert_expand_word(t_creat **res, char **word);
void				check_heredoc(char *str, int *x, t_creat **res);
t_creat				*read_string(t_creat **list, char *str, t_env *envr);
void				insert(t_creat **root, char *item, char *str, int flag);
void				who_first(char *str, int *x, t_creat **res, t_env *env);
void				take_string(char *str, int *x, t_creat **res, t_env *env);
int					add_back_token(t_creat **res, char *word, char flag, int x);
void				rederction_apn(char *str, int *x, t_creat **res,
						t_env *env);
char				*expand_red(t_env *env, int count, char *word,
						t_creat **res);
char				*expand_word_red(char *str, int *x, t_env *env,
						t_creat **res);
void				check_expand_new(char *str, int *x, t_creat **res,
						t_env *env);
int					check_rederction(char *str, t_creat **res, char c,
						t_env *env);

/*-------------by abelfany 2-------------*/

// tool functions
char				**ft_split(char const *s, char c);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_charjoin(char *str, char c);
char				*ft_strjoin_free(char *s1, char *s2, int f, int s);
char				*ft_itoa(int n);
char				*ft_strdup1(char *dest, char *src);
int					ft_strlen(const char *str);
int					ft_strlen_delim(char *str, char delim);
int					ft_strcmp(char *s1, char *s2);
int					ft_isnum(char *str);
char				*ft_itoa(int n);
unsigned long long	ft_atoi(char *str, size_t i, t_env *envr);
int					calc_size(char *str, char delim);
void				ft_putstr_fd(char *str, int fd);
void				ft_init_s(t_creat **res, t_vars **var, t_env **envr,
						t_creat **list);
void				ft_exit_p(int i);

//env tools

t_env				*ft_fillup_unset_help(t_env **envr);
void				fill_env(t_env **envr, char **env, int d, int i);
void				add_1pwd(t_env *ptr);
void				ft_fillup_unset(t_env **envr);
void				ft_fillup(t_env *str, char *env);
void				ft_fillup_envr(t_env *str, char *env); 
void				ft_add_three(t_env **envr);
void				ft_fillup_unset(t_env **envr);
char				*ft_getenv(t_env *envr, char *var);
char				*my_get_env(t_env *envr, char *id);
int					check_env_unavailable(t_env **envr, char *env);

// here_doc && redirections functions 

char				*expand_hrd(t_env *env, int count, char *word);
int					ft_open_heredocs(t_creat **res, t_vars **var, t_env *envr);
int					ft_check_last(t_creat *res);
int					ft_check_hrd(char *token);
int					ft_exp_check(char *token);
int					ft_heredoc_p(t_creat *res, t_vars *var, t_env *envr);
char				*take_expand_hrd(char *str, int *x, t_env *env);
void				ft_open_redirections(t_creat **res, t_vars **var);

// exec functions

char				**path_finder(char **env);
char				*command_finder(char *cmd, char *env, int i);
int					check_built_ins(t_creat *res);
int					ft_env_size(t_env *ptr);
void				ft_error(char *str);
void				execute_cmd(t_vars **var, t_env **envr, t_creat **res);
void				init_vars(t_vars *var);
void				ft_exec(t_env *envr, t_creat *res);
void				ft_error_exec(t_creat *res, char *cmd, int flag);
void				exec_built_ins(t_env **envr, t_creat *res, t_vars *var);

// commands

int					cd(t_creat *res, t_env **envr, int flag);
int					pwd(t_env *envr);
int					echo(char **opt);
int					ft_exit(t_env *env, t_creat *res, t_vars *var);
int					ft_unset_parser(char *env);
void				ft_env(char **opt, t_env *envr);
void				ft_exit_error(char *str, int flag, t_env *envr);
void				ft_export(t_env **envr, char **opt, int d);
void				unset(t_env **envr, t_creat *res, int d);

//cd functions

int					ft_file_check(char *cmd);
void				ft_add_oldpwd(t_env **envr, char *oldcwd);

// export functions

char				*ft_id_fillup(char *str);
int					ft_export_parser(char *env, int n);
int					ft_count_vars(char **opt, t_env *envr);
int					ft_export_last(t_env **envr, char **opt, int d);
void				print_env(t_env *envr);
void				print_env(t_env *envr);

// pipe functions

void				ft_pipe(t_vars *var);
void				pipe_calc(t_creat *res, t_vars *var);
void				ft_execone(int	*end, t_creat *res, t_env *envr,
						t_vars *var);
void				ft_execpipe(t_env *envr, t_creat *res, t_vars *var);
void				ft_exectwo(int *end, t_creat *res, t_env *envr,
						t_vars *var);
void				ft_close_first(int end[][2], t_creat *res, t_vars *var,
						t_env *envr);
void				ft_close_last(int end[][2], t_creat *res, t_vars *var,
						t_env *envr);
void				ft_close_pipe(int end[][2], t_creat *res, t_vars *var,
						t_env *envr);
void				ft_exec_pipe(t_env *envr, t_creat *res, int i);
void				ft_close_all(t_vars *var);
int					check_pipes(t_creat *res);
int					pipes_exec(t_creat *res, t_vars *var, t_env *envr);

// free tools

void				ft_free_loop(char **opt);
void				free_var(t_vars *var);
void				free_res(t_creat *res);
void				free_opt(char **str);
void				free_list(t_creat **save);
char				*free_path(char **path);
int					free_line(char *str);

// all pipe functions

int					rd_in_p(t_creat **ptr);
int					rd_out_p(t_creat **ptr);
int					rd_ap_p(t_creat **ptr);
int					ft_error_rd_p(t_creat *res, int n);
int					check_pipes(t_creat *res);
void				rd_init(t_creat *res, t_vars *var);
void				ft_close_all_rd(t_vars *var);
void				ft_init_p_vars(t_vars *var, t_creat *res);
void				hrd_signal_reset(void);
void				ft_pipe(t_vars *var);
void				pipe_calc(t_creat *res, t_vars *var);
void				ft_input_fix(t_vars **var, t_creat *res);
void				ft_close_all_p(t_vars *var, int i);
void				ft_error_p(void);
void				ft_systemcall_protect(int val);
void				ft_malloc_protect(void *ptr);

// signals && handlers

void				signal_child(void);
void				signal_hrd(void);
void				handler_ignore(int a);
void				here_doc_handler(int a);
void				exitstatus_handler(int status);
void				handler_ignore(int a);
void				handler_child(int a);
void				exec_signals(t_creat *res);
void				signal_ignore(void);
void				signals(void);

#endif