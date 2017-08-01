#author Justin Barish
#since 06292017

CC=g++
CXXFLAGS=-I./include  -std=c++11 -L./include -lrt -lcreateoi -lpthread
CFLAGS=$CXXFLAGS
LIB= -L./include -lcreateoi
EXEC=robot
#OBJS= ./Code/PincherApp.o ./Code/SerialCommPincher003.o
OBJS=./ZRC3/main.o ./ZRC3/driver.o

all: ${OBJS}
	$(CC)   ${OBJS}  -o ${EXEC} $(CXXFLAGS)
clean: 
	rm ZRC3/*.o
fclean: clean
	rm $(EXEC)
re: fclean all

