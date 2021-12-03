project('binsearch', 'c', version: '1.0.0')

i18n = import('i18n')
intl = dependency('intl')

buf = executable(meson.project_name(), meson.project_name() + '.c', dependencies: intl)

subdir('po')
