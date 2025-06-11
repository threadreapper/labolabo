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

.PHONY: tests clean check_style format

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
$(1)_test: $(1)_test.o $(1).a PoolAllocator.a
	gcc -g -static -o $(1)_test $(1)_test.o $(1).a PoolAllocator.a -lm
test_$(1): $(1)_test
	./$(1)_test
endef

$(foreach target,$(TARGETS),$(if $(wildcard $(target)_test.c),$(eval $(call TEST_RULES,$(target)))))
