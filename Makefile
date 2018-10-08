CC = gcc
C2 = -std=c99
PROGNAME = huff_compress
PROGNAME2 = huff_uncompress
source = huffman.c
source2 = decompression.c

all :  $(PROGNAME) $(PROGNAME2)


huff.o : huffman.c
	$(CC) -c -g huffman.cpp

uncompress.o : decompression.c
	$(CC) -c -g decompression.cpp

$(PROGNAME) : $(source:.cpp=.o)
	$(CC) $(C2) $(source:.cpp=.o) -o $(PROGNAME)
	rm -rf *.o

$(PROGNAME2) : $(source2:.cpp=.o)
	$(CC) $(C2) $(source2:.cpp=.o) -o $(PROGNAME2)
	rm -rf *.o

t = `date +%d_%m_%Y_%H%M`
#!date -I

save : $(PROGNAME)
	tar -cvf $(t).tar.gz $(PROGNAME)
