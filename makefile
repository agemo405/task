CXX = clang++
CXXFLAGS = -std=c++20 -Wall
LDFLAGS = -lncurses

SRCS = task_main.cpp task_def.cpp
TARGET = task

all : $(TARGET)

$(TARGET) : $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)


clean :
	rm -f $(TARGET)
	rm -f *.data.bin

push :
	git add .
	git commit -m "$(m)"
	git push
