NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RDLFLAG  = -lreadline

BLUE = "\033[1;94m"
PURPLE = "\033[1;35m"
YELLOW = "\033[0;33m"
LIGHT_YELLOW = "\033[1;33m"
NOCOLOR = "\033[0;37m"
CYAN = "\033[1;32m"
WHITE = "\033[1;37m"
GRIS = "\033[1;90m"

SRCS = mandatory/minishell.c		\
		mandatory/parsing/expand.c		\
		mandatory/parsing/parse_line.c		\
		mandatory/parsing/parse_line_1.c		\
		mandatory/parsing/parse_line_2.c		\
		mandatory/parsing/help.c		\
		mandatory/parsing/help2.c		\
		mandatory/parsing/help3.c		\
		mandatory/parsing/signals.c		\
		mandatory/parsing/tokenize.c		\
		mandatory/parsing/tokenize_1.c		\
		mandatory/parsing/tokenize_2.c		\
		mandatory/parsing/tokenize_3.c		\
		mandatory/parsing/tokenize_4.c		\
		mandatory/parsing/tokenize_5.c		\
		mandatory/parsing/tokenize_6.c		\
		mandatory/parsing/expand_1.c		\
		mandatory/exec/exec_1.c		\
		mandatory/exec/heredoc1.c \
		mandatory/env/env_help.c \
		mandatory/built-ins/export.c \
		mandatory/built-ins/utils/ft_lstadd_back.c \
		mandatory/env/create_env.c mandatory/built-ins/env.c mandatory/built-ins/pwd.c mandatory/built-ins/cd.c mandatory/built-ins/echo.c mandatory/built-ins/unset.c mandatory/built-ins/handle_built_in.c mandatory/built-ins/utils/ft_putstr_fd_bonus.c \
        mandatory/built-ins/ft_exit.c mandatory/built-ins/utils/ft_split_cmd_bonus.c mandatory/built-ins/utils/ft_substr.c \
        mandatory/exec/exec.c mandatory/exec/cmd_path.c mandatory/exec/heredoc.c mandatory/exec/io_fds.c mandatory/exec/err_handle.c mandatory/exec/executing.c mandatory/exec/env_to_arr.c



OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) mandatory/header.h
	@$(CC) $(CFLAGS) $(OBJS) $(RDLFLAG) -o $(NAME)
	@echo $(WHITE)"  				"$(RESET)
	@echo $(LIGHT_YELLOW)"MINISHELL"$(NOCOLOR)"                       "$(CYAN)"[COMPILE FINISHED]"$(RESET)
	@echo $(CYAN)"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"$(RESET)
	@echo $(GOLD)"To start:"$(RESET)
	@echo $(WHITE)"  ➜ Run: "$(CYAN)"./minishell"$(RESET)
	@echo $(WHITE)"  					Have fun!"$(RESET)
	@echo $(CYAN)"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"$(RESET)
	@echo $(WHITE)"     	                  by: hhammiou && smaksiss"$(RESET)

%.o: %.c mandatory/header.h
	@echo $(GRIS)"compiling :"$(NOCOLOR)"      	"$(WHITE)"$<"$(NOCOLOR)" "$(CYAN)" √"$(NOCOLOR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo $(BLUE)"Object files removed"$(NOCOLOR)

fclean: clean
	@rm -f $(NAME)
	@echo $(PURPLE)"Files Executables Removed"$(NOCOLOR)

re: fclean all

.PHONY: clean
