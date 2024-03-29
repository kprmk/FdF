NAME = libft.a
COMPILER = gcc
FLAGS = -g -Wall -Wextra -Werror
INCLUDE_FOLDERS := -I includes/
SOURCES_FOLDER  := srcs/
OBJECTS_FOLDER  := objs/
# MLX := -lm -L/usr/lib/X11 -lmlx -lXext -lX11
MLX := -lmlx -framework OpenGL -framework AppKit

vpath %.c srcs
SOURCES :=	libft/aux.c \
			libft/checks_rounding.c \
			libft/print_other.c \
			libft/create_and_fill_list.c \
			libft/ft_itoa_base.c \
			libft/list.c \
			libft/print_unsigned.c \
			libft/fill_fields.c \
			libft/ft_itoa_long.c \
			libft/print_csp.c \
			libft/width.c \
			libft/flags.c \
			libft/ft_printf.c \
			libft/print_int.c \
			libft/print_elem.c \
			libft/printf_float.c \
			libft/int_aux.c \
			libft/int_aux2.c \
			libft/uint_aux.c \
			libft/align.c \
			libft/floats.c \
			libft/long_arithm_char.c \
			libft/long_arithm_char_2.c \
			libft/long_arithm.c \
			libft/parse_for_floats.c \
			libft/inf_nan.c \
			libft/ft_atoi.c \
			libft/ft_strmap.c \
			libft/ft_bzero.c \
			libft/ft_isalnum.c \
			libft/ft_isalpha.c \
			libft/ft_isascii.c \
			libft/ft_isdigit.c \
			libft/ft_isprint.c \
			libft/ft_memalloc.c \
			libft/ft_memccpy.c \
			libft/ft_memchr.c \
			libft/ft_memcmp.c \
			libft/ft_memcpy.c \
			libft/ft_memdel.c \
			libft/ft_memmove.c \
			libft/ft_memset.c \
			libft/ft_strcat.c \
			libft/ft_strchr.c \
			libft/ft_strclr.c \
			libft/ft_strcmp.c \
			libft/ft_strcpy.c \
			libft/ft_strdel.c \
			libft/ft_strdup.c \
			libft/ft_striter.c \
			libft/ft_striteri.c \
			libft/ft_strlcat.c \
			libft/ft_strlen.c \
			libft/ft_strncat.c \
			libft/ft_strncmp.c \
			libft/ft_strncpy.c \
			libft/ft_strnew.c \
			libft/ft_strnstr.c \
			libft/ft_strrchr.c \
			libft/ft_strstr.c \
			libft/ft_tolower.c \
			libft/ft_toupper.c \
			libft/ft_strmap.c \
			libft/ft_strmapi.c \
			libft/ft_strequ.c \
			libft/ft_strnequ.c \
			libft/ft_strsub.c \
			libft/ft_strjoin.c \
			libft/ft_spaces.c \
			libft/ft_spaces_rev.c \
			libft/ft_strisempty.c \
			libft/ft_strtrim.c \
			libft/ft_strsplit.c \
			libft/ft_free_split.c \
			libft/ft_itoa.c \
			libft/abs.c \
			libft/ft_putchar_fd.c \
			libft/ft_putstr_fd.c \
			libft/ft_putendl_fd.c \
			libft/ft_putchar.c \
			libft/ft_putstr.c \
			libft/ft_putendl.c \
			libft/ft_putnbr_fd.c \
			libft/ft_putnbr.c \
			libft/ft_lstnew.c \
			libft/ft_lstdelone.c \
			libft/ft_lstadd.c \
			libft/ft_lstdel.c \
			libft/ft_lstiter.c \
			libft/ft_lstmap.c \
			libft/ft_lstdelone_s.c \
			libft/ft_lstnew_fd.c \
			libft/ft_strjoin_s.c \
			libft/get_next_line.c \


OBJECTS := $(SOURCES:.c=.o)

OBJECTS := $(addprefix $(OBJECTS_FOLDER), $(OBJECTS))
SOURCES := $(addprefix $(SOURCES_FOLDER), $(SOURCES))

all: $(NAME)
	@$(CC) $(FLAGS) srcs/*.c $(MLX) $(INCLUDE_FOLDERS) srcs/$(NAME) -o fdf

$(NAME): $(OBJECTS)
	@ar rcs srcs/$(NAME) $(OBJECTS)

$(DIR_O)/%.o: $(DIR_S)/%.c
	@mkdir -p obj
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

objs/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDE_FOLDERS) -c $< -o $@

clean:
	@rm -rf $(OBJECTS)
	@rm -rf objs
	@rm -rf libft
	
fclean: clean
	@rm -f srcs/$(NAME)
	@rm -f fdf

re: fclean all

all: $(NAME)