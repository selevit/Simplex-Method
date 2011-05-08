# default: sourceData.o basis.o
#	c++ main.cpp sourceData.o basis.o -o Simplex
# basis.o: basis.h
# 	c++ -c basis.h -o basis.o
# sourceData.o: sourceData.cpp sourceData.h
#	c++ -c sourceData.cpp sourceData.h -o sourceData.o

default:
	c++ main.cpp simplex.h sourceData.cpp sourceData.h -o Simplex
