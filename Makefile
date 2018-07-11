TARGET = PowerAna

CXX = g++
CXXFLAGS = -std=c++11 -O0 -g
LDFLAGS = -lm -lrt -lpthread 
INC = -I include/

OBJ_DIR = obj/
SRC_DIR = src/
SRC_FILES := $(wildcard $(SRC_DIR)*.cc)
OBJ_FILES := $(patsubst $(SRC_DIR)%.cc,$(OBJ_DIR)%.o,$(SRC_FILES))

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(INC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.cc
	$(CXX) $(CXXFLAGS) $(INC) $(LDFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_DIR)*.o $(TARGET)
