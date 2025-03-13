# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 22:54:23 by rbardet-          #+#    #+#              #
#    Updated: 2025/03/13 20:31:38 by rbardet-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3

SRC_DIR     = src
LIBFT_DIR   = libft
INC_DIR     = includes
OBJ_DIR     = objs

BUILTINS_DIR  = $(SRC_DIR)/builtins
EXEC_DIR      = $(SRC_DIR)/exec
SUB_EXEC_DIR  = $(EXEC_DIR)/exec
REDIRECT_DIR  = $(EXEC_DIR)/redirect
PARSE_DIR     = $(SRC_DIR)/parsing
SYNTAX_DIR    = $(PARSE_DIR)/syntax_error
QUOTE_DIR     = $(PARSE_DIR)/quotes
TOKENIZE_DIR  = $(PARSE_DIR)/tokenize
WILDCARD_DIR  = $(PARSE_DIR)/wildcards
VALIDATE_DIR  = $(PARSE_DIR)/validate_input
LOGICAL_DIR   = $(SRC_DIR)/logical_op

SRCS = $(SRC_DIR)/main.c \
	$(SRC_DIR)/get_readline.c \
	$(SRC_DIR)/invalid_par.c \
	$(SRC_DIR)/invalid_par2.c \
	$(SRC_DIR)/shell_loop.c \
	$(SRC_DIR)/signal.c \
	$(SRC_DIR)/signal2.c \
	$(LOGICAL_DIR)/execute_tokens.c \
	$(LOGICAL_DIR)/subshell.c \
	$(LOGICAL_DIR)/logical_op.c \
	$(LOGICAL_DIR)/exec_subshell.c \
	$(LOGICAL_DIR)/exec_utils.c \
	$(BUILTINS_DIR)/ft_env.c \
	$(BUILTINS_DIR)/ft_pwd.c \
	$(BUILTINS_DIR)/ft_echo.c \
	$(BUILTINS_DIR)/ft_export.c \
	$(BUILTINS_DIR)/ft_unset.c \
	$(BUILTINS_DIR)/ft_exit.c \
	$(BUILTINS_DIR)/ft_cd.c \
	$(BUILTINS_DIR)/atol.c \
	$(SUB_EXEC_DIR)/builtin_exec.c \
	$(SUB_EXEC_DIR)/exec_cmd.c \
	$(SUB_EXEC_DIR)/check_path_cmd.c \
	$(SUB_EXEC_DIR)/cmd_check.c \
	$(SUB_EXEC_DIR)/fork_exec.c \
	$(REDIRECT_DIR)/parse_cmd.c \
	$(REDIRECT_DIR)/parse_cmd2.c \
	$(REDIRECT_DIR)/parse_cmd3.c \
	$(REDIRECT_DIR)/here_doc.c \
	$(REDIRECT_DIR)/find_env_path.c \
	$(REDIRECT_DIR)/redirect.c \
	$(REDIRECT_DIR)/redirect_open.c \
	$(REDIRECT_DIR)/redirect_exec.c \
	$(REDIRECT_DIR)/redirect_utils.c \
	$(REDIRECT_DIR)/get_flag.c \
	$(REDIRECT_DIR)/redirect_loop.c \
	$(REDIRECT_DIR)/find_next_pipe.c \
	$(REDIRECT_DIR)/xD.c \
	$(REDIRECT_DIR)/replace_doc.c \
	$(REDIRECT_DIR)/split_doc_utils.c \
	$(REDIRECT_DIR)/split_for_doc.c \
	$(REDIRECT_DIR)/here_doc_utils.c \
	$(REDIRECT_DIR)/here_doc_parse.c \
	$(REDIRECT_DIR)/not_valid.c \
	$(EXEC_SUBDIR_SRCS) \
	$(PARSING_SUBDIR_SRCS) \
	$(QUOTE_SUBDIR_SRCS) \
	$(VALIDATE_DIR)/backtick_remove.c \
	$(VALIDATE_DIR)/backtick_remove2.c \
	$(VALIDATE_DIR)/validate_only_backslash_tick.c \
	$(VALIDATE_DIR)/validate_input.c \
	$(QUOTE_DIR)/all_closed.c \
	$(QUOTE_DIR)/all_closed2.c \
	$(QUOTE_DIR)/process_input_line.c \
	$(QUOTE_DIR)/is_only.c \
	$(QUOTE_DIR)/is_only_quotes.c \
	$(SYNTAX_DIR)/syntax_error.c \
	$(SYNTAX_DIR)/syntax_error2.c \
	$(SYNTAX_DIR)/syntax_error3.c \
	$(SYNTAX_DIR)/syntax_error4.c \
	$(SYNTAX_DIR)/error_utils.c \
	$(TOKENIZE_DIR)/split_token.c \
	$(TOKENIZE_DIR)/parse_word.c \
	$(TOKENIZE_DIR)/parse_back.c \
	$(TOKENIZE_DIR)/parse_word2.c \
	$(TOKENIZE_DIR)/append_utils.c \
	$(TOKENIZE_DIR)/dollar_utils.c \
	$(TOKENIZE_DIR)/handle_dollar.c \
	$(TOKENIZE_DIR)/handle_dollar_braces.c \
	$(WILDCARD_DIR)/handle_wildcard.c \
	$(WILDCARD_DIR)/match_pattern.c \
	$(WILDCARD_DIR)/ambigous.c \
	$(WILDCARD_DIR)/expand_wildcard.c \
	$(WILDCARD_DIR)/match_pattern2.c \
	$(WILDCARD_DIR)/quote_remover.c \

OBJS    = $(SRCS:%.c=$(OBJ_DIR)/%.o)
INCLUDES = -I $(INC_DIR) -I $(LIBFT_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	@echo "\033[32mLinking objects and creating $(NAME)...\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/libft.a -o $(NAME) -lreadline
	@echo "\033[32m$(NAME) successfully created!\033[0m"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	@echo "\033[34mBuilding libft...\033[0m"
	@make -C $(LIBFT_DIR) > /dev/null 2>&1

clean:
	@if [ -d "$(OBJ_DIR)" ] && [ -n "$$(ls -A $(OBJ_DIR) 2>/dev/null)" ]; then \
		echo "\033[33mCleaning object files...\033[0m"; \
		rm -rf $(OBJ_DIR); \
		make -C $(LIBFT_DIR) clean > /dev/null 2>&1; \
		echo "\033[32mClean completed successfully!\033[0m"; \
	else \
		echo "\033[33mNo objects to clean.\033[0m"; \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		echo "\033[33mRemoving $(NAME)...\033[0m"; \
		rm -f $(NAME); \
		make -C $(LIBFT_DIR) fclean > /dev/null 2>&1; \
		echo "\033[32mFull clean completed successfully!\033[0m"; \
	else \
		echo "\033[33mNo executable to clean.\033[0m"; \
	fi

re: fclean all

.PHONY: all clean fclean re
