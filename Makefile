NAME = griddy.a

SRCS = griddy.c \
	griddies.c \
	configuration_utilities.c \
	connection_handlers.c \
	constructors.c

OBJS = $(SRCS:.c=.o)

OBJS_DIR = build
SRCS_DIR = srcs
LIBS_DIR = libs
OBJS_PATH = $(addprefix $(OBJS_DIR)/, $(OBJS))
SRCS_PATH = $(addprefix $(SRCS_DIR)/, $(SRCS))

INCLUDES = includes libs/cdata_structures/includes libs/centropy/includes
INCLUDES_FLAGS = $(addprefix -I, $(INCLUDES))

FLAGS = #-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS_PATH)
	make -C $(LIBS_DIR)/centropy
	ar rc $(NAME) $(OBJS_PATH)
	ranlib $(NAME)

$(OBJS_PATH): $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	gcc $(FLAGS) -I$(INCLUDES_FLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all