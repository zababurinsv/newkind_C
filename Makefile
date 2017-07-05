DEPFILE	= newkind.depend

CC	= gcc

SRCS = alg_gfx.c alg_main.c docked.c elite.c intro.c planet.c shipdata.c shipface.c sound.c space.c swat.c threed.c vector.c random.c trade.c options.c stars.c missions.c pilot.c file.c keyboard.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Ofast --fast-math -Wall -g $(shell allegro-config --cflags)
LIBS = $(shell allegro-config --libs)

EXE	= newkind

all:
	$(MAKE) $(DEPFILE)
	$(MAKE) $(EXE)

.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -c $<

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LIBS)

dep:
	$(MAKE) $(DEPFILE)

$(DEPFILE): Makefile *.c *.h
	$(CC) -MM $(CFLAGS) $(SRCS) > $(DEPFILE)

clean:
	rm -f $(OBJS) $(EXE)

distclean:
	$(MAKE) clean
	rm -f $(DEPFILE) *~ *.swp a.out

.PHONY: dep all clean distclean

ifneq ($(wildcard $(DEPFILE)),)
	include $(DEPFILE)
endif
