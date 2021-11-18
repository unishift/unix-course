project('esub', 'c', version: '1.0.0')

executable(
	'esub', 'esub.c',
)

test_strings = [
	['regexp', 'substituion', 'string'],
	['.*', 'abc', 'verylongstring'],
	['a', 'hello', 'aaaaaaaaaabaaaaaaaaaaabc'],
	['abc', 'testword', 'aksdfajkhsdgkajshdlkasbsabcasdfccba'],
	[
		'(15)(.*)(20)',
		'\\3\\2\\1',
		'15 16 17 18 19 20 21'
	],
	[
		'(a*(b*))',
		'\\2-\\1=',
		'aaabbbccc'
	],
]

test_script = find_program('test.sh', required: false)
foreach args : test_strings
	test(' '.join(args), test_script, args: args)
endforeach
