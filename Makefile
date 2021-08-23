#CXX=clang++
CXXFLAGS=-g -std=c++11 -Wall -pedantic
PROG    = H3CSocket
SRC			= $(wildcard *.cpp)
OBJS		= $(SRC:%.cpp=%.o)

PKGS    = glib-2.0
CFLAGS += $(shell pkg-config --cflags $(PKGS))
LDLIBS += $(shell pkg-config --libs $(PKGS))
LDLIBS += -lz -lpthread -lm -ldl -lidm_netsdk


all: $(OBJS)
	$(CXX) $(CFLAGS) -o $(PROG) $^ -Llib/ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CFLAGS) -c $<

clean:
	rm -f *.o
	rm $(PROG)