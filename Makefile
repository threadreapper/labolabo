TARGETS = RefCounter
TEST_TARGETS = $(addprefix test_, $(TARGETS))

clean:
	rm -rf *.o *.a *_test

check_style:
	clang-format -style=Google -i `find -regex ".+\.[ch]"` --dry-run --Werror

format:
	clang-format -style=Google -i `find -regex ".+\.[ch]"`

tests: $(TEST_TARGETS)

valgrind: test_RefCounter
	valgrind --leak-check=full ./test_RefCounter

.PHONY: tests clean valgrind

# Reference Counter

RefCounter.o: RefCounter.h RefCounter.c PoolAllocator.h PoolAllocator.c
	gcc -g -c RefCounter.c -o RefCounter.o

RefCounter.a: RefCounter.o
	ar rc RefCounter.a RefCounter.o

RefCounter_test.o: RefCounter_test.c
	gcc -g -c RefCounter_test.c -o RefCounter_test.o

RefCounter_test: RefCounter_test.o RefCounter.a
	gcc -g -static -o RefCounter_test RefCounter_test.o RefCounter.a

test_RefCounter: RefCounter_test
	./RefCounter_test
