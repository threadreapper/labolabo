STYLE = Google

SRC_DIR := src
TEST_DIR := tests

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
TARGETS := $(basename $(notdir $(filter-out %_test,$(SRC_FILES))))
TEST_TARGETS := $(foreach target,$(TARGETS),$(if $(wildcard $(TEST_DIR)/$(target)_test.c),test_$(target)))

CFLAGS := -g -Wall -Wextra -I$(SRC_DIR)
LDFLAGS := -lm

VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1

clean:
	rm -rf *.o *.a *_test *.d $(SRC_DIR)/*.o $(SRC_DIR)/*.d $(TEST_DIR)/*.o $(TEST_DIR)/*.d

check_style:
	clang-format -style=$(STYLE) -i `find . -regex ".*\.[ch]"` --dry-run --Werror

format:
	clang-format -style=$(STYLE) -i `find . -regex ".*\.[ch]"`

tests: $(TEST_TARGETS)

valgrind_tests: $(TEST_TARGETS:test_%=valgrind_%)

.PHONY: tests clean check_style format valgrind_tests

DEP_FILES := $(patsubst %.c,%.d,$(SRC_FILES) $(wildcard $(TEST_DIR)/*.c))
-include $(DEP_FILES)

define TARGET_RULES

$(SRC_DIR)/$(1).o: $(SRC_DIR)/$(1).c
	gcc $(CFLAGS) -c $$< -o $$@ -MMD -MP

$(1).a: $(SRC_DIR)/$(1).o
	ar rc $$@ $$^

endef

$(foreach target,$(TARGETS),$(eval $(call TARGET_RULES,$(target))))

define TEST_RULES

$(TEST_DIR)/$(1)_test.o: $(TEST_DIR)/$(1)_test.c
	gcc $(CFLAGS) -c $$< -o $$@ -MMD -MP

$(1)_test: $(TEST_DIR)/$(1)_test.o $(1).a
	gcc $(CFLAGS) -o $$@ $$^ $(LDFLAGS)

test_$(1): $(1)_test
	./$(1)_test

valgrind_$(1): $(1)_test
	valgrind $(VALGRIND_FLAGS) ./$(1)_test

endef

$(foreach target,$(TARGETS),$(if $(wildcard $(TEST_DIR)/$(target)_test.c),$(eval $(call TEST_RULES,$(target)))))
