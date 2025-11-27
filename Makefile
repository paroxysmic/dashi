OBJDIR := obj
LIBDIR := lib
SRCDIR := src
DBGOBJDIR := dbg-obj
LIBFILES := $(wildcard $(LIBDIR)/*.cpp)
OBJFILES := $(patsubst $(LIBDIR)/%.cpp,$(OBJDIR)/%.o,$(LIBFILES))
DBGOBJFILES := $(patsubst $(LIBDIR)/%.cpp,$(DBGOBJDIR)/%.o, $(LIBFILES))
main: $(OBJFILES) $(SRCDIR)/main.cpp
	g++ -c $(SRCDIR)/main.cpp -Iinclude -O3 -o $(OBJDIR)/main.o
	g++ $(OBJFILES) $(OBJDIR)/main.o -O3 -o main
test: $(DBGOBJFILES) $(SRCDIR)/test.cpp
	g++ -c -g $(SRCDIR)/test.cpp -Iinclude -O0 -o $(DBGOBJDIR)/test.o
	g++ -g $(DBGOBJFILES) $(DBGOBJDIR)/test.o -O0 -o test
$(OBJDIR)/%.o: $(LIBDIR)/%.cpp
	g++ -c $< -Iinclude -O3 -o $@
$(DBGOBJDIR)/%.o: $(LIBDIR)/%.cpp
	g++ -c $< -Iinclude -g -O0 -o $@
.PHONY: clean init
clean:
	rm -f $(OBJFILES)
	rm -f $(DBGOBJFILES)
	rm -f main test
init:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(LIBDIR)
	@mkdir -p $(SRCDIR)
	@mkdir -p $(DBGOBJDIR)
	@mkdir -p include