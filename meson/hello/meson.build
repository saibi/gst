project('hello', 'c')
build_machine.system()
src = ['main.c', 'foo.c']
executable('demo', sources : src, c_args: '-Wall' )

template = 'string: @0@, number: @1@, bool: @2@'

res = template.format('text', 1, true)

