# Ensure directories for object and binary files exist
OBJDIR = build
BINDIR = bin
SRCEXTS = .c 
MY_CFLAGS = -Wall -std=c89 -pedantic
CFLAGS = -g -O2
CC = gcc
RM = rm -f

# Define object files for Regine tests
OBJ_REGINE_PER_ESISTE = $(OBJDIR)/ReginePerEsiste.o
OBJ_REGINE_PER_ESISTE_TEST = $(OBJDIR)/ReginePerEsisteTest.o

OBJ_REGINE_PER_OGNI = $(OBJDIR)/ReginePerOgni.o
OBJ_REGINE_PER_OGNI_TEST = $(OBJDIR)/ReginePerOgniTest.o

# Define the final executables for the tests
EXE_REGINE_PER_ESISTE_TEST = $(BINDIR)/ReginePerEsisteTest
EXE_REGINE_PER_OGNI_TEST = $(BINDIR)/ReginePerOgniTest

# Ensure build and bin directories exist
$(shell mkdir -p $(OBJDIR) $(BINDIR))

# Compile only the objects
objs: $(OBJ_REGINE_PER_ESISTE) $(OBJ_REGINE_PER_ESISTE_TEST) \
      $(OBJ_REGINE_PER_OGNI) $(OBJ_REGINE_PER_OGNI_TEST)

# ReginePerEsiste object and test object
$(OBJDIR)/ReginePerEsiste.o: ReginePerEsiste.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c ReginePerEsiste.c -o $(OBJDIR)/ReginePerEsiste.o

$(OBJDIR)/ReginePerEsisteTest.o: tests/ReginePerEsisteTest.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c tests/ReginePerEsisteTest.c -o $(OBJDIR)/ReginePerEsisteTest.o

# ReginePerOgni object and test object
$(OBJDIR)/ReginePerOgni.o: ReginePerOgni.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c ReginePerOgni.c -o $(OBJDIR)/ReginePerOgni.o

$(OBJDIR)/ReginePerOgniTest.o: tests/ReginePerOgniTest.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c tests/ReginePerOgniTest.c -o $(OBJDIR)/ReginePerOgniTest.o

# Linking the test executables with their object files
$(EXE_REGINE_PER_ESISTE_TEST): $(OBJ_REGINE_PER_ESISTE) $(OBJ_REGINE_PER_ESISTE_TEST)
	$(CC) $(MY_CFLAGS) $(CFLAGS) -o $(EXE_REGINE_PER_ESISTE_TEST) $(OBJ_REGINE_PER_ESISTE) $(OBJ_REGINE_PER_ESISTE_TEST)

$(EXE_REGINE_PER_OGNI_TEST): $(OBJ_REGINE_PER_OGNI) $(OBJ_REGINE_PER_OGNI_TEST)
	$(CC) $(MY_CFLAGS) $(CFLAGS) -o $(EXE_REGINE_PER_OGNI_TEST) $(OBJ_REGINE_PER_OGNI) $(OBJ_REGINE_PER_OGNI_TEST)

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
all: $(EXE_REGINE_PER_ESISTE_TEST) $(EXE_REGINE_PER_OGNI_TEST)

