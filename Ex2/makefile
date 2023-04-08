CC=gcc
CFLAGS=-Ofast
BINDIR=build
SRCDIR=source
INFILE=dictionary.txt
INFILE2=correctme.txt
DEPS=$(SRCDIR)/SkipList.c $(SRCDIR)/main_ex2.c

all: clean $(BINDIR)/main_ex2

$(BINDIR)/main_ex2: $(DEPS) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

run: all
	$(BINDIR)/main_ex2 $(INFILE) $(INFILE2) 4

clean:
	rm -rf $(BINDIR)