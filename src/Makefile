.PHONY: all clean test s21_matrix_oop.a gcov_report build rebuild leaks check checkcpp

CC=gcc
CFLAGS= -std=c++17 -Wall -Wextra -Werror 


OS = $(shell uname)
ifeq ($(OS), Linux)
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs gtest`
else
	LIBFLAGS=-lstdc++ -lm -lgtest
endif

CFILES= test.cc s21_matrix_oop.cc
OBJECTS=$(CFILES:.cpp=.o)
TARGET = tests
LIB_NAME = s21_matrix_oop.a
LIB_FILES = s21_matrix_oop.o

default: test gcov_report

build: all

rebuild: clean all 

all: $(TARGET)

$(LIB_NAME): s21_matrix_oop.o s21_matrix_oop.h
	@ar -rcs $(LIB_NAME) $?
	@ranlib $@
	@cp $@ lib$@

test: rebuild
	./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CC)  $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LIBFLAGS)

%.o: %.cpp
	$(CC) -c $(CFLAGS)  $<

gcov_report: 
	$(CC) --coverage $(CFLAGS) $(CFILES) -o $(TARGET) $(LIBFLAGS) 
	./$(TARGET)
	lcov -t  "$(TARGET)" --ignore-errors mismatch  -o $(TARGET).info -c -d ./ --no-external
	genhtml -o report $(TARGET).info
	open report/index.html

leaks: $(TARGET)
	 leaks  --atExit -- ./$(TARGET) -exclude


checkcpp:
	cppcheck --enable=all  --language=c++ --suppress=missingIncludeSystem --check-config *.cc *.h

check:	
	cp ../materials/linters/.clang-format .  
	clang-format -i *.cc *.h
	clang-format -n *.cc *.h
	rm .clang-format

clean:
	rm -rf $(TARGET)  *.a *.o *.out  *.gc* *.info *report 