CC=gcc
CFLAGS=-Ofast
BINDIR=build
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
	$(BINDIR)/main_ex1 $(INFILE) $(OUTFILE) 20 1

field2: $(BINDIR)/main_ex1 $(INFILE)
	$(BINDIR)/main_ex1 $(INFILE) $(OUTFILE) 22 2

field3: $(BINDIR)/main_ex1 $(INFILE)
	$(BINDIR)/main_ex1 $(INFILE) $(OUTFILE) 21 3

run: all field2

test: $(SRCDIR)/test_MergeBinSorter.c $(SRCDIR)/MergeBinSorter.c $(SRCDIR)/unity.c
	$(CC) $(CFLAGS) $^ -o $(BINDIR)/test_MergeBinSorter
	$(BINDIR)/test_MergeBinSorter
clean:
	rm -rf $(BINDIR) $(OUTFILE)
