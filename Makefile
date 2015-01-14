.PHONY: all clean test run

BUILD_DIR := bin

all:
	mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR} && ([ -e Makefile ] || cmake ..)  && make --no-print-directory

run:
	./bin/dominion

test:
	make all && ./bin/dominion < ./test/test_input.test

clean:
	${RM} -rf ${BUILD_DIR}
