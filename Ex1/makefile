CC=gcc
CFLAGS=-Ofast
BINDIR=bin
SRCDIR=source
INFILE=records.csv
OUTFILE=sorted.csv
DEPS=$(SRCDIR)/MergeBinSorter.c $(SRCDIR)/main_ex1.c $(SRCDIR)/ReaderUtility.c

all: $(BINDIR)/main_ex1

$(BINDIR)/main_ex1: $(BINDIR) $(DEPS)
	$(CC) $(CFLAGS) $^ -o $@

$(BINDIR):
	mkdir $(BINDIR)

clean:
	rm -rf $(BINDIR) $(OUTFILE)

field1: $(BINDIR)/main_ex1 $(INFILE)
	$(BINDIR)/main_ex1 $(INFILE) $(OUTFILE) 77 1

field2: $(BINDIR)/main_ex1 $(INFILE)
	$(BINDIR)/main_ex1 $(INFILE) $(OUTFILE) 40 2

field3: $(BINDIR)/main_ex1 $(INFILE)
	$(BINDIR)/main_ex1 $(INFILE) $(OUTFILE) 10 3
