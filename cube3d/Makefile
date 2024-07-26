NAME = cub3D

SRC_C =	tools/ft_isnum.c \
		tools/ft_split.c \
		tools/ft_strcmp.c \
		tools/ft_strncmp.c \
		tools/ft_atoi.c \
		tools/ft_strdup.c \
		tools/ft_is_space.c \
		tools/ft_strlen.c \
		tools/ft_substr.c \
		tools/ft_strjoin.c \
		tools/ft_strjoinx.c \
		tools/ft_strchr.c \
		tools/cpy_map.c \
		tools/utils1.c \
		check_map_contant.c \
		check_map.c \
		check_name.c \
		check_textures_and_colors.c \
		error.c \
		execution.c \
		ft_get_next_line.c \
		main.c \
		parsing.c \
		readfilecontant.c \
		parsing_utilitis.c \
		parsing_utilitis2.c \
		parsing_utilitis3.c \
		parsing_utilitis4.c \
		execution_utilities.c \

COMPILER = cc

FLAGS = -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3

OBJC = $(SRC_C:.c=.o)

all: $(NAME)

$(NAME): $(OBJC)
	$(COMPILER) $(OBJC) -L../mlx -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o : %.c cub3d.h
	$(COMPILER) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	rm -rf $(OBJC) $(OBJ_BC)

fclean: clean
	rm -rf $(NAME) $(BONUS_NAME)

re: fclean all