CC = gcc
LC = lcov

CFLAGS = -c -Wall -Werror -Wextra  -std=c11
AFLAGS = ar rc
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LCOVFLAGS = -c -d . -o

SOURCES = $(wildcard *.c)
LIBSOURCES = $(wildcard s21*.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
LIBOBJECTS = $(patsubst %.c, %.o, $(LIBSOURCES))
EXECUTABLE = test
PROJECT_NAME = s21_decimal

ifeq ($(shell uname -s),Linux)
OPEN_CMD = xdg-open
OFLAGS =  -lcheck -lsubunit  -lrt -lpthread -lgcov -o
endif
ifeq ($(shell uname -s),Darwin)
OPEN_CMD = open
OFLAGS = -lcheck -lpthread -lgcov -o
endif

all:  s21_decimal.a $(SOURCES) check test

.c.o:
	$(CC) $(CFLAGS) $< $(GCOVFLAGS) -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(OFLAGS) $@ -lm
	./$(EXECUTABLE)

s21_decimal.a:
	$(CC) $(CFLAGS) $(LIBSOURCES) -lm
	$(AFLAGS) s21_decimal.a $(LIBOBJECTS)
	rm -rf *.o

gcov_report:
	$(LC) $(LCOVFLAGS) report.info
	genhtml report.info
	$(OPEN_CMD) ./index.html

check:
	# leaks -atExit -- ./$(EXECUTABLE) | grep LEAK:
ifeq ("","$(wilcard ./.clang-format)")
	-cp -f ../materials/linters/.clang-format ./.clang-format
endif
	-clang-format -style=google -i $(SOURCES)

clean:
	-rm -rf *.o
	-rm -rf *.gc*
	-rm -rf *.a
	-rm -rf *.png *.info *.html *.css *.info
	-rm -rf src usr
	-rm -rf test
	
rebuild: clean all
