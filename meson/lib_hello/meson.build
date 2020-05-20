project('hello', 'c')
libsrc = ['foo.c']
libfoo = library('foolib', libsrc)

src = ['main.c']
preobj = ['bar.o']
executable('demo', sources : src, link_with : libfoo, objects : preobj )
