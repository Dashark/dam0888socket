#CXX=clang++
CXXFLAGS=-g -std=c++11 -Wall -pedantic
PROG    = dam0888Socket
SRC			= $(wildcard *.cpp)
OBJS		= $(SRC:%.cpp=%.o)

PKGS    = glib-2.0 libmodbus
CFLAGS += $(shell pkg-config --cflags $(PKGS))
LDLIBS += $(shell pkg-config --libs $(PKGS))
LDLIBS += -lrdkafka++ -lz -lpthread -lm -ldl


all: $(OBJS)
	$(CXX) $(CFLAGS) -o $(PROG) $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CFLAGS) -c $<

clean:
	rm -f *.o
	rm $(PROG)