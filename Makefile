NAME         = ft_nm ft_otool
CFLAGS      += -g -Wall -Wextra -Werror
CFLAGS      += -std=c11 -pedantic -pedantic-errors

ifeq ($(DEBUG),yes)
	CFLAGS  += -g3 -O0 -fno-inline -DNOT_CORRECTION
else
	CFLAGS  += -O2
endif
ifeq ($(SAN),yes)
	CFLAGS	+= -fsanitize=address
	LDFLAGS += -fsanitize=address
endif
CFLAGS  += $(TMP_CFLAGS)

# Headers
CFLAGS    += -I./inc

COM_SOURCES = common/misc.c common/file.c common/fat.c common/fat_init.c \
			  common/type.c common/arch.c common/ar.c common/ar_err.c \
			  common/ar_tools.c ft_nm_parse_opt.c ft_nm_mach.c ft_nm_ar.c \
			  ft_nm_fat.c common/mach_o.c common/mach_o_err.c \
			  common/is_mach_o.c ft_nm_output.c common/mach_o_lc.c \
			  common/mach_o_symtab.c common/mach_o_section.c common/fat_iter.c \
			  common/mach_o_err2.c common/ar_err2.c common/file2.c \
			  ft_otool_ar.c ft_otool_fat.c ft_otool_mach.c ft_otool_parse_opt.c

# Sources
SRC_PATH    = src

SOURCES     = $(COM_SOURCES) $(NAME:%=%.c)
# Generation
vpath %.c $(SRC_PATH) $(addprefix $(SRC_PATH)/,$(SRC_SUBDIR))
OBJ_PATH    = .obj
COM_OBJECTS = $(COM_SOURCES:%.c=$(OBJ_PATH)/%.o)
OBJECTS     = $(SOURCES:%.c=$(OBJ_PATH)/%.o)
DEP_PATH    = .dep/
DEPS        = $(SOURCES:%.c=$(DEP_PATH)/%.d)
BUILD_DIR   = $(OBJ_PATH) $(OBJ_PATH)/common \
			  $(DEP_PATH)/common $(DEP_PATH)

# Libft
LIBFT_PATH = libft
LIBFT      = $(LIBFT_PATH)/libft.a
CFLAGS    += -I $(LIBFT_PATH)/inc
LDFLAGS   += -L $(LIBFT_PATH) -lft

#TEST_C = 00_test_facile.c 01_test_moins_facile.c
#TEST_H = x06_random.xxd
TEST_DIR = test
TEST_H = $(shell cd $(TEST_DIR) && find . -name '*.xxd')
EXEC_C = $(TEST_C:%.c=$(TEST_DIR)/%.out) 
EXEC_H = $(TEST_H:%.xxd=$(TEST_DIR)/%.out)
TESTS    = $(EXEC_C) $(EXEC_H) $(TEST_DIR)/999_no_read_rights.out

.SECONDARY: $(OBJECTS)

all: $(DEPS) $(NAME)

-include $(DEPS)

$(NAME): %:$(OBJ_PATH)/%.o $(COM_OBJECTS) $(LIBFT)
	$(CC) $(LDFLAGS) -o $@ $^

$(LIBFT):
	@$(MAKE) -q -C $(LIBFT_PATH) || echo $(MAKE) -C $(LIBFT_PATH) && \
		$(MAKE) -j8 -C $(LIBFT_PATH)

$(OBJECTS): $(OBJ_PATH)/%.o: %.c | $(OBJ_PATH)/common
	$(CC) $(CFLAGS) -o $@ -c $<

$(DEP_PATH)/%.d: %.c | $(DEP_PATH)/common
	$(CC) $(CFLAGS) -MM $< -MT $(OBJ_PATH)/$*.o -MF $@

$(BUILD_DIR):
	mkdir -p $@

$(EXEC_C): %.out:%.c
	$(CC) -o $@ $<

$(EXEC_H): %.out:%.xxd
	cat $< | cut '-d#' -f1 | xxd -r -p > $@ && chmod 755 $@

$(TEST_DIR)/999_no_read_rights.out:
	touch $@ && chmod 100 $@

check: $(NAME) $(TESTS)
	./run_tests.sh

tests: $(TESTS)

clean:
	$(RM) -rf $(OBJ_PATH) $(DEP_PATH) $(TESTS)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	$(RM) -f $(NAME) $(EXEC_C) $(EXEC_H)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re check tests $(LIBFT)
