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

define TARGET_RULES

$(1).o: $(1).c $(1).h
	gcc -g -c $(1).c -o $(1).o

$(1).a: $(1).o
	ar rc $(1).a $(1).o

$(1)_test.o: $(1)_test.c $(1).h
	gcc -g -c $(1)_test.c -o $(1)_test.o

$(1)_test: $(1)_test.o $(1).a
	gcc -g -o $(1)_test $(1)_test.o $(1).a

test_$(1): $(1)_test
    ./$(1)_test
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(1)_test

endef

$(foreach target,$(TARGETS),$(eval $(call TARGET_RULES,$(target))))