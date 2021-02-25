CXX=g++

CXXFLAGS = -Wall -Wextra -Werror

tst: tst.o test_tst.o
	${CXX} $^ -o $@
	#$^: tst.o test_tst.o
	#$@: tst

clean:
	/bin/rm -f tst *.o
