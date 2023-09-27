CXX := g++
CXXFLAGS := -Wall -Wextra
LDFLAGS := -lcurl

# List of source files and corresponding executable names
SRCS := phone-numbers-generator.cpp name-list-generator.cpp name-associator.cpp binary-search.cpp
EXECS := $(SRCS:.cpp=)

all: $(EXECS)

# Rule to compile each source file into an executable
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(EXECS)
