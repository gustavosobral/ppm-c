myapp := ppm-test

IDIR = ../include
LDIR = lib
SRCDIR = ../src

# CC for C, CXX for C++
# CFLAGS for C, CXXFLAGS for C++, CPPFLAGS for both
CXX :=	g++
CXXFLAGS :=	-Wall -L/usr/lib -lgtest -lgtest_main -lpthread
INCS := -I$(IDIR)/ -I. -I/usr/include/gtest/
LIBS :=

# wildcard = single file name specifies many files 
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
TEST_SOURCES = $(wildcard *.cpp)
OBJ_ :=  $(SOURCES:$(SRCDIR)/%.cpp=%.o)
OBJ = $(subst main.o,,$(OBJ_))
OBJ_TEST :=  $(TEST_SOURCES:%.cpp=%.o)
DEPS = $(IDIR)/*.hpp

all: $(myapp)

#$^ = the filenames of all the prerequisites, separated by spaces, discard duplicates
# $@ = the target filename  
$(myapp): $(OBJ) $(OBJ_TEST)
	@echo "linking files"
	$(CXX) $(OBJ) $(OBJ_TEST) $(CXXFLAGS) $(INCS) -o $@
	rm -rf *.o 

# $< = the first prerequisite filename
%.o : $(SRCDIR)/%.cpp $(DEPS)
	@echo "compiling SOURCES"
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@

%-test.o : %-test.cpp 
	@echo "compiling TESTS"
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@

run:
	./$(myapp)

install-dep: 
	sudo apt-get install libgtest-dev
	sudo apt-get install cmake 
	cd /usr/src/gtest && sudo cmake CMakeLists.txt && sudo make && sudo cp *.a /usr/lib

.PHONY: clean

clean:
	rm -rf *.o ~* ppm-test ppm-test.xml

my_echo:
	@echo $(OBJ_TEST) 