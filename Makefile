clear:
	rm -rf *.o *.a *_test


check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror


fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`


quadratic_equation.o: quadratic_equation.h quadratic_equation.c
	gcc -g -c quadratic_equation.c -o quadratic_equation.o


quadratic_equation.a: quadratic_equation.o
	ar rc quadratic_equation.a quadratic_equation.o


quadratic_test.o: quadratic_test.c
	gcc -g -c quadratic_test.c -o quadratic_test.o


quadratic_test: quadratic_test.o quadratic_equation.a
	gcc -g -static -o quadratic_test quadratic_test.o quadratic_equation.a -lm


try: quadratic_test
	./quadratic_test
