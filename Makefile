clear:
	rm -rf *.o *.a *_test


check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror


fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

# ---------------quadratic equation-------------------------------
quadratic_equation.o: quadratic_equation.h quadratic_equation.c
	gcc -g -c quadratic_equation.c -o quadratic_equation.o


quadratic_equation.a: quadratic_equation.o
	ar rc quadratic_equation.a quadratic_equation.o


quadratic_test.o: quadratic_test.c
	gcc -g -c quadratic_test.c -o quadratic_test.o


quadratic_test: quadratic_test.o quadratic_equation.a
	gcc -g -static -o quadratic_test quadratic_test.o quadratic_equation.a -lm

# -----------------------------------------------------------------

# ----------------dynamic array------------------------------------
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

#--------------------------------------------------------------------

#------------------------integration---------------------------------

integration.o: integration.h integration.c
	gcc -g -c integration.c -o integration.o


integration.a: integration.o
	ar rc integration.a integration.o


_test.o: main.c
	gcc -g -c main.c -o _test.o


integration_test: _test.o integration.a
	gcc -g -static -o integration_test _test.o integration.a -lm

#----------------------------------------------------------------------

#--------------------------------stack---------------------------------

stack_test: stack_test.o f_stack.a
	gcc -g -static -o stack_test stack_test.o f_stack.a
  

stack_test.o: stack_test.c f_stack.h
	gcc -g -c stack_test.c


f_stack.o: f_stack.c f_stack.h
	gcc -g -c f_stack.c


f_stack.a: f_stack.o
	ar rc f_stack.a f_stack.o

#------------------------------------------------------------------------

#----------------------------linked-list---------------------------------

list_f.o: list_f.h list_f.c
	gcc -g -c list_f.c -o list_f.o


list_f.a: list_f.o
	ar rc list_f.a list_f.o


list_test.o: list_test.c
	gcc -g -c list_test.c -o list_test.o


list_test: list_test.o list_f.a
	gcc -g -static -o list_test list_test.o list_f.a -lm

#-------------------------------------------------------------------------

#-----------------------------pool_allocator------------------------------

allocator.o: pool_allocator.h pool_allocator.c
	gcc -g -c pool_allocator.c -o allocator.o


allocator.a: allocator.o
	ar rc allocator.a allocator.o


test.o: main.c
	gcc -g -c main.c -o test.o


test: test.o allocator.a
	gcc -g -static -o alloc_test test.o allocator.a -lm
#-------------------------------------------------------------------------

# -----------------------------garbage_collector--------------------------
gc.o: garbage_collector.h garbage_collector.c pool_allocator.h
	gcc -g -c garbage_collector.c -o gc.o

gc.a: gc.o allocator.o
	ar rc gc.a gc.o allocator.o

gc_test.o: garbage_collector_test.c garbage_collector.h pool_allocator.h
	gcc -g -c garbage_collector_test.c -o gc_test.o

gc_test: gc_test.o gc.a
	gcc -g -static -o gc_test gc_test.o gc.a -lm
#-------------------------------------------------------------------------

try: gc_test
	./gc_test

check_memory: gc_test
	valgrind --leak-check=full ./gc_test
