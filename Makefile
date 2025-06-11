TARGETS = ObjectManager CycleDetector RefCounter
TEST_TARGETS = $(addprefix test_, $(TARGETS))

clean:
	rm -rf *.o *.a *_test

format:
	clang-format -style=Google -i `find . -regex ".*\.\(c\|h\)"`

check_style:
	clang-format -style=Google `find . -regex ".*\.\(c\|h\)"` --dry-run --Werror

tests: $(TEST_TARGETS)

valgrind: $(TEST_TARGETS)
	@which valgrind > /dev/null 2>&1 || (echo "Error: Valgrind is not installed. Skipping valgrind tests." && exit 0)
	for test_target in $(TEST_TARGETS); do \
		if [ -f "./$(test_target)" ]; then \
			echo "Running valgrind for $(test_target)..."; \
			valgrind --leak-check=full ./$$test_target; \
		else \
			echo "Skipping valgrind for $(test_target): executable not found."; \
		fi \
	done

define TARGET_RULES

ifneq (,$(wildcard src/$(1).c))
$(1).o: src/$(1).c src/$(1).h
	gcc -g -c src/$(1).c -o $(1).o
else
$(1).o:
	@echo "Skipping $(1).o: src/$(1).c not found"
endif

ifneq (,$(wildcard src/$(1).c))
$(1).a: $(1).o
ifeq ($(1),RefCounter)
	ar rc $(1).a $(1).o PoolAllocator.o
else
	ar rc $(1).a $(1).o
endif
else
$(1).a:
	@echo "Skipping $(1).a: src/$(1).c not found"
endif

ifneq (,$(wildcard tests/$(1)_test.c))
$(1)_test.o: tests/$(1)_test.c src/$(1).h
	gcc -g -c tests/$(1)_test.c -o $(1)_test.o

$(1)_test: $(1)_test.o $(1).a
	gcc -g -o $(1)_test $(1)_test.o $(1).a

test_$(1): $(1)_test
	./$(1)_test
else
test_$(1):
	@echo "Skipping test_$(1): tests/$(1)_test.c not found"
endif

endef

$(foreach target,$(TARGETS),$(eval $(call TARGET_RULES,$(target))))

ifneq (,$(wildcard src/PoolAllocator.c))
PoolAllocator.o: src/PoolAllocator.c src/PoolAllocator.h
	gcc -g -c src/PoolAllocator.c -o PoolAllocator.o
else
PoolAllocator.o:
	@echo "Skipping PoolAllocator.o: src/PoolAllocator.c not found"
endif

.PHONY: tests clean valgrind format check_style
