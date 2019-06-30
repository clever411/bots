EXECUTABLE = main
CFLAGS = -std=gnu++17 -c -O5 -DDEBUG -I./library
LDFLAGS = -L./library/clever/lib
LIBS = -lsfml-graphics -lsfml-system -lsfml-window -pthread -lclever-layout





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
	BotField.o Plant.o Bot.o BotGen.o Body.o Mineral.o \
	CellPrinter.o Gradient.o Stat.o
	g++ $(LDFLAGS) -o $(EXECUTABLE) \
	main.o define.o init.o \
	BotField.o Plant.o Bot.o BotGen.o Body.o Mineral.o \
	CellPrinter.o Gradient.o Stat.o $(LIBS)

main.o: main.cpp declare.hpp init.hpp \
	BotField.hpp Cell.hpp Plant.hpp Bot.hpp Body.hpp Mineral.hpp \
	CellPrinter.hpp Stat.hpp
	g++ $(CFLAGS) -o main.o main.cpp



define.o: define.cpp declare.hpp BotField.hpp Cell.hpp Plant.hpp Bot.hpp Body.hpp Mineral.hpp CellPrinter.hpp
	g++ $(CFLAGS) -o define.o define.cpp



init.o: init.cpp init.hpp declare.hpp Bot.hpp BotField.hpp CellPrinter.hpp
	g++ $(CFLAGS) -o init.o init.cpp



BotField.o: BotField.cpp BotField.hpp Body.hpp Bot.hpp Cell.hpp Mapping.hpp Mineral.hpp Plant.hpp 
	g++ $(CFLAGS) -o BotField.o BotField.cpp



Plant.o: Plant.cpp Plant.hpp BotField.hpp Cell.hpp
	g++ $(CFLAGS) -o Plant.o Plant.cpp


Bot.o: Bot.cpp Bot.hpp BotField.hpp BotGen.hpp Cell.hpp Plant.hpp Body.hpp Mineral.hpp
	g++ $(CFLAGS) -o Bot.o Bot.cpp

BotGen.o: BotGen.cpp BotGen.hpp
	g++ $(CFLAGS) -o BotGen.o BotGen.cpp



Body.o: Body.cpp Body.hpp Cell.hpp Mineral.hpp
	g++ $(CFLAGS) -o Body.o Body.cpp


Mineral.o: Mineral.cpp Mineral.hpp Cell.hpp Plant.hpp
	g++ $(CFLAGS) -o Mineral.o Mineral.cpp





CellPrinter.o: CellPrinter.cpp CellPrinter.hpp Cell.hpp Plant.hpp Bot.hpp BotField.hpp Body.hpp Mineral.hpp Gradient.hpp
	g++ $(CFLAGS) -o CellPrinter.o CellPrinter.cpp


Gradient.o: Gradient.cpp Gradient.hpp
	g++ $(CFLAGS) -o Gradient.o Gradient.cpp


Stat.o: Stat.cpp Stat.hpp
	g++ $(CFLAGS) -o Stat.o Stat.cpp





# end
