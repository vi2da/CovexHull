CXX = g++
CXXFLAGS = -g -Wvla -Wextra -Wall -pthread -std=c++11
LDFLAGS = -g

TARGETS = PointSetBinaryOperations ConvexHull

VALGRIND = valgrind --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes

TAR_TARGET =  ConvexHull.cpp Makefile Point.cpp Point.h PointSetBinaryOperations.cpp PointSet.cpp PointSet.h README


all: $(TARGETS)
ifeq (, $(MAKECMDGOALS))
	./$<
endif


valgrindConvexHull: ConvexHull
	$(VALGRIND) $<

valgrindBinaryOper: PointSetBinaryOperations
	$(VALGRIND) $<


$(TARGETS): %: %.o PointSet.o Point.o
	$(CXX) $(LDFLAGS) $^ -o $@

Point.o: Point.h
PointSet.o: Point.h PointSet.h
ConvexHull.o: Point.h PointSet.h
PointSetBinaryOperations.o: Point.h PointSet.h


clean:
	rm -f $(TARGETS) *.o *~

tar:
	tar cfv ex1.tar $(TAR_TARGET)

.PHONY: all clean valgrindConvexHull valgrindBinaryOper tar
