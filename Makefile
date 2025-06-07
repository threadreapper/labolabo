# Общие настройки
STYLE = Google  # Единый стиль форматирования для всех веток

# Автоматическое определение целей
SRC_FILES := $(wildcard *.c)
TARGETS := $(basename $(SRC_FILES))
TEST_TARGETS := $(addprefix test_, $(TARGETS))

# Очистка
clean:
	rm -rf *.o *.a *_test *.d

# Проверка стиля кода
check_style:
	clang-format -style=$(STYLE) -i `find . -regex ".*\.[ch]"` --dry-run --Werror

# Форматирование кода
format:
	clang-format -style=$(STYLE) -i `find . -regex ".*\.[ch]"`

# Запуск тестов
tests: $(TEST_TARGETS)

.PHONY: tests clean check_style format

# Автоматическое создание зависимостей
DEP_FILES := $(patsubst %.c,%.d,$(SRC_FILES))
-include $(DEP_FILES)

# Общие правила для всех целей
define TARGET_RULES

$(1).o: $(1).c
	gcc -g -c $(1).c -o $(1).o -MMD -MP

$(1).a: $(1).o
	ar rc $(1).a $(1).o

$(1)_test.o: $(1)_test.c
	gcc -g -c $(1)_test.c -o $(1)_test.o -MMD -MP

$(1)_test: $(1)_test.o $(1).a
	gcc -g -static -o $(1)_test $(1)_test.o $(1).a -lm

test_$(1): $(1)_test
	./$(1)_test

endef

# Генерация правил для каждой цели
$(foreach target,$(TARGETS),$(eval $(call TARGET_RULES,$(target))))
