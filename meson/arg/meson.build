project('hello', 'c')
add_global_arguments('-DVER=1', language : 'c')
add_project_arguments('-DWORLD', language : 'c')
src = ['main.c', 'foo.c']
executable('demo', sources : src, c_args: '-DHELLO -Wall -Wall' )



