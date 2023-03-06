# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 15:26:24 by nadel-be          #+#    #+#              #
#    Updated: 2023/03/06 18:38:11 by nadel-be         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                    COLORS                                    #
# **************************************************************************** #
# Text Reset
RCol	= \033[0m

# Regular
Bla		= \033[0;30m
Red		= \033[0;31m
Gre		= \033[0;32m
Yel		= \033[0;33m
Blu		= \033[0;34m
Pur		= \033[0;35m
Cya		= \033[0;36m
Whi		= \033[0;37m

# Bold
BBla	= \033[1;30m
BRed	= \033[1;31m
BGre	= \033[1;32m
BYel	= \033[1;33m
BBlu	= \033[1;34m
BPur	= \033[1;35m
BCya	= \033[1;36m
BWhi	= \033[1;37m

# Underline
UBla	= \033[4;30m
URed	= \033[4;31m
UGre	= \033[4;32m
UYel	= \033[4;33m
UBlu	= \033[4;34m
UPur	= \033[4;35m
UCya	= \033[4;36m
UWhi	= \033[4;37m

# High Intensity
IBla	= \033[0;90m
IRed	= \033[0;91m
IGre	= \033[0;92m
IYel	= \033[0;93m
IBlu	= \033[0;94m
IPur	= \033[0;95m
ICya	= \033[0;96m
IWhi	= \033[0;97m

# BoldHigh Intens
BIBla	= \033[1;90m
BIRed	= \033[1;91m
BIGre	= \033[1;92m
BIYel	= \033[1;93m
BIBlu	= \033[1;94m
BIPur	= \033[1;95m
BICya	= \033[1;96m
BIWhi	= \033[1;97m

# Background
On_Bla	= \033[40m
On_Red	= \033[41m
On_Gre	= \033[42m
On_Yel	= \033[43m
On_Blu	= \033[44m
On_Pur	= \033[45m
On_Cya	= \033[46m
On_Whi	= \033[47m

# High Intensity Backgrounds
On_IBla	= \033[0;100m
On_IRed	= \033[0;101m
On_IGre	= \033[0;102m
On_IYel	= \033[0;103m
On_IBlu	= \033[0;104m
On_IPur	= \033[0;105m
On_ICya	= \033[0;106m
On_IWhi	= \033[0;107m

# **************************************************************************** #
#                                    TEXTS                                     #
# **************************************************************************** #

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #
SRCS =	source/jmsh.c								\
		source/signals.c							\
		source/utils.c								\
		source/utils2.c								\
		source/builtins/b_cd.c						\
		source/builtins/b_echo.c					\
		source/builtins/b_env.c						\
		source/builtins/b_exit.c					\
		source/builtins/b_export.c					\
		source/builtins/b_pwd.c						\
		source/builtins/b_unset.c					\
		source/builtins/b_utils.c					\
		source/execution/access.c					\
		source/execution/child.c					\
		source/execution/cmd.c						\
		source/execution/exec_line.c				\
		source/execution/fd.c						\
		source/execution/fork.c						\
		source/execution/pipe.c						\
		source/parsing/build_exec_blocks.c			\
		source/parsing/exec_blocks_utils.c			\
		source/parsing/expand_variables.c			\
		source/parsing/heredoc.c					\
		source/parsing/merge_words_remove_spaces.c	\
		source/parsing/parsing.c					\
		source/parsing/parsing_utils.c				\
		source/parsing/tokenize.c					\
		source/parsing/tokenize_extra.c				\
		source/parsing/tokenize_utils.c				\
		source/parsing/verify_tokens.c				\

# **************************************************************************** #
#                                  VARIABLES                                   #
# **************************************************************************** #
NAME			= minishell

LIBFT			= libft.a
LIBFTPATH		= ./libft/
OBJS			= $(SRCS:.c=.o)

RLNAIM			= -lreadline -L/Users/nadel-be/.brew/opt/readline/lib -I/Users/nadel-be/.brew/opt/readline/include

INCLIBFT		= -I./libft/
INC				= -I./source/
INC				+= -I./source/parsing/
INC				+= -I./source/execution/
INC				+= -I./source/builtins/
INC				+= -I$(LIBFTPATH)get_next_line/
INC				+= -I$(LIBFTPATH)printf/
ALLINC			= $(INCLIBFT) $(INC) 

CC				= gcc
RM				= rm -f
AR				= ar rcs
# CFLAGSDEBUG		= -Wall -Wextra -Werror -I. -Iincludes -g -fsanitize=address
CFLAGS			= -Wall -Wextra -Werror 
# CFLAGST			= -Wall -Wextra -Werror -I./ -I./libft/ $(ALLINC) $(RLNAIM)



# **************************************************************************** #
#                                   COMMANDS                                   #
# **************************************************************************** #
all:		$(NAME)

jmsh: all
	@clear
	@./$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(ALLINC) -o $@ -c $<

$(NAME):	$(OBJS)
	@make -C $(LIBFTPATH)
	@printf "$(Blu)Making libft... $(RCol)"
	@mv $(LIBFTPATH)$(LIBFT) $(LIBFT)
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(ALLINC) -L. -lft $(RLNAIM)
	@echo "$(Gre)Done!$(RCol)"

clean:
	@echo "$(Red)Removing objects: $(RCol)"
	$(RM) $(OBJS)
	@make clean -C $(LIBFTPATH)

fclean:	clean
	@echo "Removing $(NAME)"
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	@make fclean -C $(LIBFTPATH)

re:	fclean $(NAME)

.PHONY:		all clean fclean re