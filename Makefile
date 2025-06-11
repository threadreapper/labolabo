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
	which valgrind || (echo "Error: Valgrind is not installed. Please install it and try again." && exit 1)
	for test_target in $(TEST_TARGETS); do \
		test -f ./$(test_target) || (echo "Executable '$(test_target)' not found. Skipping valgrind for this target."; continue); \
		valgrind --leak-check=full ./$$test_target; \
	done

define TARGET_RULES

$(1).o: $(1).c $(1).h
	gcc -g -c $(1).c -o $(1).o

$(1).a: $(1).o
ifeq ($(1),RefCounter)
	ar rc $(1).a $(1).o PoolAllocator.o
else
	ar rc $(1).a $(1).o
endif

$(1)_test.o: $(1)_test.c $(1).h
ifneq (,$(wildcard $(1)_test.c))
	gcc -g -c $(1)_test.c -o $(1)_test.o
else
	@echo "Skipping $(1)_test.o: $(1)_test.c not found"
endif

$(1)_test: $(1)_test.o $(1).a
ifneq (,$(wildcard $(1)_test.c))
	gcc -g -o $(1)_test $(1)_test.o $(1).a
else
	@echo "Skipping $(1)_test: $(1)_test.c not found"
endif

test_$(1): $(1)_test
ifneq (,$(wildcard $(1)_test.c))
	./$(1)_test
else
	@echo "Skipping test_$(1): $(1)_test.c not found"
endif

endef

$(foreach target,$(TARGETS),$(eval $(call TARGET_RULES,$(target))))

PoolAllocator.o: PoolAllocator.c PoolAllocator.h
	gcc -g -c PoolAllocator.c -o PoolAllocator.o

.PHONY: tests clean valgrind format check_style
