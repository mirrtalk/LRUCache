# 
# date: 2014/12/10
#

CFLAGS=-I./ -std=c++0x -fPIC -fno-builtin-memcmp -O

TARGET=liblrucache.a
TARGET_TEST=cache_test

OBJ_DIR=./obj
SRC_DIR=./src
OBJ=$(addprefix $(OBJ_DIR)/, \
    cache.o \
    coding.o \
    hash.o \
    port_posix.o \
    ldb_cache.o \
    )

all: $(OBJ)
	ar -rs $(TARGET) $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@-if [ ! -d $(OBJ_DIR) ];then mkdir $(OBJ_DIR); fi
	g++ $(CFLAGS) -c $< -o $@

test:
	g++ -Wall -L./ $(SRC_DIR)/cache_test.c -pthread -lstdc++ -llrucache -g2 -o $(TARGET_TEST)

clean:
	rm -rf $(TARGET) $(TARGET_TEST) $(OBJ_DIR) *.a nohup.out

mc:
	@rm -f nohup.out
	nohup valgrind --tool=memcheck  --leak-check=full --verbose ./$(TARGET_TEST)&
	
.PHONY: all test clean mc
