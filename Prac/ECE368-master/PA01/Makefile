GCC = gcc
CFLAG = -g -Wall -Wshadow -Werror -O3
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose 
INPUTDIR = testcases/
OUTPUTDIR = output/

default: build

build: environment
	$(GCC) $(CFLAG) -c sorting.main.c 
	$(GCC) $(CFLAG) -c sorting.c
	$(GCC) $(CFLAG) sorting.main.o sorting.o sorting.h -o proj1

#test: build
#	./proj1 s $(INPUTDIR)10.txt $(INPUTDIR)seq10.txt $(OUTPUTDIR)output.txt
#	$(VALGRIND) --log-file=$(OUTPUTDIR)$@_valgrind.log ./proj1 s $(INPUTDIR)10.txt $(OUTPUTDIR)$@_seq10.txt $(OUTPUTDIR)$@_s10.txt
#	#tail -n 1 $(OUTPUTDIR)$@_valgrind.log

test1_s: build
	./proj1 s $(INPUTDIR)1000.txt $(INPUTDIR)seq1000.txt $(OUTPUTDIR)s1000.txt > $(OUTPUTDIR)$@_output.txt
	#$(VALGRIND) --log-file=$(OUTPUTDIR)$@_valgrind.log ./proj1 s $(INPUTDIR)1000.txt $(OUTPUTDIR)$@_seq1000.txt $(OUTPUTDIR)$@_s1000.txt > $(OUTPUTDIR)$@_output.txt
	#tail -n 1 $(OUTPUTDIR)$@_valgrind.log

test1_i: build
	./proj1 i $(INPUTDIR)1000.txt $(INPUTDIR)seq1000.txt $(OUTPUTDIR)s1000.txt > $(OUTPUTDIR)$@_output.txt
	#$(VALGRIND) --log-file=$(OUTPUTDIR)$@_valgrind.log ./proj1 i $(INPUTDIR)1000.txt $(OUTPUTDIR)$@_seq1000.txt $(OUTPUTDIR)$@_s1000.txt > $(OUTPUTDIR)$@_output.txt
	#tail -n 1 $(OUTPUTDIR)$@_valgrind.log

test2_s: build
	./proj1 s $(INPUTDIR)10000.txt $(INPUTDIR)seq10000.txt $(OUTPUTDIR)s10000.txt > $(OUTPUTDIR)$@_output.txt
	#$(VALGRIND) --log-file=$(OUTPUTDIR)$@_valgrind.log ./proj1 s $(INPUTDIR)10000.txt $(OUTPUTDIR)$@_seq10000.txt $(OUTPUTDIR)$@_s10000.txt > $(OUTPUTDIR)$@_output.txt
	#tail -n 1 $(OUTPUTDIR)$@_valgrind.log

test2_i: build
	./proj1 i $(INPUTDIR)10000.txt $(INPUTDIR)seq10000.txt $(OUTPUTDIR)s10000.txt > $(OUTPUTDIR)$@_output.txt
	#$(VALGRIND) --log-file=$(OUTPUTDIR)$@_valgrind.log ./proj1 i $(INPUTDIR)10000.txt $(OUTPUTDIR)$@_seq10000.txt $(OUTPUTDIR)$@_s10000.txt > $(OUTPUTDIR)$@_output.txt
	#tail -n 1 $(OUTPUTDIR)$@_valgrind.log

test3_s: build
	./proj1 s $(INPUTDIR)100000.txt $(INPUTDIR)seq100000.txt $(OUTPUTDIR)s100000.txt > $(OUTPUTDIR)$@_output.txt
	#$(VALGRIND) --log-file=$(OUTPUTDIR)$@_valgrind.log ./proj1 s $(INPUTDIR)100000.txt $(OUTPUTDIR)$@_seq100000.txt $(OUTPUTDIR)$@_s100000.txt > $(OUTPUTDIR)$@_output.txt
	#tail -n 1 $(OUTPUTDIR)$@_valgrind.log

test3_i: build
	./proj1 i $(INPUTDIR)100000.txt $(INPUTDIR)seq100000.txt $(OUTPUTDIR)s100000.txt > $(OUTPUTDIR)$@_output.txt
	#$(VALGRIND) --log-file=$(OUTPUTDIR)$@_valgrind.log ./proj1 i $(INPUTDIR)100000.txt $(OUTPUTDIR)$@_seq100000.txt $(OUTPUTDIR)$@_s100000.txt > $(OUTPUTDIR)$@_output.txt
	#tail -n 1 $(OUTPUTDIR)$@_valgrind.log

test4_s: build
	./proj1 s $(INPUTDIR)1000000.txt $(INPUTDIR)seq1000000.txt $(OUTPUTDIR)s1000000.txt > $(OUTPUTDIR)$@_output.txt
	#$(VALGRIND) --log-file=$(OUTPUTDIR)$@_valgrind.log ./proj1 s $(INPUTDIR)1000000.txt $(OUTPUTDIR)$@_seq1000000.txt $(OUTPUTDIR)$@_s1000000.txt > $(OUTPUTDIR)$@_output.txt
	#tail -n 1 $(OUTPUTDIR)$@_valgrind.log

test4_i: build
	./proj1 i $(INPUTDIR)1000000.txt $(INPUTDIR)seq1000000.txt $(OUTPUTDIR)s1000000.txt > $(OUTPUTDIR)$@_output.txt
	#$(VALGRIND) --log-file=$(OUTPUTDIR)$@_valgrind.log ./proj1 i $(INPUTDIR)1000000.txt $(OUTPUTDIR)$@_seq1000000.txt $(OUTPUTDIR)$@_s1000000.txt > $(OUTPUTDIR)$@_output.txt
	#tail -n 1 $(OUTPUTDIR)$@_valgrind.log


environment:
	mkdir -p output
