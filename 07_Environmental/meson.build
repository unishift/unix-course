project('rhasher', 'c', version: '1.0.0')

# Dependencies
c_args = []
deps = []

cc = meson.get_compiler('c')
librhash = cc.find_library(
	'librhash',
	dirs: '/usr/local/lib'
)
deps += librhash

if not get_option('disable-readline')
	libreadline = dependency('readline', required: false)
	if libreadline.found()
		c_args += '-DUSE_READLINE'
		deps += libreadline
	endif
endif

# Executable
add_project_arguments('-Wno-pointer-sign', language: 'c')
executable(
	'rhasher', 'rhasher.c',
	dependencies: deps,
	c_args: c_args
)

# Tests
test_script = find_program('test.sh', required: false)

algos_to_test = ['SHA1', 'MD5', 'TTH']
foreach algo: algos_to_test
	test(algo + ' test', test_script, env: 'ALGO=' + algo, is_parallel: false)
endforeach