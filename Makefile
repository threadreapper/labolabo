STYLE = Google

SRC_FILES := $(wildcard *.c)
TARGETS := $(basename $(filter-out %_test,$(SRC_FILES)))
TEST_TARGETS := $(foreach target,$(TARGETS),$(if $(wildcard $(target)_test.c),test_$(target)))

clean:
	rm -rf *.o *.a *_test *.d

check_style:
	clang-format -style=$(STYLE) -i `find . -regex ".*\.[ch]"` --dry-run --Werror

format:
	clang-format -style=$(STYLE) -i `find . -regex ".*\.[ch]"`

tests: $(TEST_TARGETS)

valgrind: $(TEST_TARGETS)
	@echo "Running Valgrind memory checks..."
	@for test in $(TEST_TARGETS); do \
		echo "Checking $$test with Valgrind..."; \
		valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 --errors-for-leak-kinds=all ./$$test || exit 1; \
	done
	@echo "All tests passed Valgrind checks successfully!"

.PHONY: tests clean check_style format valgrind

DEP_FILES := $(patsubst %.c,%.d,$(SRC_FILES))
-include $(DEP_FILES)

define TARGET_RULES

$(1).o: $(1).c
	gcc -g -c $(1).c -o $(1).o -MMD -MP

$(1).a: $(1).o
	ar rc $(1).a $(1).o

endef

$(foreach target,$(TARGETS),$(eval $(call TARGET_RULES,$(target))))

define TEST_RULES

$(1)_test.o: $(1)_test.c
	gcc -g -c $(1)_test.c -o $(1)_test.o -MMD -MP

$(1)_test: $(1)_test.o $(1).a
	gcc -g -static -o $(1)_test $(1)_test.o $(1).a -lm

test_$(1): $(1)_test
	./$(1)_test

endef

$(foreach target,$(TARGETS),$(if $(wildcard $(target)_test.c),$(eval $(call TEST_RULES,$(target)))))
