TARGETS = PoolAllocator hash_table
TEST_TARGETS = $(addprefix test_, $(TARGETS))

clean:
	rm -rf *.o *.a *_test

check_style:
	clang-format -style=LLVM -i find . -regex ".*\.[ch]" --dry-run --Werror

format:
	clang-format -style=LLVM -i find . -regex ".*\.[ch]"

tests: $(TEST_TARGETS)

.PHONY: tests clean

# Pool Allocator
PoolAllocator.o: PoolAllocator.h PoolAllocator.c
	gcc -g -c PoolAllocator.c -o PoolAllocator.o

PoolAllocator.a: PoolAllocator.o
	ar rc PoolAllocator.a PoolAllocator.o

# Hash Table with Pool Allocator
hash_table.o: hash_table.h hash_table.c PoolAllocator.h
	gcc -g -c hash_table.c -o hash_table.o

hash_table.a: hash_table.o
	ar rc hash_table.a hash_table.o

hash_table_test.o: hash_table_test.c hash_table.h PoolAllocator.h
	gcc -g -c hash_table_test.c -o hash_table_test.o

hash_table_test: hash_table_test.o hash_table.a PoolAllocator.a
	gcc -g -static -o hash_table_test hash_table_test.o hash_table.a PoolAllocator.a -lm

test_hash_table: hash_table_test
	./hash_table_test
