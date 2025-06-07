# Define targets
TARGETS = StackOps
TEST_TARGETS = $(addprefix test_, $(TARGETS))

# Clean up build artifacts
clean:
	rm -rf *.o *.a *_test

# Format source code using clang-format
fmt:
	find . -regex '.*\.[ch]' -exec clang-format -style=Google -i {} +

# Check formatting without modifying files
check_fmt:
	clang-format -style=Google -i `find -regex ".+\.[ch]"` --dry-run --Werror

# Build and run tests
tests: $(TEST_TARGETS)

run:
	find . -name "Makefile" -execdir make -f {} \;
	if find . -type f -name "*_test" -exec sh -c '{} && echo "тест пройден успешно"' \; ; then \
		echo "Все тесты выполнены."; \
	else \
		echo "Тесты не найдены."; \
	fi

# Declare phony targets
.PHONY: tests clean fmt check_fmt run

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
