TARGETS = ObjectManager
TEST_TARGETS = $(addprefix test_, $(TARGETS))

clean:
	rm -rf *.o *.a *_test

format:
	clang-format -style=Google -i `find . -regex ".*\.\(c\|h\)"`

check_style:
	clang-format -style=Google `find . -regex ".*\.\(c\|h\)"` --dry-run --Werror

tests: $(TEST_TARGETS)

valgrind: test_ObjectManager
	which valgrind || (echo "Error: Valgrind is not installed. Please install it and try again." && exit 1)
	test -f ./ObjectManager_test || (echo "Error: Executable 'ObjectManager_test' not found. Run 'make' first." && exit 1)
	valgrind --leak-check=full ./ObjectManager_test

.PHONY: tests clean valgrind

# Object Manager

ObjectManager.o: ObjectManager.c ObjectManager.h
	gcc -g -c ObjectManager.c -o ObjectManager.o

ObjectManager.a: ObjectManager.o
	ar rc ObjectManager.a ObjectManager.o

ObjectManager_test.o: ObjectManager_test.c
	gcc -g -c ObjectManager_test.c -o ObjectManager_test.o

ObjectManager_test: ObjectManager_test.o ObjectManager.a
	gcc -g -o ObjectManager_test ObjectManager_test.o ObjectManager.a

test_ObjectManager: ObjectManager_test
	./ObjectManager_test
