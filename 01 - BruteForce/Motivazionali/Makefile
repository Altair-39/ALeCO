# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -O2
OBJDIR = build
BINDIR = bin
SRCEXTS = .c
RM = rm -f

# Ensure build and bin directories exist
$(shell mkdir -p $(OBJDIR) $(BINDIR))

# Define object files for ValutazionePer
OBJ_VALUTAZIONEPER = $(OBJDIR)/ValutazionePer.o
OBJ_VALUTAZIONEPER_NOGREEDY_TEST = $(OBJDIR)/ValutazionePerNoGreedyTest.o

# Define object files for ValutazioneSot
OBJ_VALUTAZIONESOT = $(OBJDIR)/ValutazioneSot.o
OBJ_VALUTAZIONESOT_NOGREEDY_TEST = $(OBJDIR)/ValutazioneSotNoGreedyTest.o

# Define object files for ValutazioneSotSmallTest
OBJ_VALUTAZIONESOT_SMALL_TEST = $(OBJDIR)/ValutazioneSotSmallTest.o

# Define the final executable files
EXE_VALUTAZIONEPER = $(BINDIR)/ValutazionePer
EXE_VALUTAZIONEPER_NOGREEDY_TEST = $(BINDIR)/ValutazionePerNoGreedyTest
EXE_VALUTAZIONESOT = $(BINDIR)/ValutazioneSot
EXE_VALUTAZIONESOT_NOGREEDY_TEST = $(BINDIR)/ValutazioneSotNoGreedyTest
EXE_VALUTAZIONESOT_SMALL_TEST = $(BINDIR)/ValutazioneSotSmallTest

# Compile only the objects
objs: $(OBJ_VALUTAZIONEPER) $(OBJ_VALUTAZIONEPER_NOGREEDY_TEST) $(OBJ_VALUTAZIONESOT) $(OBJ_VALUTAZIONESOT_NOGREEDY_TEST) $(OBJ_VALUTAZIONESOT_SMALL_TEST)

# ValutazionePer object
$(OBJDIR)/ValutazionePer.o: ValutazionePer.c
	$(CC) $(CFLAGS) -c ValutazionePer.c -o $(OBJDIR)/ValutazionePer.o

# ValutazionePer test object
$(OBJDIR)/ValutazionePerNoGreedyTest.o: tests/ValutazionePerNoGreedyTest.c
	$(CC) $(CFLAGS) -c tests/ValutazionePerNoGreedyTest.c -o $(OBJDIR)/ValutazionePerNoGreedyTest.o

# ValutazioneSot object
$(OBJDIR)/ValutazioneSot.o: ValutazioneSot.c
	$(CC) $(CFLAGS) -c ValutazioneSot.c -o $(OBJDIR)/ValutazioneSot.o

# ValutazioneSot test object
$(OBJDIR)/ValutazioneSotNoGreedyTest.o: tests/ValutazioneSotNoGreedyTest.c
	$(CC) $(CFLAGS) -c tests/ValutazioneSotNoGreedyTest.c -o $(OBJDIR)/ValutazioneSotNoGreedyTest.o

# ValutazioneSotSmallTest object
$(OBJDIR)/ValutazioneSotSmallTest.o: tests/ValutazioneSotSmallTest.c
	$(CC) $(CFLAGS) -c tests/ValutazioneSotSmallTest.c -o $(OBJDIR)/ValutazioneSotSmallTest.o

# Linking the ValutazionePer executable
$(EXE_VALUTAZIONEPER): $(OBJ_VALUTAZIONEPER)
	$(CC) $(CFLAGS) -o $(EXE_VALUTAZIONEPER) $(OBJ_VALUTAZIONEPER)

# Linking the ValutazionePer test executable
$(EXE_VALUTAZIONEPER_NOGREEDY_TEST): $(OBJ_VALUTAZIONEPER) $(OBJ_VALUTAZIONEPER_NOGREEDY_TEST)
	$(CC) $(CFLAGS) -o $(EXE_VALUTAZIONEPER_NOGREEDY_TEST) $(OBJ_VALUTAZIONEPER) $(OBJ_VALUTAZIONEPER_NOGREEDY_TEST)

# Linking the ValutazioneSot executable
$(EXE_VALUTAZIONESOT): $(OBJ_VALUTAZIONESOT)
	$(CC) $(CFLAGS) -o $(EXE_VALUTAZIONESOT) $(OBJ_VALUTAZIONESOT)

# Linking the ValutazioneSot test executable
$(EXE_VALUTAZIONESOT_NOGREEDY_TEST): $(OBJ_VALUTAZIONESOT) $(OBJ_VALUTAZIONESOT_NOGREEDY_TEST)
	$(CC) $(CFLAGS) -o $(EXE_VALUTAZIONESOT_NOGREEDY_TEST) $(OBJ_VALUTAZIONESOT) $(OBJ_VALUTAZIONESOT_NOGREEDY_TEST)

# Linking the ValutazioneSotSmallTest executable
$(EXE_VALUTAZIONESOT_SMALL_TEST): $(OBJ_VALUTAZIONESOT) $(OBJ_VALUTAZIONESOT_SMALL_TEST)
	$(CC) $(CFLAGS) -o $(EXE_VALUTAZIONESOT_SMALL_TEST) $(OBJ_VALUTAZIONESOT) $(OBJ_VALUTAZIONESOT_SMALL_TEST)

# Clean all the generated files
clean:
	$(RM) -r $(OBJDIR) $(BINDIR)

# Clean all files and dependencies
distclean: clean

# Show help message
help:
	@echo
	@echo 'Usage: make [TARGET]'
	@echo 'TARGETS:'
	@echo '  all       (=make) compile and link.'
	@echo '  nodep=yes make without generating dependencies.'
	@echo '  objs      compile only (no linking).'
	@echo '  clean     clean objects and the executable file.'
	@echo '  distclean clean objects, the executable and dependencies.'
	@echo '  help      print this message.'
	@echo

# Define 'all' target to build the program by default
all: $(EXE_VALUTAZIONEPER_NOGREEDY_TEST) $(EXE_VALUTAZIONESOT_NOGREEDY_TEST) $(EXE_VALUTAZIONESOT_SMALL_TEST)

