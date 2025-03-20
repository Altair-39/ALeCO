# Ensure directories for object and binary files exist
OBJDIR = build
BINDIR = bin
SRCEXTS = .c 
MY_CFLAGS = -Wall
CFLAGS = -g -O2
CC = gcc
RM = rm -f

# Define object files for different source files
OBJ_DISPOSIZIONI = $(OBJDIR)/Disposizioni.o
OBJ_DISPOSIZIONI_TEST = $(OBJDIR)/DisposizioniTest.o

OBJ_DISPOSIZIONI_RPT = $(OBJDIR)/DisposizioniRpt.o
OBJ_DISPOSIZIONI_RPT_TEST = $(OBJDIR)/DisposizioniRptTest.o

OBJ_PERMUTAZIONI = $(OBJDIR)/Permutazioni.o
OBJ_PERMUTAZIONI_TEST = $(OBJDIR)/PermutazioniTest.o

OBJ_PERMUTAZIONI_RPT = $(OBJDIR)/PermutazioniRpt.o
OBJ_PERMUTAZIONI_RPT_TEST = $(OBJDIR)/PermutazioniRptTest.o

OBJ_SOTTOINSIEMI = $(OBJDIR)/Sottoinsiemi.o
OBJ_SOTTOINSIEMI_TEST = $(OBJDIR)/SottoinsiemiTest.o

# Define the final executables for the tests
EXE_DISPOSIZIONI_TEST = $(BINDIR)/DisposizioniTest
EXE_DISPOSIZIONI_RPT_TEST = $(BINDIR)/DisposizioniRptTest
EXE_PERMUTAZIONI_TEST = $(BINDIR)/PermutazioniTest
EXE_PERMUTAZIONI_RPT_TEST = $(BINDIR)/PermutazioniRptTest
EXE_SOTTOINSIEMI_TEST = $(BINDIR)/SottoinsiemiTest

# Ensure build and bin directories exist
$(shell mkdir -p $(OBJDIR) $(BINDIR))

# Compile only the objects
objs: $(OBJ_DISPOSIZIONI) $(OBJ_DISPOSIZIONI_TEST) \
      $(OBJ_DISPOSIZIONI_RPT) $(OBJ_DISPOSIZIONI_RPT_TEST) \
      $(OBJ_PERMUTAZIONI) $(OBJ_PERMUTAZIONI_TEST) \
      $(OBJ_PERMUTAZIONI_RPT) $(OBJ_PERMUTAZIONI_RPT_TEST) \
      $(OBJ_SOTTOINSIEMI) $(OBJ_SOTTOINSIEMI_TEST)

# Disposizioni object and test object
$(OBJDIR)/Disposizioni.o: Disposizioni.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c Disposizioni.c -o $(OBJDIR)/Disposizioni.o

$(OBJDIR)/DisposizioniTest.o: tests/DisposizioniTest.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c tests/DisposizioniTest.c -o $(OBJDIR)/DisposizioniTest.o

# DisposizioniRpt object and test object
$(OBJDIR)/DisposizioniRpt.o: DisposizioniRpt.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c DisposizioniRpt.c -o $(OBJDIR)/DisposizioniRpt.o

$(OBJDIR)/DisposizioniRptTest.o: tests/DisposizioniRptTest.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c tests/DisposizioniRptTest.c -o $(OBJDIR)/DisposizioniRptTest.o

# Permutazioni object and test object
$(OBJDIR)/Permutazioni.o: Permutazioni.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c Permutazioni.c -o $(OBJDIR)/Permutazioni.o

$(OBJDIR)/PermutazioniTest.o: tests/PermutazioniTest.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c tests/PermutazioniTest.c -o $(OBJDIR)/PermutazioniTest.o

# PermutazioniRpt object and test object
$(OBJDIR)/PermutazioniRpt.o: PermutazioniRpt.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c PermutazioniRpt.c -o $(OBJDIR)/PermutazioniRpt.o

$(OBJDIR)/PermutazioniRptTest.o: tests/PermutazioniRptTest.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c tests/PermutazioniRptTest.c -o $(OBJDIR)/PermutazioniRptTest.o

# Sottoinsiemi object and test object
$(OBJDIR)/Sottoinsiemi.o: Sottoinsiemi.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c Sottoinsiemi.c -o $(OBJDIR)/Sottoinsiemi.o

$(OBJDIR)/SottoinsiemiTest.o: tests/SottoinsiemiTest.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c tests/SottoinsiemiTest.c -o $(OBJDIR)/SottoinsiemiTest.o

# Linking the test executables with their object files
$(EXE_DISPOSIZIONI_TEST): $(OBJ_DISPOSIZIONI) $(OBJ_DISPOSIZIONI_TEST)
	$(CC) $(MY_CFLAGS) $(CFLAGS) -o $(EXE_DISPOSIZIONI_TEST) $(OBJ_DISPOSIZIONI) $(OBJ_DISPOSIZIONI_TEST)

$(EXE_DISPOSIZIONI_RPT_TEST): $(OBJ_DISPOSIZIONI_RPT) $(OBJ_DISPOSIZIONI_RPT_TEST)
	$(CC) $(MY_CFLAGS) $(CFLAGS) -o $(EXE_DISPOSIZIONI_RPT_TEST) $(OBJ_DISPOSIZIONI_RPT) $(OBJ_DISPOSIZIONI_RPT_TEST)

$(EXE_PERMUTAZIONI_TEST): $(OBJ_PERMUTAZIONI) $(OBJ_PERMUTAZIONI_TEST)
	$(CC) $(MY_CFLAGS) $(CFLAGS) -o $(EXE_PERMUTAZIONI_TEST) $(OBJ_PERMUTAZIONI) $(OBJ_PERMUTAZIONI_TEST)

$(EXE_PERMUTAZIONI_RPT_TEST): $(OBJ_PERMUTAZIONI_RPT) $(OBJ_PERMUTAZIONI_RPT_TEST)
	$(CC) $(MY_CFLAGS) $(CFLAGS) -o $(EXE_PERMUTAZIONI_RPT_TEST) $(OBJ_PERMUTAZIONI_RPT) $(OBJ_PERMUTAZIONI_RPT_TEST)

# Sottoinsiemi test executable
$(EXE_SOTTOINSIEMI_TEST): $(OBJ_SOTTOINSIEMI) $(OBJ_SOTTOINSIEMI_TEST)
	$(CC) $(MY_CFLAGS) $(CFLAGS) -o $(EXE_SOTTOINSIEMI_TEST) $(OBJ_SOTTOINSIEMI) $(OBJ_SOTTOINSIEMI_TEST)

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
all: $(EXE_DISPOSIZIONI_TEST) $(EXE_DISPOSIZIONI_RPT_TEST) $(EXE_PERMUTAZIONI_TEST) $(EXE_PERMUTAZIONI_RPT_TEST) $(EXE_SOTTOINSIEMI_TEST)

