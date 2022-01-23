#
# Makefile for CANopen applications
#

include Make.vars

APPL=canapp

LIBS=-lchai

FILES_MASTER=*.c common/*.c master/*.c
FILES_SLAVE=*.c common/*.c slave/*.c
FILES_TEST=*.c common/*.c master/*.c slave/*.c

canslave:
	$(CC) $(CHAICF) $(CFLAGS) $(FILES_SLAVE) $<
	$(CC) $(CHAILF) $(OBJS) -o $(APPL) $(LIBS)
	rm -f *.o

canmaster:
	$(CC) $(CHAICF) $(CFLAGS) $(FILES_MASTER) $<
	$(CC) $(CHAILF) $(OBJS) -o $(APPL) $(LIBS)
	rm -f *.o

cantest:
	$(CC) $(CHAICF) $(CFLAGS) $(FILES_TEST) $<
	$(CC) $(OBJS) -o $(APPL)
	rm -f *.o

clean:
	rm -f */*.o */$(APPL)
	rm -f *.o $(APPL)
