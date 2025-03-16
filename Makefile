clear:
	rm -rf *.o *.a *_test


check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror


fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`


list_f.o: list_f.h list_f.c
	gcc -g -c list_f.c -o list_f.o


list_f.a: list_f.o
	ar rc list_f.a list_f.o


list_test.o: list_test.c
	gcc -g -c list_test.c -o list_test.o


list_test: list_test.o list_f.a
	gcc -g -static -o list_test list_test.o list_f.a -lm


try: list_test
	./list_test
