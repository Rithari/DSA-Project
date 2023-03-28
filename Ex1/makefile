CC=gcc
CFLAGS=-Ofast
BINDIR=bin
SRCDIR=source
INFILE=records.csv
OUTFILE=sorted.csv
DEPS=$(SRCDIR)/MergeBinSorter.c $(SRCDIR)/main_ex1.c $(SRCDIR)/ReaderUtility.c

all: clean $(BINDIR)/main_ex1

$(BINDIR)/main_ex1: $(DEPS) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BINDIR):
	mkdir $(BINDIR)

field1: $(BINDIR)/main_ex1 $(INFILE)
	$(BINDIR)/main_ex1 $(INFILE) $(OUTFILE) 94 1

field2: $(BINDIR)/main_ex1 $(INFILE)
	$(BINDIR)/main_ex1 $(INFILE) $(OUTFILE) 94 2

field3: $(BINDIR)/main_ex1 $(INFILE)
	$(BINDIR)/main_ex1 $(INFILE) $(OUTFILE) 88 3

run: all field2

clean:
	rm -rf $(BINDIR) $(OUTFILE)
