.PHONY: all test test1 test2 clean

GDB_PARAMS=-q --batch-silent

range: range.c
	$(CC) -O0 -g $^ -o $@

test: test1 test2

test1: test1.txt test1.gt
	diff $^

test2: test2.txt test2.gt
	diff $^

test%.txt: test%.gdb range
	gdb $(GDB_PARAMS) --command=$< ./range
	cat gdb.txt | grep @@@ | cut -c 5- > $@
	rm -f gdb.txt

all: test

clean:
	rm -f range test*.txt
