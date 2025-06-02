TARGETS = CycleDetector
TEST_TARGETS = $(addprefix test_, $(TARGETS))

clean:
	rm -rf *.o *.a *_test

format:
	clang-format -style=Google -i `find . -regex ".*\.\(c\|h\)"`

check_fmt:
	clang-format -style=Google `find . -regex ".*\.\(c\|h\)"` --dry-run --Werror

tests: $(TEST_TARGETS)

valgrind: test_CycleDetector
	which valgrind || (echo "Error: Valgrind is not installed. Please install it and try again." && exit 1)
	test -f ./CycleDetector_test || (echo "Error: Executable 'CycleDetector_test' not found. Run 'make' first." && exit 1)
	valgrind --leak-check=full ./CycleDetector_test

.PHONY: tests clean valgrind format check_fmt

# Cycle Detector

CycleDetector.o: CycleDetector.c CycleDetector.h
	gcc -g -c CycleDetector.c -o CycleDetector.o

CycleDetector.a: CycleDetector.o
	ar rc CycleDetector.a CycleDetector.o

CycleDetector_test.o: CycleDetector_test.c
	gcc -g -c CycleDetector_test.c -o CycleDetector_test.o

CycleDetector_test: CycleDetector_test.o CycleDetector.a
	gcc -g -o CycleDetector_test CycleDetector_test.o CycleDetector.a

test_CycleDetector: CycleDetector_test
	./CycleDetector_test
