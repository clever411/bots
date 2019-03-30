EXECUTABLE = main
CFLAGS = -std=gnu++17 -c -O5 -DDEBUG -I./library
LDFLAGS =
LIBS = -lsfml-graphics -lsfml-system -lsfml-window





# main
all: $(EXECUTABLE)

run: $(EXECUTABLE)
	$(EXECUTABLE) 


re: clean $(EXECUTABLE)

rerun: clean $(EXECUTABLE)
	$(EXECUTABLE)


clean:
	-rm *.o $(EXECUTABLE)





$(EXECUTABLE): main.o define.o init.o bot_field.o CellPrinter.o Gradient.o Stat.o
	g++ $(LDFLAGS) -o $(EXECUTABLE) \
	main.o define.o init.o bot_field.o CellPrinter.o Gradient.o Stat.o $(LIBS)

main.o: main.cpp declare.hpp init.hpp Stat.hpp
	g++ $(CFLAGS) -o main.o main.cpp



define.o: define.cpp declare.hpp
	g++ $(CFLAGS) -o define.o define.cpp

declare.hpp: bot_field.hpp CellPrinter.hpp



init.o: init.cpp init.hpp declare.hpp
	g++ $(CFLAGS) -o init.o init.cpp



bot_field.o: bot_field.cpp bot_field.hpp
	g++ $(CFLAGS) -o bot_field.o bot_field.cpp



CellPrinter.o: CellPrinter.cpp CellPrinter.hpp
	g++ $(CFLAGS) -o CellPrinter.o CellPrinter.cpp

CellPrinter.hpp: bot_field.hpp Gradient.hpp



Gradient.o: Gradient.cpp Gradient.hpp
	g++ $(CFLAGS) -o Gradient.o Gradient.cpp



Stat.o: Stat.cpp Stat.hpp
	g++ $(CFLAGS) -o Stat.o Stat.cpp





# end
