# Ensure directories for object and binary files exist
OBJDIR = build
BINDIR = bin
SRCEXTS = .c 
MY_CFLAGS = -Wall 
CFLAGS = -g -O2
CC = gcc
RM = rm -f

# Define object files for ColorazioneGrafo tests
OBJ_COLORAZIONE_GRAFO_PER_ESISTE = $(OBJDIR)/ColorazioneGrafoPerEsiste.o
OBJ_COLORAZIONE_GRAFO_PER_ESISTE_TEST = $(OBJDIR)/ColorazioneGrafoPerEsisteTest.o

OBJ_COLORAZIONE_GRAFO_PER_OGNI = $(OBJDIR)/ColorazioneGrafoPerOgni.o
OBJ_COLORAZIONE_GRAFO_PER_OGNI_TEST = $(OBJDIR)/ColorazioneGrafoPerOgniTest.o

# Define the final executables for the tests
EXE_COLORAZIONE_GRAFO_PER_ESISTE_TEST = $(BINDIR)/ColorazioneGrafoPerEsisteTest
EXE_COLORAZIONE_GRAFO_PER_OGNI_TEST = $(BINDIR)/ColorazioneGrafoPerOgniTest

# Ensure build and bin directories exist
$(shell mkdir -p $(OBJDIR) $(BINDIR))

# Compile only the objects
objs: $(OBJ_COLORAZIONE_GRAFO_PER_ESISTE) $(OBJ_COLORAZIONE_GRAFO_PER_ESISTE_TEST) \
      $(OBJ_COLORAZIONE_GRAFO_PER_OGNI) $(OBJ_COLORAZIONE_GRAFO_PER_OGNI_TEST)

# ColorazioneGrafoPerEsiste object and test object
$(OBJDIR)/ColorazioneGrafoPerEsiste.o: ColorazioneGrafoPerEsiste.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c ColorazioneGrafoPerEsiste.c -o $(OBJDIR)/ColorazioneGrafoPerEsiste.o

$(OBJDIR)/ColorazioneGrafoPerEsisteTest.o: tests/ColorazioneGrafoPerEsisteTest.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c tests/ColorazioneGrafoPerEsisteTest.c -o $(OBJDIR)/ColorazioneGrafoPerEsisteTest.o

# ColorazioneGrafoPerOgni object and test object
$(OBJDIR)/ColorazioneGrafoPerOgni.o: ColorazioneGrafoPerOgni.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c ColorazioneGrafoPerOgni.c -o $(OBJDIR)/ColorazioneGrafoPerOgni.o

$(OBJDIR)/ColorazioneGrafoPerOgniTest.o: tests/ColorazioneGrafoPerOgniTest.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c tests/ColorazioneGrafoPerOgniTest.c -o $(OBJDIR)/ColorazioneGrafoPerOgniTest.o

# Linking the test executables with their object files
$(EXE_COLORAZIONE_GRAFO_PER_ESISTE_TEST): $(OBJ_COLORAZIONE_GRAFO_PER_ESISTE) $(OBJ_COLORAZIONE_GRAFO_PER_ESISTE_TEST)
	$(CC) $(MY_CFLAGS) $(CFLAGS) -o $(EXE_COLORAZIONE_GRAFO_PER_ESISTE_TEST) $(OBJ_COLORAZIONE_GRAFO_PER_ESISTE) $(OBJ_COLORAZIONE_GRAFO_PER_ESISTE_TEST)

$(EXE_COLORAZIONE_GRAFO_PER_OGNI_TEST): $(OBJ_COLORAZIONE_GRAFO_PER_OGNI) $(OBJ_COLORAZIONE_GRAFO_PER_OGNI_TEST)
	$(CC) $(MY_CFLAGS) $(CFLAGS) -o $(EXE_COLORAZIONE_GRAFO_PER_OGNI_TEST) $(OBJ_COLORAZIONE_GRAFO_PER_OGNI) $(OBJ_COLORAZIONE_GRAFO_PER_OGNI_TEST)

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
all: $(EXE_COLORAZIONE_GRAFO_PER_ESISTE_TEST) $(EXE_COLORAZIONE_GRAFO_PER_OGNI_TEST)
