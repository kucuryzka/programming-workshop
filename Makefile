clear:
	rm -rf *.o *.a *_test


check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror


fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`


linear_allocator.o: linear_allocator.h linear_allocator.c
	gcc -g -c linear_allocator.c -o linear_allocator.o


dynamic_array.o: dynamic_array.h dynamic_array.c linear_allocator.h
	gcc -g -c dynamic_array.c -o dynamic_array.o


dynamic_array.a: dynamic_array.o linear_allocator.o
	ar rc dynamic_array.a dynamic_array.o linear_allocator.o


array_test.o: array_test.c dynamic_array.h linear_allocator.h
	gcc -g -c array_test.c -o array_test.o


array_test: array_test.o dynamic_array.a
	gcc -g -static -o array_test array_test.o dynamic_array.a -lm


quadratic_equation.o: quadratic_equation.h quadratic_equation.c
	gcc -g -c quadratic_equation.c -o quadratic_equation.o


quadratic_equation.a: quadratic_equation.o
	ar rc quadratic_equation.a quadratic_equation.o


quadratic_test.o: quadratic_test.c
	gcc -g -c quadratic_test.c -o quadratic_test.o


quadratic_test: quadratic_test.o quadratic_equation.a
	gcc -g -static -o quadratic_test quadratic_test.o quadratic_equation.a -lm


try: array_test quadratic_test
	./array_test && ./quadratic_test
