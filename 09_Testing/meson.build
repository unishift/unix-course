project('buf', 'c', version: '1.0.0', default_options : 'b_coverage=true')

buf = library('buf', 'buf.c')

tests = [
    'init_free',
    'clear_null',
    'push_index',
    'pop',
    'grow_trunc',
]

foreach test_name : tests
    test_exe = executable(test_name, 'tests' / (test_name + '.c'), link_with: buf)
	test(test_name, test_exe)
endforeach
