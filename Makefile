fmt:
	find . -regex '.*\.[ch]' -exec clang-format -style=LLVM -i {} +
check_fmt:
	find . -regex '.*\.[ch]' -exec clang-format -style=LLVM --dry-run --Werror {} +

run:
	find . -name "Makefile" -execdir make -f {} \;
	if find . -type f -name "*_test" -exec sh -c '{} && echo "тест пройден успешно"' \; ; then \
    	echo "Все тесты выполнены."; \
  	else \
    	echo "Тесты не найдены."; \
  	fi

clean:
	find . -type f \( -name "*.o" -o -name "*.a" -o -name "*_test" \) -exec rm -f {} +
