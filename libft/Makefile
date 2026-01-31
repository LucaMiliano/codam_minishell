# **************************************************************************** #
#                                 MAKEFILE                                     #
# **************************************************************************** #

NAME        = libft.a
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
AR          = ar
ARFLAGS     = rcs

INCLUDES    = -Iinclude

SRC_DIR     = src
LIB_DIR     = lib
OBJ_DIR     = obj

SRC_FILES   = $(wildcard $(SRC_DIR)/*.c)
LIB_FILES   = $(wildcard $(LIB_DIR)/*.c)
ALL_SRC     = $(SRC_FILES) $(LIB_FILES)

# Generate object file names in obj/ directory
OBJ         = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(ALL_SRC)))

all: $(NAME)

# Recreate archive from scratch every time
$(NAME): $(OBJ)
	rm -f $(NAME)             # Remove old archive so we start fresh
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

# Compile src/ and lib/ sources into obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

