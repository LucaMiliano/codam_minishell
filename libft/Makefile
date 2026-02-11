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

SRC_FILES   = src/ft_atoi.c src/ft_atoi_base.c src/ft_atol.c src/ft_bzero.c src/ft_calloc.c src/ft_free_split.c src/ft_isalnum.c src/ft_isalpha.c src/ft_isascii.c src/ft_isdigit.c src/ft_isprint.c src/ft_itoa.c src/ft_lstadd_back.c src/ft_lstadd_front.c src/ft_lstclear.c src/ft_lstdelone.c src/ft_lstiter.c src/ft_lstlast.c src/ft_lstmap.c src/ft_lstnew.c src/ft_lstsize.c src/ft_memchr.c src/ft_memcmp.c src/ft_memcpy.c src/ft_memmove.c src/ft_memset.c src/ft_putchar_fd.c src/ft_putendl_fd.c src/ft_putnbr_fd.c src/ft_putstr_fd.c src/ft_split.c src/ft_strchr.c src/ft_strdup.c src/ft_striteri.c src/ft_strjoin.c src/ft_strjoin_char.c src/ft_strlcat.c src/ft_strlcpy.c src/ft_strlen.c src/ft_strmapi.c src/ft_strncmp.c src/ft_strnstr.c src/ft_strrchr.c src/ft_strtrim.c src/ft_substr.c src/ft_tolower.c src/ft_toupper.c
LIB_FILES   = lib/ft_hex_specifier.c lib/ft_itoahex.c lib/ft_printf.c lib/ft_putchar.c lib/ft_putnbr.c lib/ft_putnbr_unsigned.c lib/ft_putstr.c lib/ft_strlenn.c lib/ft_strncpyy.c lib/ft_strrevv.c lib/ft_toupperr.c

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

