CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lgsl -lgslcblas -lm

TARGETS = byn single
SOURCES_BYN = beggar.c shuffle.c byn.c queue.c statistics.c
SOURCES_SINGLE = beggar.c shuffle.c single.c queue.c

all: $(TARGETS)

byn: $(SOURCES_BYN)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

single: $(SOURCES_SINGLE)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f $(TARGETS)

# Execution Steps:
# 1. Run "make" command to compile the byn and single executables.
# 2. Run "./byn" or "./single" to execute the respective program.
# 3. Run "make clean" command to remove the generated executables.