# **************************************************************************** #
#                                   MINISHELL                                 #
# **************************************************************************** #

# ---- PROGRAM NAME ----
NAME		:= minishell

# ---- DIRECTORIES ----
SRC_DIR		:= src
OBJ_DIR		:= obj
INC_DIR		:= include

LIBFT_DIR	:= libft
LIBFT		:= $(LIBFT_DIR)/libft.a
LIBFT_INC	:= $(LIBFT_DIR)/include

# ---- COMPILER ----
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g3 -I$(INC_DIR) -I$(LIBFT_INC) -fPIE

# ---- LIBRARIES ----
LDFLAGS		:= -lreadline -L$(LIBFT_DIR) -lft

# ---- SOURCES ----
SRCS		:=	main.c \
				prompt/prompt.c \
				prompt/prompt_colors.c \
				prompt/prompt_utils.c \
				signals/signals.c \
				signals/signals_heredoc.c \
				lexer/tokenization_more_utils.c \
				lexer/tokenization.c \
				lexer/tokenization_utils.c \
				parser/parsing.c \
				parser/parser_add_word.c \
				parser/parser_cmd.c \
				parser/parser_redir.c \
				parser/parser_utils.c \
				expand/expand.c \
				builtins/builtins.c \
				exec/exec_cmd.c \
				exec/exec_pipeline.c \
				exec/exec_utils.c \
				heredoc/heredoc.c \
				env/env_variable.c \
				redirections/redirections.c \
				builtins/builtins_echo.c \
				builtins/builtins_cd_utils.c \
				builtins/builtins_pwd.c \
				builtins/builtins_env.c \
				builtins/builtins_cd.c \
				builtins/builtins_exit.c \
				builtins/builtins_export.c \
				builtins/builtins_unset.c \
				free/free_functions1.c \
				free/free_functions2.c \
				debugfolder/debug_tokens.c \
				debugfolder/debug_parser.c


SRC_FILES	:= $(addprefix $(SRC_DIR)/,$(SRCS))
OBJ_FILES	:= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

# ---- COLORS ----
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
RESET		:= \033[0m

# ---- RULES ----
all: $(LIBFT) $(NAME)

$(NAME): $(OBJ_FILES)
	@printf "$(BLUE)[LINK]$(RESET) $(NAME)\n"
	@$(CC) $(OBJ_FILES) $(LDFLAGS) -o $(NAME)
	@printf "$(GREEN)[OK] Minishell built successfully!$(RESET)\n"

# ---- BUILD LIBFT ----
$(LIBFT):
	@printf "$(BLUE)[LIBFT]$(RESET) Building libft...\n"
	@$(MAKE) -C $(LIBFT_DIR)

# ---- CREATE OBJ DIR AND SUBDIRS ----
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)[CC]$(RESET) $<\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(YELLOW)[CLEAN]$(RESET) Removing object files\n"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@printf "$(YELLOW)[FCLEAN]$(RESET) Removing executable and libft\n"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
