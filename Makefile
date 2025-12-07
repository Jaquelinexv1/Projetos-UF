CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

TARGET = sistema_treino
SRCS = main.cpp Sistema.cpp Exercicio.cpp Cardio.cpp Forca.cpp Ficha.cpp Historico.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

