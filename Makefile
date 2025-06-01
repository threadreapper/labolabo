TARGETS = LinearAllocator
TEST_TARGETS = $(addprefix test_, $(TARGETS))

clean:
    rm -rf *.o *.a *_test

check_style:
    clang-format -style=Google -i `find -regex ".+\.[ch]"` --dry-run --Werror

format:
    clang-format -style=Google -i `find -regex ".+\.[ch]"`

tests: $(TEST_TARGETS)

.PHONY: tests clean

# Linear Allocator

LinearAllocator.o: LinearAllocator.h LinearAllocator.c
    gcc -g -c LinearAllocator.c -o LinearAllocator.o

LinearAllocator.a: LinearAllocator.o
    ar rc LinearAllocator.a LinearAllocator.o

LinearAllocator_test.o: LinearAllocator_test.c
    gcc -g -c LinearAllocator_test.c -o LinearAllocator_test.o

LinearAllocator_test: LinearAllocator_test.o LinearAllocator.a
    gcc -g -static -o LinearAllocator_test LinearAllocator_test.o LinearAllocator.a -lm

test_LinearAllocator: LinearAllocator_test
    ./LinearAllocator_test
