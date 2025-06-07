CFLAGS = -Wall -Wextra -std=c99 -O2

SRCS = $(wildcard *.c)
TEST_SRCS = $(wildcard *_test.c)
MAIN_SRCS = $(filter-out $(TEST_SRCS), $(SRCS))

TARGET = main

all: $(TARGET)

$(TARGET): $(MAIN_SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

check-format:
	@find . -name '*.c' -o -name '*.h' | xargs clang-format --dry-run --Werror

format:
	@find . -name '*.c' -o -name '*.h' | xargs clang-format -i

test:
	@for test in $(TEST_SRCS); do \
		TEST_NAME=$$(basename $$test .c); \
		$(CC) $(CFLAGS) -o $$TEST_NAME $$test; \
		./$$TEST_NAME; \
		rm -f $$TEST_NAME; \
	done

.PHONY: all clean check-format format test