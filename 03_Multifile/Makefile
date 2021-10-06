GENERATES = prog prog-a prog-so *.a *.so README output*
TRASH = *.o *~ o.*
CFLAGS = -Wall -fPIC
ONE_WORD = Hello!
THREE_WORDS = Hello, world !

all: README prog prog-a prog-so

prog: const.o fun.o prog.o

README: prog
	./$< 2> $@

output-zero: prog
	./$< > $@ 2> $@

output-zero-%: prog-%
	LD_LIBRARY_PATH=`pwd` ./$< > $@ 2> $@

output-one: prog
	./$< $(ONE_WORD) > $@ 2> $@

output-one-%: prog-%
	LD_LIBRARY_PATH=`pwd` ./$< $(ONE_WORD) > $@ 2> $@

output-three: prog
	./$< $(THREE_WORDS) > $@ 2> $@

output-three-%: prog-%
	LD_LIBRARY_PATH=`pwd` ./$< $(THREE_WORDS) > $@ 2> $@

test-zero: output-zero output-zero-a output-zero-so
	cmp $(word 1, $^) $(word 2, $^) || true
	cmp $(word 1, $^) $(word 3, $^) || true
	cmp $(word 2, $^) $(word 3, $^) || true

test-one: output-one output-one-a output-one-so
	cmp $(word 1, $^) $(word 2, $^) || true
	cmp $(word 1, $^) $(word 3, $^) || true
	cmp $(word 2, $^) $(word 3, $^) || true

test-three: output-three output-three-a output-three-so
	cmp $(word 1, $^) $(word 2, $^) || true
	cmp $(word 1, $^) $(word 3, $^) || true
	cmp $(word 2, $^) $(word 3, $^) || true

test: test-zero test-one test-three

fun.o: outlib.h

liboutput_static.a: const.o fun.o
	ar -rcs $@ $^

prog-a: liboutput_static.a prog.o
	$(CC) $(CFLAGS) -L. prog.o -loutput_static -o $@

liboutput.so: const.o fun.o
	$(CC) $(CFLAGS) -shared $^ -o liboutput.so

prog-so: liboutput.so prog.o
	$(CC) $(CFLAGS) -L. prog.o -loutput -o $@

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)
  
