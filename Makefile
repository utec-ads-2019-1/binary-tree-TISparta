IDIR = ./include
SDIR = ./src
CXX = g++
CXXFLAGS = -std=c++11 -w -O2 -I $(IDIR)

ODIR = ./obj

_HEADERS = bstree.h iterator.h mocker.h node.h tester.h color.h
HEADERS = $(patsubst %,$(IDIR)/%,$(_HEADERS))

_OBJ = main.o tester.o mocker.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

run: $(OBJ)
	$(CXX) -o $@ $(OBJ) $(CXXFLAGS)

$(ODIR):
	mkdir $@

$(ODIR)/main.o: $(SDIR)/main.cpp $(SDIR)/tester.cpp | $(ODIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/tester.o: $(SDIR)/tester.cpp $(HEADERS) | $(ODIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/mocker.o: $(SDIR)/mocker.cpp $(IDIR)/mocker.h | $(ODIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	rm -rf $(ODIR)
	rm run


