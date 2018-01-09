GCC = gcc
CFLAG = -g -Wall -Wshadow -Werror -Wbad-function-cast -O3
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose 
INPUTDIR = input/
OUTPUTDIR = output/

default: build

build: environment
	$(GCC) $(CFLAG) river.c -o proj5

test: build
#	./proj5 $(INPUTDIR)river.in0
	$(VALGRIND) --log-file=$(OUTPUTDIR)$@_valgrind.log ./proj5 $(INPUTDIR)river.in0
	tail -n 1 $(OUTPUTDIR)$@_valgrind.log


environment:
	mkdir -p output
