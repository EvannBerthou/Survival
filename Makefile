PKGS=sdl2 SDL2_ttf SDL2_image
CXXFLAGS=-Wall -Wextra -g
LIBS=$(shell pkg-config --libs $(PKGS)) -lm

SRCS=$(wildcard src/*.cpp)
OBJS=$(addsuffix .o, $(basename $(SRCS)))

.PHONY: all clean

all: survival
survival: $(OBJS)
	g++ $(CXXFLAGS) -o survival $(OBJS) -Iincludes $(LIBS)

%.o: %.cpp
	g++ -o $@ -Iincludes $(CXXFLAGS) -c $<

clean:
	rm -f $(MAIN_OBJS) $(LIBS_OBJS)
