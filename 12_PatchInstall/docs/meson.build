# https://stackoverflow.com/a/52534082
doxygen = find_program('doxygen', required : false)
if doxygen.found()
    message('Doxygen found')
    run_target(
        'docs',
        command : 'build_docs.sh',
        env : {'DOXYGEN': doxygen.full_path()}
    )
    install_man('man/man3/binsearch.c.3')
    else
        warning('Documentation disabled without doxygen')
endif