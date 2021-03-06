NAME         = ft_nm ft_otool
CFLAGS      += -g -Wall -Wextra
CFLAGS      += -std=c11 -pedantic -pedantic-errors

ifeq ($(DEBUG),yes)
	CFLAGS  += -g3 -O0 -fno-inline
else
	CFLAGS  += -O2 -DNDEBUG
endif
ifeq ($(SAN),yes)
	CFLAGS	+= -fsanitize=address
	LDFLAGS += -fsanitize=address
endif

# Headers
CFLAGS    += -I./inc

# Sources
SRC_PATH    = src

SOURCES     = $(COM_SOURCES) $(NAME:%=%.c)
# Generation
vpath %.c $(SRC_PATH) $(addprefix $(SRC_PATH)/,$(SRC_SUBDIR))
OBJ_PATH    = .obj
COM_OBJECTS = $(COM_SOURCES:%.c=$(OBJ_PATH)/%.o)
OBJECTS     = $(SOURCES:%.c=$(OBJ_PATH)/%.o)
DEP_PATH    = .dep
DEPS        = $(SOURCES:%.c=$(DEP_PATH)/%.d)
BUILD_DIR   = $(OBJ_PATH) $(DEP_PATH)

# Libft
LIBFT_PATH = libft
LIBFT      = $(LIBFT_PATH)/libft.a
CFLAGS    += -I $(LIBFT_PATH)/inc
LDFLAGS   += -L $(LIBFT_PATH) -lft

TEST_C = 00_test_facile.c 01_test_moins_facile.c
TEST_H = x06_random.xxd
TEST_DIR = test
EXEC_C = $(TEST_C:%.c=$(TEST_DIR)/%.out) 
EXEC_H = $(TEST_H:%.xxd=$(TEST_DIR)/%.out)
TESTS    = $(EXEC_C) $(EXEC_H)

.SECONDARY: $(OBJECTS)

all: $(DEPS) $(NAME)

-include $(DEPS)

$(NAME): %:$(OBJ_PATH)/%.o $(COM_OBJECTS) | $(LIBFT)
	$(CC) $(LDFLAGS) -o $@ $^

$(LIBFT):
	@$(MAKE) -q -C $(LIBFT_PATH) || echo $(MAKE) -C $(LIBFT_PATH) && \
		$(MAKE) -C $(LIBFT_PATH)

$(OBJECTS): $(OBJ_PATH)/%.o: %.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $<

$(DEP_PATH)/%.d: %.c | $(DEP_PATH)
	$(CC) $(CFLAGS) -MM $< -MT $(OBJ_PATH)/$*.o -MF $@

$(BUILD_DIR):
	mkdir -p $@

$(EXEC_C): %.out:%.c
	$(CC) -o $@ $<

$(EXEC_H): %.out:%.xxd
	cat $< | cut '-d#' -f1 | xxd -r -p > $@ && chmod 755 $@

check: $(NAME) $(TESTS)
	./run_tests.sh

clean:
	$(RM) -rf $(OBJ_PATH) $(DEP_PATH) $(TESTS)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	$(RM) -rf $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all $(LIBFT) clean fclean re check
