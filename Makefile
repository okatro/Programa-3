# ##################################################################
#
# Makefile
# Author: Mauricio Matamoros
# License: MIT
#
# ##################################################################

CC       = gcc
CFLAGS   = -Wall
SILENT   = @
PROGRAMS = complex
.PHONY: all test clean $(PROGRAMS)

all: $(PROGRAMS)

$(PROGRAMS): %: %.c
	$(SILENT) $(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o

test:
	$(SILENT) make -s
	$(SILENT) ./complex 1+1i + 1-1i
	$(SILENT) ./complex 1+1i - 1-1i
	$(SILENT) ./complex 1+1i * 1-1i
	$(SILENT) ./complex 1+1i / 1-1i
