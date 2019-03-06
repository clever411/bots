EXECUTABLE = main
CFLAGS = -std=gnu++17 -c -Wall -g3 -DDEBUG -I./library
LDFLAGS =
LIBS = -lsfml-graphics -lsfml-system -lsfml-window





# main
all: $(EXECUTABLE)

run: $(EXECUTABLE)
	$(EXECUTABLE) 


re: clean $(EXECUTABLE)

rerun: clean $(EXECUTABLE)
	$(EXECUTABLE)



$(EXECUTABLE): main.o define.o init.o life.o CellPrinter.o
	g++ $(LDFLAGS) -o $(EXECUTABLE) \
	main.o define.o init.o life.o CellPrinter.o $(LIBS)

main.o: main.cpp
	g++ $(CFLAGS) -o main.o main.cpp

define.o: define.cpp
	g++ $(CFLAGS) -o define.o define.cpp

init.o: init.cpp
	g++ $(CFLAGS) -o init.o init.cpp

life.o: life.cpp
	g++ $(CFLAGS) -o life.o life.cpp

CellPrinter.o: CellPrinter.cpp
	g++ $(CFLAGS) -o CellPrinter.o CellPrinter.cpp








# clean
clean:
	-rm *.o $(EXECUTABLE)





# end
