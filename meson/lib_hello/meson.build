project('hello', 'c')
libsrc = ['foo.c']
libfoo = library('foolib', libsrc)

src = ['main.c']
executable('demo', sources : src, link_with : libfoo )
