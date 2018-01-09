GCC = gcc
CFLAG = -g -Wall -Wshadow -Werror -O3
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose 
INPUTDIR = testcases/
OUTPUTDIR = output/

default: build

build: environment
	$(GCC) $(CFLAG) -c sorting.main.c 
	$(GCC) $(CFLAG) -c sorting.c
	$(GCC) $(CFLAG) sorting.main.o sorting.o sorting.h -o proj2

test: build
#	./proj2 samples/10.txt
#	./proj2 $(INPUTDIR)seq1000.txt output/output.txt

	./proj2 $(INPUTDIR)1000.txt output/output.txt
#	$(VALGRIND) ./proj2 $(INPUTDIR)10000.txt output/output.txt
#	$(VALGRIND) ./proj2 samples/10.txt output/output.txt
#	./proj1 s $(INPUTDIR)10.txt $(INPUTDIR)seq10.txt $(OUTPUTDIR)output.txt
#	$(VALGRIND) --log-file=$(OUTPUTDIR)$@_valgrind.log ./proj1 s $(INPUTDIR)10.txt $(OUTPUTDIR)$@_seq10.txt $(OUTPUTDIR)$@_s10.txt
#	#tail -n 1 $(OUTPUTDIR)$@_valgrind.log
#

test2: build
	./proj2 $(INPUTDIR)10000.txt output/output.txt

test3: build
	./proj2 $(INPUTDIR)100000.txt output/output.txt

test4: build
	./proj2 $(INPUTDIR)1000000.txt output/output.txt

environment:
	mkdir -p output
