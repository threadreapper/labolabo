TARGETS = RefCounter
TEST_TARGETS = $(addprefix test_, $(TARGETS))

clean:
	rm -rf *.o *.a *_test

format:
	clang-format -style=Google -i `find . -regex ".*\.\(c\|h\)"`

check_style:
	clang-format -style=Google `find . -regex ".*\.\(c\|h\)"` --dry-run --Werror

tests: $(TEST_TARGETS)

valgrind: test_RefCounter
	valgrind --leak-check=full ./test_RefCounter

.PHONY: tests clean valgrind

define TARGET_RULES

$(1).o: $(1).c $(1).h
	gcc -g -c $(1).c -o $(1).o

$(1).a: $(1).o PoolAllocator.o
	ar rc $(1).a $(1).o PoolAllocator.o

$(1)_test.o: $(1)_test.c $(1).h
	gcc -g -c $(1)_test.c -o $(1)_test.o

test_$(1): $(1)_test.o $(1).a
	gcc -g -static -o test_$(1) $(1)_test.o $(1).a

endef

$(foreach target,$(TARGETS),$(eval $(call TARGET_RULES,$(target))))

PoolAllocator.o: PoolAllocator.c PoolAllocator.h
	gcc -g -c PoolAllocator.c -o PoolAllocator.o
