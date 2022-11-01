CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
INCLUDE_PATH=.
CCF_INCLUDES = -I $(INCLUDE_PATH)

ORIGINAL_LIBFT_SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c\
ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c\
ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c\
ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c\
ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c\
ft_strmapi.c ft_striteri.c
#ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

WRITE_SRCS = write/ft_putchar.c write/ft_putchar_fd.c write/ft_putendl_fd.c write/ft_putnbase.c write/ft_putnbr_fd.c write/ft_putstr.c write/ft_putstr_fd.c write/ft_putstrn.c

GET_NEXT_LINE_SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

FT_PRITF_SRCS = ft_printf/ft_printf.c ft_printf/deal.c\
				ft_printf/conversions/char.c ft_printf/conversions/string.c ft_printf/conversions/pointer.c ft_printf/conversions/decimal.c ft_printf/conversions/int.c ft_printf/conversions/unsigned.c ft_printf/conversions/hexadecimal.c ft_printf/conversions/percent.c\
				ft_printf/slot/slot.c ft_printf/slot/utils.c\

SRCS = $(ORIGINAL_LIBFT_SRCS) $(GET_NEXT_LINE_SRCS) $(FT_PRITF_SRCS) $(WRITE_SRCS)
OBJS = $(SRCS:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $@ $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) $(CCF_INCLUDES) -c $< -o $@

norm:
	norminette $(SRCS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all
