NAME = wolf3d
OBJS = objs/main.o objs/map_reader.o objs/redraw.o objs/redraw2.o objs/loop_hooks.o objs/key_hooks.o objs/error.o
HEADERS = includes libft/includes minilibx_macos
HEADERS2 = includes/wolf3d.h libft/includes/libft.h minilibx_macos/mlx.h
LIBFT = libft/libft.a
LIBMLX = minilibx_macos/libmlx.a
CFLAGS = -Wall -Wextra -Werror
FRAMEWORKS = -framework Appkit -framework OpenGL

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	gcc $(CFLAGS) -I libft/includes -I minilibx_macos $(OBJS) $(LIBFT) $(LIBMLX) -o $(NAME) $(FRAMEWORKS)

$(OBJS): objs/%.o: srcs/%.c $(HEADERS2) objs
	gcc $(CFLAGS) -I libft/includes -I minilibx_macos -c $< -o $@

objs:
	mkdir objs

$(LIBFT):
	make -C libft

$(LIBMLX):
	make -C minilibx_macos

clean:
	rm -rf objs
	make clean -C libft
	make clean -C minilibx_macos

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY : all clean fclean re