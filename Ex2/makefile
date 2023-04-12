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

# <max_height> is optimal between 16 and 20
run: all
	$(BINDIR)/main_ex2 $(INFILE) $(INFILE2) 18

test: $(SRCDIR)/test_SkipList.c $(SRCDIR)/SkipList.c $(SRCDIR)/unity.c
	$(CC) $(CFLAGS) $^ -o $(BINDIR)/test_SkipList
	$(BINDIR)/test_SkipList

clean:
	rm -rf $(BINDIR)
