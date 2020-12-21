EXEC=tictoe.out
SDIR=src
IDIR=include
ODIR=build
LDIR=lib

CXX=g++
CXXFLAGS=-I$(IDIR)

LIBS=-L$(LDIR) -lsfml-graphics -lsfml-window -lsfml-system -lpthread -lsfml-network

_DEPS = GameEngine.hpp GameStateManager.hpp GameState.hpp MenuState.hpp PlayingState.hpp GameLogic.hpp
_OBJ = main.o GameEngine.o GameStateManager.o MenuState.o PlayingState.o GameLogic.o

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all run clean

all: $(EXEC) run

run:
	$(ODIR)/$(EXEC)

clean:
	rm -f $(ODIR)/*.o

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(EXEC): $(OBJ)
	$(CXX) -o $(ODIR)/$@ $^ $(CXXFLAGS) $(LIBS)
