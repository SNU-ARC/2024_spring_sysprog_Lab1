CC=gcc
CFLAGS=-g
TARGET=abstr1_hexdump abstr2_mm abstr3_proc_sched

all: $(TARGET)
 
clean:
	rm -f $(TARGET)
 
$(TARGET): %: %.c
	$(CC) $(CFLAGS) -o $@ $@.c
