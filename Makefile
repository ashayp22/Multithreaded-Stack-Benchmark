EXENAME = main
OBJS = main.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm
BENCHFLAGS = -isystem benchmark/include \
  -Lbenchmark/build/src -lbenchmark -lpthread

# Custom Clang version enforcement logic:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) $(BENCHFLAGS) -o $(EXENAME)

main.o : clean main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

test: output_msg catchmain.o tests.o
	$(LD) catchmain.o tests.o $(LDFLAGS) -o test

catchmain.o : catch/catchmain.cpp catch/catch.hpp
	$(CXX) $(CXXFLAGS) catch/catchmain.cpp

tests.o : tests/tests.cpp catch/catch.hpp
	$(CXX) $(CXXFLAGS) tests/tests.cpp

clean :
	-rm -f *.o $(EXENAME) test
