### Constants: g++
INC=-I.
CXX=g++ -std=c++11
CXX_OPT=-Werror -Wextra -Wall -Wfatal-errors -pedantic 

### Constants: gtest
GTEST_ROOT_DIR=ext/googletest/googletest/
GTEST_BUILD_DIR=${GTEST_ROOT_DIR}/build
GTEST_INC_DIR=${GTEST_ROOT_DIR}/include
GTEST_MAIN=${GTEST_BUILD_DIR}/libgtest_main.a
GTEST_INC=-I${GTEST_INC_DIR}
GTEST_LIB=${GTEST_BUILD_DIR}/libgtest.a
GTEST_TARGET=bin/gtest

### Regression test binaries
TEST_OBJ=\
	test/buf_stream.o\
	test/comment_stream.o\
	test/indent_stream.o\
	test/seq_stream.o\
	test/sub_stream.o

### Top-level commands
all: ${GTEST_TARGET}
check: ${GTEST_TARGET}
		${GTEST_TARGET}
submodule:
		git submodule init
		git submodule update
clean:
		rm -rf ${BINS} ${GTEST_BUILD_DIR} ${TEST_OBJ} ${GTEST_TARGET}

### Build rules
test/%.o: test/%.cc test/*.cc include/*.h
	${CXX} ${CXX_OPT} ${INC} ${GTEST_INC} -c $< -o $@
${GTEST_LIB}:
	mkdir -p ${GTEST_BUILD_DIR}
	cd ${GTEST_BUILD_DIR} && cmake .. && make
${GTEST_TARGET}: ${GTEST_LIB} ${GTEST_MAIN} ${LIB} ${TEST_OBJ} 
	${CXX} -o $@ ${TEST_OBJ} ${LIB} ${GTEST_LIB} ${GTEST_MAIN} -lpthread

