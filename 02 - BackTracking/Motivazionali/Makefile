# Ensure directories for object and binary files exist
OBJDIR = build
BINDIR = bin
SRCEXTS = .c 
MY_CFLAGS = -Wall -std=c89
CFLAGS = -g -O2
CC = gcc
RM = rm -f

# Define object files for OrdinamentoPer
OBJ_ORDINAMENTO_PER = $(OBJDIR)/OrdinamentoPer.o
OBJ_ORDINAMENTO_PER_TEST = $(OBJDIR)/OrdinamentoPerTest.o

# Define object files for ValutazioniSot
OBJ_VALUTAZIONI_SOT = $(OBJDIR)/ValutazioniSot.o
OBJ_VALUTAZIONI_SOT_TEST = $(OBJDIR)/ValutazioniSotTest.o

# Define the final executables for the tests
EXE_ORDINAMENTO_PER_TEST = $(BINDIR)/OrdinamentoPerTest
EXE_VALUTAZIONI_SOT_TEST = $(BINDIR)/ValutazioniSotTest

# Ensure build and bin directories exist
$(shell mkdir -p $(OBJDIR) $(BINDIR))

# Compile only the objects
objs: $(OBJ_ORDINAMENTO_PER) $(OBJ_ORDINAMENTO_PER_TEST) \
      $(OBJ_VALUTAZIONI_SOT) $(OBJ_VALUTAZIONI_SOT_TEST)

# OrdinamentoPer object and test object
$(OBJDIR)/OrdinamentoPer.o: OrdinamentoPer.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c OrdinamentoPer.c -o $(OBJDIR)/OrdinamentoPer.o

$(OBJDIR)/OrdinamentoPerTest.o: tests/OrdinamentoPerTest.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c tests/OrdinamentoPerTest.c -o $(OBJDIR)/OrdinamentoPerTest.o

# ValutazioniSot object and test object
$(OBJDIR)/ValutazioniSot.o: ValutazioniSot.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c ValutazioniSot.c -o $(OBJDIR)/ValutazioniSot.o

$(OBJDIR)/ValutazioniSotTest.o: tests/ValutazioniSotTest.c
	$(CC) $(MY_CFLAGS) $(CFLAGS) -c tests/ValutazioniSotTest.c -o $(OBJDIR)/ValutazioniSotTest.o

# Linking the test executables
$(EXE_ORDINAMENTO_PER_TEST): $(OBJ_ORDINAMENTO_PER) $(OBJ_ORDINAMENTO_PER_TEST)
	$(CC) $(MY_CFLAGS) $(CFLAGS) -o $(EXE_ORDINAMENTO_PER_TEST) $(OBJ_ORDINAMENTO_PER) $(OBJ_ORDINAMENTO_PER_TEST)

$(EXE_VALUTAZIONI_SOT_TEST): $(OBJ_VALUTAZIONI_SOT) $(OBJ_VALUTAZIONI_SOT_TEST)
	$(CC) $(MY_CFLAGS) $(CFLAGS) -o $(EXE_VALUTAZIONI_SOT_TEST) $(OBJ_VALUTAZIONI_SOT) $(OBJ_VALUTAZIONI_SOT_TEST)

# Clean all the generated files
clean:
	$(RM) -r $(OBJDIR) $(BINDIR)

# Show help message
help:
	@echo
	@echo 'Usage: make [TARGET]'
	@echo 'TARGETS:'
	@echo '  all       (=make) compile and link.'
	@echo '  objs      compile only (no linking).'
	@echo '  clean     clean objects and the executable file.'
	@echo '  help      print this message.'
	@echo

# Define 'all' target to build the program by default
all: $(EXE_ORDINAMENTO_PER_TEST) $(EXE_VALUTAZIONI_SOT_TEST)

