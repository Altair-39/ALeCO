# Ensure directories for object and binary files exist
OBJDIR = build
BINDIR = bin
SRCEXTS = .c 
MY_CFLAGS = -Wall 
CFLAGS = -g -O2
CC = gcc
RM = rm -f

# Define object files for CamminoHamiltoniano tests
OBJ_CAMMINO_HAMILTONIANO_PER_ESISTE = $(OBJDIR)/CamminoHamiltonianoPerEsiste.o
OBJ_CAMMINO_HAMILTONIANO_PER_ESISTE_TEST = $(OBJDIR)/CamminoHamiltonianoPerEsisteTest.o

OBJ_CAMMINO_HAMILTONIANO_PER_OGNI = $(OBJDIR)/CamminoHamiltonianoPerOgni.o
OBJ_CAMMINO_HAMILTONIANO_PER_OGNI_TEST = $(OBJDIR)/CamminoHamiltonianoPerOgniTest.o

# Define the final executables for the tests
EXE_CAMMINO_HAMILTONIANO_PER_ESISTE_TEST = $(BINDIR)/CamminoHamiltonianoPerEsisteTest
EXE_CAMMINO_HAMILTONIANO_PER_OGNI_TEST = $(BINDIR)/CamminoHamiltonianoPerOgniTest

# Ensure build and bin directories exist
$(shell mkdir -p $(OBJDIR) $(BINDIR))

# Compile only the objects
objs: $(OBJ_CAMMINO_HAMILTONIANO_PER_ESISTE) $(OBJ_CAMMINO_HAMILTONIANO_PER_ESISTE_TEST) \
      $(OBJ_CAMMINO_HAMILTONIANO_PER_OGNI) $(OBJ_CAMMINO_HAMILTONIANO_PER_OGNI_TEST)

# CamminoHamiltonianoPerEsiste object and test object
$(OBJDIR)/CamminoHamiltonianoPerEsiste.o: CamminoHamiltonianoPerEsiste.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c CamminoHamiltonianoPerEsiste.c -o $(OBJDIR)/CamminoHamiltonianoPerEsiste.o

$(OBJDIR)/CamminoHamiltonianoPerEsisteTest.o: tests/CamminoHamiltonianoPerEsisteTest.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c tests/CamminoHamiltonianoPerEsisteTest.c -o $(OBJDIR)/CamminoHamiltonianoPerEsisteTest.o

# CamminoHamiltonianoPerOgni object and test object
$(OBJDIR)/CamminoHamiltonianoPerOgni.o: CamminoHamiltonianoPerOgni.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c CamminoHamiltonianoPerOgni.c -o $(OBJDIR)/CamminoHamiltonianoPerOgni.o

$(OBJDIR)/CamminoHamiltonianoPerOgniTest.o: tests/CamminoHamiltonianoPerOgniTest.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c tests/CamminoHamiltonianoPerOgniTest.c -o $(OBJDIR)/CamminoHamiltonianoPerOgniTest.o

# Linking the test executables with their object files
$(EXE_CAMMINO_HAMILTONIANO_PER_ESISTE_TEST): $(OBJ_CAMMINO_HAMILTONIANO_PER_ESISTE) $(OBJ_CAMMINO_HAMILTONIANO_PER_ESISTE_TEST)
	$(CC) $(MY_CFLAGS) $(CFLAGS) -o $(EXE_CAMMINO_HAMILTONIANO_PER_ESISTE_TEST) $(OBJ_CAMMINO_HAMILTONIANO_PER_ESISTE) $(OBJ_CAMMINO_HAMILTONIANO_PER_ESISTE_TEST)

$(EXE_CAMMINO_HAMILTONIANO_PER_OGNI_TEST): $(OBJ_CAMMINO_HAMILTONIANO_PER_OGNI) $(OBJ_CAMMINO_HAMILTONIANO_PER_OGNI_TEST)
	$(CC) $(MY_CFLAGS) $(CFLAGS) -o $(EXE_CAMMINO_HAMILTONIANO_PER_OGNI_TEST) $(OBJ_CAMMINO_HAMILTONIANO_PER_OGNI) $(OBJ_CAMMINO_HAMILTONIANO_PER_OGNI_TEST)

# Clean all the generated files
clean:
	$(RM) -r $(OBJDIR) $(BINDIR)

# Clean all files and dependencies
distclean: clean
	$(RM) $(DEPS)

# Show help message
help:
	@echo
	@echo 'Usage: make [TARGET]'
	@echo 'TARGETS:'
	@echo '  all       (=make) compile and link.'
	@echo '  NODEP=yes make without generating dependencies.'
	@echo '  objs      compile only (no linking).'
	@echo '  clean     clean objects and the executable file.'
	@echo '  distclean clean objects, the executable and dependencies.'
	@echo '  help      print this message.'
	@echo

# Define 'all' target to build the program by default
all: $(EXE_CAMMINO_HAMILTONIANO_PER_ESISTE_TEST) $(EXE_CAMMINO_HAMILTONIANO_PER_OGNI_TEST)
