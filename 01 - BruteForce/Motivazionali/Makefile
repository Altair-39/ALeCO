# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -O2
OBJDIR = build
BINDIR = bin
SRCEXTS = .c
RM = rm -f

# Ensure build and bin directories exist
$(shell mkdir -p $(OBJDIR) $(BINDIR))

# Define object files
OBJ_VALUTAZIONEPER = $(OBJDIR)/ValutazionePer.o
OBJ_VALUTAZIONEPER_NOGREEDY_TEST = $(OBJDIR)/ValutazionePerNoGreedyTest.o

# Define the final executable
EXE_VALUTAZIONEPER_NOGREEDY_TEST = $(BINDIR)/ValutazionePerNoGreedyTest

# Compile only the objects
objs: $(OBJ_VALUTAZIONEPER) $(OBJ_VALUTAZIONEPER_NOGREEDY_TEST)

# ValutazionePer object
$(OBJDIR)/ValutazionePer.o: ValutazionePer.c 
	$(CC) $(CFLAGS) -c ValutazionePer.c -o $(OBJDIR)/ValutazionePer.o

# ValutazionePer test object
$(OBJDIR)/ValutazionePerNoGreedyTest.o: tests/ValutazionePerNoGreedyTest.c 
	$(CC) $(CFLAGS) -c tests/ValutazionePerNoGreedyTest.c -o $(OBJDIR)/ValutazionePerNoGreedyTest.o

# Linking the test executable
$(EXE_VALUTAZIONEPER_NOGREEDY_TEST): $(OBJ_VALUTAZIONEPER) $(OBJ_VALUTAZIONEPER_NOGREEDY_TEST)
	$(CC) $(CFLAGS) -o $(EXE_VALUTAZIONEPER_NOGREEDY_TEST) $(OBJ_VALUTAZIONEPER) $(OBJ_VALUTAZIONEPER_NOGREEDY_TEST)

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
all: $(EXE_VALUTAZIONEPER_NOGREEDY_TEST)

