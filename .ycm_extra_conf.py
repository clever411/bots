def Settings( **kwargs ):
  return { 'flags': [
    #  '-Wall',
    #  '-Wextra',
    #  '-Werror',
    '-std=c++17',
    '-x', 'c++',    
	'-isystem', '/usr/include',
	'-isystem', '/usr/local/include',
    '-isystem', '/usr/include/c++/9',
    '-isystem', '/usr/include/c++/9/backward',
	'-isystem', '/usr/include/x86_64-linux-gnu/c++/9',
	'-I', 'src',
	'-I', 'lib',
  ] }
