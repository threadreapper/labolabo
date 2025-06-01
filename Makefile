TARGETS = StackOps
TEST_TARGETS = $(addprefix test_, $(TARGETS))

clean:
    rm -rf *.o *.a *_test

check_fmt:
    clang-format -style=Google -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
    clang-format -style=Google -i `find -regex ".+\.[ch]"`

tests: $(TEST_TARGETS)

.PHONY: tests clean

# Stack Operations

StackOps.o: StackOps.h StackOps.c
    gcc -g -c StackOps.c -o StackOps.o

StackOps.a: StackOps.o
    ar rc StackOps.a StackOps.o

StackOps_test.o: StackOps_test.c
    gcc -g -c StackOps_test.c -o StackOps_test.o

StackOps_test: StackOps_test.o StackOps.a
    gcc -g -static -o StackOps_test StackOps_test.o StackOps.a

test_StackOps: StackOps_test
    ./StackOps_test
