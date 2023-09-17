# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 11:45:24 by abelfany          #+#    #+#              #
#    Updated: 2023/08/31 18:43:31 by anchaouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = minishell.h
NAME = minishell

READLINE= /Users/$(USER)/.brew/Cellar/readline/8.2.1/lib
INCLUDE= /Users/$(USER)/.brew/Cellar/readline/8.2.1/include

SRC =	./parsing/flager.c ./parsing/checkers.c ./parsing/cmd_and_quots.c ./parsing/expand_helper.c \
		./parsing/expand.c ./parsing/extensions.c ./parsing/handlers.c ./parsing/helpers_functions.c \
		./parsing/herdoc_append.c ./parsing/heredoc.c ./parsing/lst_gen.c ./parsing/read_input.c ./parsing/expand_fun.c \
		./parsing/redirection.c ./parsing/split_word.c ./parsing/expand_tools.c\
		./execution/ft_heredoc.c ./execution/ft_heredoc_tools.c ./execution/env_tools.c ./execution/redirections_tools.c \
		./execution/redirections.c ./execution/ft_getenv.c ./execution/exec_tools.c ./execution/init.c ./execution/env.c ./execution/exec_tools2.c\
		./execution/check_cmd.c ./execution/handlers.c ./execution/exec_cmd.c ./execution/env_three_tools.c ./execution/exec_signal.c \
		./pipes/pipe_close.c ./pipes/pipe_exec.c ./pipes/pipes_hrd.c ./pipes/pipes_rd_tools.c \
		./pipes/pipes.c ./pipes/init_vars.c ./pipes/pipes_exec_tools.c ./pipes/pipes_tools.c  \
		./pipes/pipes_rd.c  ./pipes/pipes_hrd_tools.c \
		./commands/export_tools.c ./commands/export_parsing.c ./commands/unset_parsing.c \
		./commands/export.c ./commands/unset.c  ./commands/cd_tools.c ./commands/exit.c \
	 	./commands/cd.c ./commands/pwd.c  ./commands/echo.c ./commands/env.c \
		ft_atoi.c ft_itoa.c ft_split.c ft_strcpy.c free_tools.c tools.c utils.c ft_strjoin.c \
		ft_protect.c ft_strlen.c tools1.c minishell.c \

S_OBJ = $(SRC:.c=.o)
C_FLAG = -Wall -Wextra -Werror
RM = @rm -rf

all: $(NAME)

$(NAME):$(S_OBJ)
	cc $(C_FLAG) -lreadline -L $(READLINE) $(S_OBJ) -o $(NAME)
	
%.o : %.c $(HEADER)
	cc $(C_FLAG) -I $(INCLUDE)  -c $< -o $@
	
clean :
	$(RM) $(S_OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all 

.PHONY : all fclean clean re

