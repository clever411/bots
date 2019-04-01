EXECUTABLE = main
CFLAGS = -std=gnu++17 -c -O5 -DDEBUG -I./library
LDFLAGS =
LIBS = -lsfml-graphics -lsfml-system -lsfml-window -pthread





# main
all: $(EXECUTABLE)

run: $(EXECUTABLE)
	$(EXECUTABLE) 


re: clean $(EXECUTABLE)

rerun: clean $(EXECUTABLE)
	$(EXECUTABLE)


clean:
	-rm *.o $(EXECUTABLE)





$(EXECUTABLE): \
	main.o define.o init.o \
	BotField.o Bot.o \
	CellPrinter.o Gradient.o Stat.o
	g++ $(LDFLAGS) -o $(EXECUTABLE) \
	main.o define.o init.o \
	BotField.o Bot.o \
	CellPrinter.o Gradient.o Stat.o $(LIBS)

main.o: main.cpp declare.hpp init.hpp Stat.hpp
	g++ $(CFLAGS) -o main.o main.cpp



define.o: define.cpp declare.hpp
	g++ $(CFLAGS) -o define.o define.cpp

declare.hpp: BotField.hpp CellPrinter.hpp



init.o: init.cpp init.hpp declare.hpp
	g++ $(CFLAGS) -o init.o init.cpp



BotField.o: BotField.cpp BotField.hpp
	g++ $(CFLAGS) -o BotField.o BotField.cpp

BotField.hpp: Cell.hpp Plant.hpp Bot.hpp Body.hpp



Bot.o: Bot.cpp Bot.hpp BotField.hpp
	g++ $(CFLAGS) -o Bot.o Bot.cpp





CellPrinter.o: CellPrinter.cpp CellPrinter.hpp
	g++ $(CFLAGS) -o CellPrinter.o CellPrinter.cpp

CellPrinter.hpp: BotField.hpp Gradient.hpp



Gradient.o: Gradient.cpp Gradient.hpp
	g++ $(CFLAGS) -o Gradient.o Gradient.cpp



Stat.o: Stat.cpp Stat.hpp
	g++ $(CFLAGS) -o Stat.o Stat.cpp





# end
