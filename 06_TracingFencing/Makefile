SUCCESS=0
EINVARG=1
EINFILE=2
EOUTFILE=3
EREAD=4
EWRITE=5

TEST_GENERATED=reference.txt input.txt output.txt PROTECT.txt
GENERATED=move protect.so ${TEST_GENERATED}
TESTS=test_base test_input test_output test_ld_reload

.PHONY: all clean ${TESTS} 

move: move.c
	${CC} $< -o $@

protect.so: protect_so.c
	${CC} -shared -fPIC -ldl $< -o $@

test_base: move
	@echo $@ > reference.txt
	@cp reference.txt input.txt	

	@(./move input.txt output.txt > /dev/null 2> /dev/null || \
	   test $$? -eq ${SUCCESS} \
	&& cmp reference.txt output.txt \
	&& test ! -f input.txt \
	&& echo $@ passed) || echo $@ not passed

	@rm -f ${TEST_GENERATED}

test_input: move
	@echo $@ > reference.txt
	@cp reference.txt input.txt	

	@strace -e trace=openat -e inject=openat:retval=-1:when=3 ./move input.txt output.txt > /dev/null 2> /dev/null || \
	(  test $$? -eq ${EINFILE} \
	&& cmp reference.txt input.txt \
	&& test ! -f output.txt \
	&& echo $@ passed) || echo $@ not passed

	@rm -f ${TEST_GENERATED}

test_output: move
	@echo $@ > reference.txt
	@cp reference.txt input.txt	

	@strace -e trace=openat -e inject=openat:retval=-1:when=4 ./move input.txt output.txt > /dev/null 2> /dev/null || \
	(  test $$? -eq ${EOUTFILE} \
	&& cmp reference.txt input.txt \
	&& test ! -f output.txt \
	&& echo $@ passed) || echo $@ not passed

	@rm -f ${TEST_GENERATED}

test_ld_reload: move protect.so
	@echo $@ > reference.txt
	@cp reference.txt PROTECT.txt	

	@(LD_PRELOAD=`pwd`/protect.so ./move PROTECT.txt output.txt > /dev/null 2> /dev/null || \
	   test $$? -eq ${SUCCESS} \
	&& cmp reference.txt PROTECT.txt \
	&& cmp reference.txt output.txt \
	&& echo $@ passed) || echo $@ not passed

	@rm -f ${TEST_GENERATED}

tests: ${TESTS}

all: move tests

clean:
	rm -rf ${GENERATED}