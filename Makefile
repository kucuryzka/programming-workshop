clear:
	rm -rf *.o *.a *_test


check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror


fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`


allocator.o: pool_allocator.h pool_allocator.c
	gcc -g -c pool_allocator.c -o allocator.o


allocator.a: allocator.o
	ar rc allocator.a allocator.o


test.o: main.c
	gcc -g -c main.c -o test.o


test: test.o allocator.a
	gcc -g -static -o alloc_test test.o allocator.a -lm


try: test
	./alloc_test
