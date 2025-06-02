TASKS = dynamic_array
TEST_EXECUTABLES = $(addprefix test_, $(TASKS))

clean:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

tests: $(TEST_EXECUTABLES)

.PHONY: tests clean

# Dynamic Array

LinearAllocator.o: LinearAllocator.h LinearAllocator.c
	gcc -g -c LinearAllocator.c -o LinearAllocator.o

dynamic_array.o: dynamic_array.h dynamic_array.c LinearAllocator.h
	gcc -g -c dynamic_array.c -o dynamic_array.o

dynamic_array.a: dynamic_array.o LinearAllocator.o
	ar rc dynamic_array.a dynamic_array.o LinearAllocator.o

dynamic_array_test.o: dynamic_array_test.c dynamic_array.h LinearAllocator.h
	gcc -g -c dynamic_array_test.c -o dynamic_array_test.o

dynamic_array_test: dynamic_array_test.o dynamic_array.a
	gcc -g -static -o dynamic_array_test dynamic_array_test.o dynamic_array.a -lm

test_dynamic_array: dynamic_array_test
	./dynamic_array_test
