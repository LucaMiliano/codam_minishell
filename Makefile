# **************************************************************************** #
#                                   MINISHELL                                 #
# **************************************************************************** #

# ---- PROGRAM NAME ----
NAME        := minishell

# ---- DIRECTORIES ----
SRC_DIR     := src
OBJ_DIR     := obj
INC_DIR     := include

LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a
LIBFT_INC   := $(LIBFT_DIR)/include

# ---- COMPILER ----
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g3 -I$(INC_DIR) -I$(LIBFT_INC)

# ---- LIBRARIES ----
LDFLAGS     := -lreadline -L$(LIBFT_DIR) -lft

# ---- SOURCES ----
SRCS        :=  main.c \
                prompt.c

SRC_FILES   := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJ_FILES   := $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

# ---- COLORS ----
GREEN   := \033[1;32m
YELLOW  := \033[1;33m
BLUE    := \033[1;34m
RESET   := \033[0m

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
