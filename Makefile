AUTHORS	= dantonik, tdehne
DATE	= $$(date +%Y/%m/%d)
BUSER = ~/.brew/opt/glfw/lib/

CC			=	cc
CFLAGS		=	-Werror -Wextra -Wall

NAME 		=	miniRT

OBJ_DIR		=	obj/
SRC_DIR		=	src/
INC_DIR		=	include/
LIBA = MLX42/build/libmlx42.a

GNL_DIR = ./get_next_line/
GNL = ./get_next_line/gnl.a

SRC_NAME	=	main init vector/vector vector/vector_2 vector/vector_3 vector/vector_4 \
				hit light color_utils color_room \
				utils/utils utils/utils_2  utils/main_utils utils/create utils/error_handling \
				parser/parser parser/string_utils parser/parse_float parser/parse_skip parser/parse_skip2 \
				parser/parse_get parser/parse_check parser/parse_print parser/parse_print2 \
				parser/parse_get_obj hit_quadratic light_utils rotation keyhooks keyhooks_utils
INC_NAME	=	miniRT vector structs parser

SRC_FILES	=	$(addsuffix .c, $(addprefix $(SRC_DIR), $(SRC_NAME)))
OBJ_FILES	=	$(addsuffix .o, $(addprefix $(OBJ_DIR), $(SRC_NAME)))
INC_FILES	=	$(addsuffix .h, $(addprefix $(INC_DIR), $(INC_NAME)))

ifeq ($(shell uname -s),Linux)
	OS := Linux
	LIB	=	-ldl -lglfw -pthread -lm
else ifeq ($(shell uname -s),Darwin)
	ifeq ($(shell uname -p),arm)
		OS := MacOS silicone
		LIB		=	-framework Cocoa -framework OpenGL -framework IOKit -lglfw -L /opt/homebrew/Cellar/glfw/3.3.8/lib/
	else
		OS := MacOS intel
		LIB		=	-framework Cocoa -framework OpenGL -framework IOKit -lglfw -L ~/.brew/opt/glfw/lib/
	endif
else
	OS := Unknown
	exit 1
endif

$(info Compiling for $(OS))

all : $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parser
	@mkdir -p $(OBJ_DIR)/vector
	@mkdir -p $(OBJ_DIR)/utils

$(GNL):
	@make -C $(GNL_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -I$(INC_DIR) -o $@ -IMLX42/include
#
$(NAME) : $(GNL) $(OBJ_DIR) $(OBJ_FILES) $(INC_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME) $(LIBA) $(LIB) -I$(INC_DIR) $(GNL)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(GNL_DIR)

fclean: clean
	@rm -f $(NAME) .header
	@make fclean -C $(GNL_DIR)

re: fclean all

