TEST_TARGETS = $(addprefix test_, $(TARGETS))
fmt:
	find . -regex '.*\.[ch]' -exec clang-format -style=LLVM -i {} +
check_fmt:
	find . -regex '.*\.[ch]' -exec clang-format -style=LLVM --dry-run --Werror {} +

tests: $(TEST_TARGETS)

run:
	find . -name "Makefile" -execdir make -f {} \;
	if find . -type f -name "*_test" -exec sh -c '{} && echo "тест пройден успешно"' \; ; then \
		echo "Все тесты выполнены."; \
	else \
		echo "Тесты не найдены."; \
		fi

clean:
	rm -rf *.o *.a *_test

check_style:
	clang-format -style=Google -i `find -regex ".+\.[ch]"` --dry-run --Werror

format:
	clang-format -style=Google -i `find -regex ".+\.[ch]"`

tests: $(TEST_TARGETS)

.PHONY: tests clean

# LinkedList Operations

LinkedListOps.o: LinkedListOps.h LinkedListOps.c
	gcc -g -c LinkedListOps.c -o LinkedListOps.o

LinkedListOps.a: LinkedListOps.o
	ar rc LinkedListOps.a LinkedListOps.o

LinkedListOps_test.o: LinkedListOps_test.c
	gcc -g -c LinkedListOps_test.c -o LinkedListOps_test.o

LinkedListOps_test: LinkedListOps_test.o LinkedListOps.a
	gcc -g -static -o LinkedListOps_test LinkedListOps_test.o LinkedListOps.a

test_LinkedListOps: LinkedListOps_test
	./LinkedListOps_test
