NAME			=	cub3d
NAME_BONUS		=	cub3d_bonus

HEADER			=	cub3d.h cub3d_structs.h

GCC				=	gcc -g3 -Wall -Wextra -Werror

DIR_LIBA		=	libft/
DIR_MINILIBX	=	mlx/
DIR_UTILS		=	utils/
DIR_MAP			=	cub_file/
DIR_GNL			=	get_next_line/
DIR_MANDATORY	=	mandatory/
DIR_BONUS		=	bonus/

SRC				=	main.c screen.c minimap.c texture.c motion.c sprites.c hook.c
SRC_UTILS		=	utils0.c utils1.c utils2.c utils3.c
SRC_MAP			=	read_map.c read_map_param.c checking_map_for_closure.c \
					cub_file.c color_param.c cub_file_utils.c make_map_mas.c write_map_list.c
SRC_GNL			=	get_next_line.c get_next_line_utils.c

SRC_BONUS		=	main.c screen.c minimap.c texture.c motion.c sprites.c hook.c fog_bonus.c screenshot_bonus.c screenshot_utils_bonus.c

UTILS			=	$(addprefix $(DIR_UTILS), $(SRC_UTILS))
MAP				=	$(addprefix $(DIR_MAP), $(SRC_MAP))
GNL				=	$(addprefix $(DIR_GNL), $(SRC_GNL))
BONUS			=	$(addprefix $(DIR_BONUS), $(SRC_BONUS))
MANDATORY		=	$(addprefix $(DIR_MANDATORY), $(SRC))

OBJ				=	$(MANDATORY:.c=.o) $(UTILS:.c=.o) $(MAP:.c=.o) $(GNL:.c=.o) $(LIBA:.c=.o)
OBJ_BONUS		=	$(BONUS:.c=.o) $(UTILS:.c=.o) $(MAP:.c=.o) $(GNL:.c=.o) $(LIBA:.c=.o)

all				:	mlx libft $(NAME) 

bonus			:	mlx libft $(NAME_BONUS) 
					
%.o				:	%.c $(HEADER)
					$(GCC) -I mlx -c $< -o $@

$(NAME)			:	$(OBJ)
					make -C mlx/
#					@echo "\033[0;35mКомпилю cub3d...\033[0;32m"
#					@echo "\033[0;35mСоздаю исполняемый файл...\033[0;32m"
					$(GCC) -o $(NAME) $(OBJ) libft/libft.a -Lmlx -lmlx -framework OpenGL -framework AppKit

$(NAME_BONUS)	:	$(OBJ_BONUS)
					make -C mlx/
					$(GCC) -o $(NAME_BONUS) $(OBJ_BONUS) libft/libft.a -Lmlx -lmlx -framework OpenGL -framework AppKit

xpm				:	mlx
					$(GCC) xpm_viewer.c -o xpm_viewer -Lmlx -lmlx -framework OpenGL -framework AppKit

mlx				:
#					@echo "\033[0;35mКомпилю minilibx... \033[0;32m"
					make -C mlx/
libft			:
#					@echo "\033[0;35mКомпилю libft... \033[0;32m"
					make -C $(DIR_LIBA)


clean			:
#					@echo "\033[0;35mУдаляю объектные файлы...\033[0;31m"
					make clean -C $(DIR_LIBA)
					make clean -C $(DIR_MINILIBX)
#					@echo "\033[0;35mcub3d: ЧИСТКА ОБЪЕКТНИКОВ...\033[0;31m"
					rm -f $(OBJ)
					rm -f $(OBJ_BONUS)

fclean			:	clean
#					@echo "\033[0;35mУдаляю исполняемый файл...\033[0;31m"
					rm -f $(NAME)
					rm -f $(NAME_BONUS)
#					make fclean -C $(DIR_LIBA)
#					make clean -C $(DIR_MINILIBX)

re				:	fclean all

.PHONY			:	all libft clean fclean re
