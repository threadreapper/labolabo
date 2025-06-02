TARGETS = RefCounter
TEST_TARGETS = $(addprefix test_, $(TARGETS))

clean:
	rm -rf *.o *.a *_test

check_style:
	clang-format -style=Google -i `find . -regex ".*\.\(c\|h\)"` --dry-run --Werror

format:
	clang-format -style=Google -i `find . -regex ".*\.\(c\|h\)"`

tests: $(TEST_TARGETS)

valgrind: test_RefCounter
	valgrind --leak-check=full ./test_RefCounter

.PHONY: tests clean valgrind

# Reference Counter

RefCounter.o: RefCounter.c RefCounter.h PoolAllocator.h
	gcc -g -c RefCounter.c -o RefCounter.o

PoolAllocator.o: PoolAllocator.c PoolAllocator.h
	gcc -g -c PoolAllocator.c -o PoolAllocator.o

RefCounter.a: RefCounter.o PoolAllocator.o
	ar rc RefCounter.a RefCounter.o PoolAllocator.o

RefCounter_test.o: RefCounter_test.c
	gcc -g -c RefCounter_test.c -o RefCounter_test.o

test_RefCounter: RefCounter_test.o RefCounter.a
	gcc -g -static -o test_RefCounter RefCounter_test.o RefCounter.a
