clear:
	rm -rf *.o *.a test1


checkfmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror


fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`


functions.o: functions.h functions.c
	gcc -g -c functions.c -o functions.o


functions.a: functions.o
	ar rc functions.a functions.o


test.o: test.c
	gcc -g -c test.c -o test.o


test: test.o functions.a
	gcc -g -static -o test1 test.o functions.a -lm


try: test
	./test1
