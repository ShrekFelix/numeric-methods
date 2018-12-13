SOURCES=Expr.cpp numerics.cpp extremum.cpp integral.cpp
OBJS=$(patsubst %.cpp, %.o, $(SOURCES))
CPPFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++11

numerics: $(OBJS)
	g++ $(CPPFLAGS) -o numerics $(OBJS)
%.o: %.cpp Expr.h numerics.h
	g++ $(CPPFLAGS) -c $<

clean:
	rm numerics *~ *.o
