cflags  := -std=gnu++17 -c -Wall
ldflags := -L./lib/clever/lib
libs    := -lsfml-graphics -lsfml-system -lsfml-window -pthread -lclever-layout -lclever-gradient





# main
build: main

run: build
	main

runfps: main
	LIBGL_SHOW_FPS=1 main 2>&1 | \
	tee /dev/stderr | sed -u -n -e '/^libGL: FPS = /{s/.* \([^ ]*\)= /\1/;p}' | \
	osd_cat --lines=1 --color=yellow --outline=1 --pos=top --align=left


re: clean build

rerun: clean run


source_dirs     := src src/utils src/field src/entities
header_dirs     := src lib
search_wildcard := $(wildcard $(addsuffix /*.cpp,$(source_dirs)))
object_files    := $(patsubst %.cpp,%.o,$(search_wildcard))
object_files    := $(notdir $(object_files))
object_files    := $(addprefix target/,$(object_files))
VPATH           := $(source_dirs)

main: ./target $(object_files)
	g++ $(ldflags) -o $@ $(object_files) $(libs)

./target:
	if ! [ -d ./target ]; then mkdir target; fi

target/%.o: %.cpp
	g++ $(cflags) -o $@ -MD $(addprefix -I,$(header_dirs)) $<

include $(wildcard target/*.d)



# clean
clean:
	-rm target/*.o main





# end
