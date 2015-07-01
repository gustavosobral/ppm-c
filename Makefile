myapp := ppm

IDIR = include
LDIR = lib
SRCDIR = src

# CC for C, CXX for C++
# CFLAGS for C, CXXFLAGS for C++, CPPFLAGS for both
CXX :=	g++
CXXFLAGS :=	-Wall
INCS := -I$(IDIR)/
LIBS :=

# wildcard = single file name specifies many files 
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(SOURCES:$(SRCDIR)/%.cpp=%.o)
DEPS = $(IDIR)/*.hpp

all: $(myapp)

# $^ = the filenames of all the prerequisites, separated by spaces, discard duplicates
# $@ = the target filename  
$(myapp): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCS) -o $@ $^ 
	rm -rf *.o 

# $< = the first prerequisite filename
%.o : $(SRCDIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf ~* ppm doc/