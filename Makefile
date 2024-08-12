# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I/opt/homebrew/opt/sfml/include -I/opt/homebrew/Cellar/googletest/1.15.0/include -pthread

# Linker flags
LDFLAGS = -L/opt/homebrew/opt/sfml/lib -L/opt/homebrew/lib -L/opt/homebrew/opt/googletest/lib -lsfml-graphics -lsfml-window -lsfml-system -lgtest -lgtest_main

# Source and object files
SRCS = src/main.cpp lib/gui/Window.cpp lib/gui/GuiField.cpp lib/domain/pieces/Piece.cpp lib/domain/utils/Position.cpp lib/domain/Player.cpp lib/domain/Board.cpp lib/domain/Field.cpp lib/domain/pieces/Pawn.cpp lib/domain/Game.cpp lib/domain/utils/Error.cpp lib/domain/utils/Move.cpp lib/domain/pieces/Knight.cpp lib/domain/pieces/Bishop.cpp lib/domain/pieces/Rook.cpp lib/domain/pieces/Queen.cpp lib/domain/pieces/King.cpp lib/gui/EndScreen.cpp lib/gui/DecisionButton.cpp lib/gui/DecisionField.cpp lib/Session.cpp
TEST_SRCS = tests/firstTest.cpp
OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Executable name
TARGET = chess
TEST_TARGET = test_chess

# Default target
all: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(TEST_OBJS) -o $(TEST_TARGET) $(LDFLAGS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)

# Phony targets
.PHONY: all clean test
