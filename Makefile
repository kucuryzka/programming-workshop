clear:
	rm -rf *.o *.a *_test


check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror


fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`
    

stack_test: stack_test.o f_stack.a
	gcc -g -static -o stack_test stack_test.o f_stack.a
  

stack_test.o: stack_test.c f_stack.h
	gcc -g -c stack_test.c


f_stack.o: f_stack.c f_stack.h
	gcc -g -c f_stack.c


f_stack.a: f_stack.o
	ar rc f_stack.a f_stack.o


try: stack_test
	./stack_test
