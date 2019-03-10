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



$(EXECUTABLE): main.o define.o init.o bot_field.o
	g++ $(LDFLAGS) -o $(EXECUTABLE) \
	main.o define.o init.o bot_field.o $(LIBS)

main.o: main.cpp
	g++ $(CFLAGS) -o main.o main.cpp

define.o: define.cpp
	g++ $(CFLAGS) -o define.o define.cpp

init.o: init.cpp
	g++ $(CFLAGS) -o init.o init.cpp

bot_field.o: bot_field.cpp
	g++ $(CFLAGS) -o bot_field.o bot_field.cpp










# clean
clean:
	-rm *.o $(EXECUTABLE)





# end
