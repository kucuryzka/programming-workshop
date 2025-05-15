clear:
	rm -rf *.o *.a test1


check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror


fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`


linear_allocator.o: linear_allocator.h linear_allocator.c
	gcc -g -c linear_allocator.c -o linear_allocator.o


hash_table.o: hash_table.h hash_table.c linear_allocator.h
	gcc -g -c hash_table.c -o hash_table.o


hash_table.a: hash_table.o linear_allocator.o
	ar rc hash_table.a hash_table.o linear_allocator.o


hash_table_test.o: hash_table_test.c hash_table.h linear_allocator.h
	gcc -g -c hash_table_test.c -o hash_table_test.o


hash_table_test: hash_table_test.o hash_table.a
	gcc -g -static -o hash_table_test hash_table_test.o hash_table.a -lm


try: hash_table_test
	./*_test