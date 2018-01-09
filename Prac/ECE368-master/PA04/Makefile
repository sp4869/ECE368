GCC = gcc
CFLAG = -g -Wall -Wshadow -Werror -Wbad-function-cast -O3
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose 
INPUTDIR = proj4_flr/
OUTPUTDIR = output/

default: build

build: environment
	$(GCC) $(CFLAG) reroot.c -o proj4

test: build
	./proj4 $(INPUTDIR)r6.po $(OUTPUTDIR)output_$@.txt
#	$(VALGRIND) --log-file=$(OUTPUTDIR)$@_valgrind.log ./proj4 $(INPUTDIR)r0.po $(OUTPUTDIR)output_$@.txt
#	tail -n 1 $(OUTPUTDIR)$@_valgrind.log


environment:
	mkdir -p output
