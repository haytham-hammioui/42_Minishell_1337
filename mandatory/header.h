/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaksiss <smaksiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:56:59 by hhammiou          #+#    #+#             */
/*   Updated: 2025/10/04 13:14:27 by smaksiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# ifndef SUCCESS
#  define SUCCESS 1
# endif

# ifndef FAILURE
#  define FAILURE 0
# endif

# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <time.h>
# include <unistd.h>

extern int	g_exit_code;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SINGLE_QUOTED,
	TOKEN_DOUBLE_QUOTED
}					t_token_type;

typedef struct s_env
{
	char			*value;
	int				is_env_fails;
	char			*name;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				was_quoted;
	struct s_token	*next;
}					t_token;

typedef struct s_fd
{
	int				pipefd[2];
	int				fdin;
	int				fdout;
}					t_fd;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			**infile;
	char			**outfile;
	int				append;
	pid_t			pid;
	char			**heredoc;
	int				*heredoc_expand;
	t_fd			*fd;
	int				flag;
	char			**or_env;
	t_env			*env;
	int				is_path_works;
	int				is_cmd_fails;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_minishell
{
	char			*line;
	t_token			*tokens;
	t_env			*new_env;
	t_cmd			*cmds;
	int				g_exit_code;
}					t_minishell;

typedef struct s_word_params
{
	char	*line;
	int		*i;
	t_env	*env;
	char	**value;
	int		*was_quoted;
}	t_word_params;

typedef struct s_regular_word_params
{
	char		*line;
	int			*i;
	t_env		*env;
	t_token		**tokens;
}	t_regular_word_params;

typedef struct s_extract_params
{
	char	*line;
	int		*i;
	t_env	*env;
	char	quote;
	int		*was_quoted;
}	t_extract_params;

/*------------help-------------*/
void				ft_exit(int ac);
void				print_banner(void);
char				*ft_strndup(const char *s, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strdup(char *s);
int					ft_chr(const char *s, int c);
void				cleanup_and_exit(t_cmd *cmd, int flag);
void				ft_lstadd_back(t_env **lst, t_env *new);
void				ft_lstclear(t_env **lst);
int					ft_isalnum(int c);
int					d_exit(void);
int					ft_isalpha(int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				increment_shlvl(t_env **env);

/*----------signals------------*/
void				intial_signals(void);

/*------------tokenize----------*/
t_token				*ft_tokenize(char *line);
char				*ft_quoted(char *line, int *i, t_token_type *type);
char				*ft_operator(char *line, int *i, t_token_type *type);
char				*ft_word(char *line, int *i);
int					*append_heredoc_flag(int *flags, int new_flag);
char				*extract_quoted_text(t_extract_params *params);
void				handle_quotes_in_word(t_word_params *params, 
						int *local_quoted);
void				append_remaining_text(t_extract_params *params,
						char **res, int start);

/*---------exp------------------*/
void				ft_expand(t_token *tokens, t_env *env);

/*-------parsing-----------*/
t_cmd				*parse_line(t_minishell *mshell);
char				*get_value(t_env *env, char *key);
t_cmd				*tokenizer(char *line, t_env *env);
char				*ft_itoa(int n);

/*-------built ins-----------*/

int					_echo(t_cmd *cmd);
int					_cd(t_cmd *cmd, t_env **menv);
int					_pwd(void);
int					_env(t_env *env, int i);
int					_export(t_cmd *cmd, t_env **env);
int					f_exit(t_cmd *cmd);

int					check_built_in(t_cmd *cmd);
int					get_minus_n_count(t_cmd *cmd);
int					is_valid_args(t_cmd *cmd);
int					main_exit(t_cmd *cmd);
long long			convert_to_ll(char *str);
void				f_clean(t_cmd *cmds);
int					exec_built_in(t_cmd *cmd, t_env **env);
t_env				*create_env(char **env);
int					check_var_content_valid(t_env *tmp);
int					check_var_content_exist(t_env *env, t_env *tmp);
void				env_replace(t_env **lst, t_env *new);
void				env_replace_middle(t_env **lst, t_env *new);
int					env_replace1(t_env **menv, char *name, char *value);
void				ft_lstadd_front(t_env **alst, t_env *new);
int					_unset(t_cmd *cmd, t_env **env);
t_env				*copy_parts(char *env);
int					_env_export(t_env *env);

/*-------execution-----------*/

char				**env_to_arr(t_env *env);
void				wait_children(t_cmd *cmds);
int					cmd_find_path(t_cmd *cm);
int					open_fds(t_cmd *cmd);
int					exec_builtin_handle(t_cmd *cmds);
int					dup_stdin(t_fd *fd, int newfd);
int					dup_stdout(t_fd *fd, int newfd);
int					here_doc(t_cmd *cmd, char *limiter);
void				close_fds(t_fd *fd);
void				intial_signals_exec(void);
int					exec_cmd(t_cmd *cmd);
void				exec(t_cmd *cmds);
void				close_child(t_cmd *cmd);

/*------- HELP FUNCTIONS -----------*/

int					ft_isalpha(int c);
void				ft_putstr_fd(char *s, int fd);
int					ft_isalnum(int c);
int					pwd_replace(t_env **menv);
char				*get_cmd(char **ag);
void				free_str(char **str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_is_not(char *ptr);
char				**ft_split_n(char const *s, char c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*join_cmd(char **myenv, char **str1);
char				**find_path_fd(char **ag, char **env, int *in, int *out);
char				*gft_strjoin(char *s1, char *s2);
size_t				gft_strlen(const char *s);
char				*gft_strdup(const char *s);
void				last_cmd(char **ag, char **myenv, int *fd, int *file);
void				forking_h(int *file, char **ag, char **myenv, int *fd);
void				fork_free(pid_t *pid, int *file, int *fd, char **myenv);
void				fork_err(pid_t *pid, int *fd);
void				add_token(char *line, int *i, t_env *env, t_token **tokens);
void				read_env_name(char *line, int *i, t_env *env, char **res);
void				process_redirection(t_cmd *cmd, t_token *current);
void				append_char_to_str(char c, char **value);
t_cmd				*init_cmd(void);
void				push_cmd_back(t_cmd **head, t_cmd *node);
void				free_tokens(t_token **tokens);
void				free_close(int *fd, int *file, int pid);
char				*merge_strings(char *main_str, char *extra, int free_extra);
void				check_word(t_word_params *params);
void				expand_var(char *line, int *i, t_env *env, char **res);
char				**append_arg(char **args, char *new_arg);
void				parent_pr(int *fd, int *prev_pipe);
void				add_in_list(t_token **head, char *value, t_token_type type,
						int was_quoted);
int					*append_heredoc_flag(int *flags, int new_flag);
t_token_type		get_char_type(char *line, int *i);
int					ambiguous_red(char *line, t_env *env);
int					ambiguous_realfunc(char *value);
int					check_redirect_syntax(char *line, int *i, char red_type);
int					check_redirect(char *line);
int					check_and(char *line);
int					check_quotes_and(char *line);
int					check_semicolon(char *line);
int					check_pipe(char *line);
int					handle_quote_char(char *line, int *i, int *open);
int					ncount(long n);
char				*ft_itoa(int n);
int					check_filename(char *line);
int					check_env(char **env);
int					check_args(char *str);
void				ft_lstadd_back(t_env **lst, t_env *new);
char				*ft_strndup(const char *s, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strchr2(const char *s, int c);
void				_here_sig(int sig);
char				*strjoin_free_c(char *s, char c);
size_t				ft_strlen(const char *s);
char				*strjoin_free(char *s1, char *s2);
int					var(char *limiter, char *line);
int					ft_isdigit(int c);
void				ft_putnbr(int nb, int fd);
char				*get_env_val(char *key, t_env *env);
void				heredoc_handeler(char *limiter, int fd, t_env *env);
int					create_heredoc(t_cmd *cmd, char *limiter);
void				ft_putchar(char c, int fd);
t_env				*ft_lstnew(char *name, char *value);

#endif