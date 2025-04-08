clear:
	rm -rf *.o *.a *_test


check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror


fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`


integration.o: integration.h integration.c
	gcc -g -c integration.c -o integration.o


integration.a: integration.o
	ar rc integration.a integration.o


_test.o: main.c
	gcc -g -c main.c -o _test.o


test: _test.o integration.a
	gcc -g -static -o integration_test _test.o integration.a -lm


try: test
	./integration_test
