INC_DIR:=./src/*.h
SRCS:=$(wildcard ./src/*cc)
OBJS:= $(patsubst %.cc, %.o, $(SRCS))
LIBS:= 

CXX:=g++

CXXFLAGS:= -w -g -std=c++11 -lpthread -ljson $(addprefix -I, $(INC_DIR)) $(LIBS)

EXE:=./bin/game.exe

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
