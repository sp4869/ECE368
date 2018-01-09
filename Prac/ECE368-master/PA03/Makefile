GCC = gcc
CFLAG = -g -Wall -Wshadow -Werror -Wbad-function-cast -O3
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose 
INPUTDIR = input/
OUTPUTDIR = output/

default: build

build: environment
	$(GCC) $(CFLAG) packing.c -o proj3

test: build
	./proj3 $(INPUTDIR)r6_flr.txt $(OUTPUTDIR)output_$@.txt
#	$(VALGRIND) --log-file=$(OUTPUTDIR)$@_valgrind.log ./proj3 $(INPUTDIR)r1_flr.txt $(OUTPUTDIR)output_$@.txt
#	tail -n 1 $(OUTPUTDIR)$@_valgrind.log


environment:
	mkdir -p output
