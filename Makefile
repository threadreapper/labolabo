TARGETS = PoolAllocator
TEST_TARGETS = $(addprefix test_, $(TARGETS))

clean:
    rm -rf *.o *.a *_test

check_style:
    clang-format -style=Google -i `find -regex ".+\.[ch]"` --dry-run --Werror

format:
    clang-format -style=Google -i `find -regex ".+\.[ch]"`

tests: $(TEST_TARGETS)

.PHONY: tests clear

# Pool Allocator

PoolAllocator.o: PoolAllocator.h PoolAllocator.c
    gcc -g -c PoolAllocator.c -o PoolAllocator.o

PoolAllocator.a: PoolAllocator.o
    ar rc PoolAllocator.a PoolAllocator.o

PoolAllocator_test.o: PoolAllocator_test.c
    gcc -g -c PoolAllocator_test.c -o PoolAllocator_test.o

PoolAllocator_test: PoolAllocator_test.o PoolAllocator.a
    gcc -g -static -o PoolAllocator_test PoolAllocator_test.o PoolAllocator.a -lm

test_PoolAllocator: PoolAllocator_test
    ./PoolAllocator_test
