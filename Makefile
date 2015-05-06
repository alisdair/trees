CFLAGS+=-g -Wall -Werror -Isrc -std=c99 -O2

SRCS=$(wildcard src/**/*.c src/*.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))

TEST_SRCS=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRCS))

TARGET=build/libtrees.a

all: $(TARGET) tests

$(TARGET): CFLAGS += -fpic
$(TARGET): build $(OBJS)
	ar rcs $@ $(OBJS)
	ranlib $@

build:
	@mkdir -p build
	@mkdir -p bin

$(TESTS): $(TARGET)

tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

clean:
	rm -rf build $(OBJS) $(TESTS)
	rm -f tests/tests.log

.PHONY: all tests clean valgrind
