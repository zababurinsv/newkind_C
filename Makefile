DEPFILE	= newkind.depend
CC	= gcc
SRCS	= datafilebank.c SDL2_gfxPrimitives.c SDL2_rotozoom.c sdl.c main.c docked.c elite.c intro.c planet.c shipdata.c shipface.c sound.c space.c swat.c threed.c vector.c random.c trade.c options.c stars.c missions.c pilot.c file.c keyboard.c
OBJS	= $(SRCS:.c=.o)
CFLAGS	= -std=c99 -pipe -Ofast -ffast-math -fno-common -falign-functions=16 -falign-loops=16 -Wall -g -I. $(shell sdl2-config --cflags)
#CFLAGS	= -std=c99 -pipe -O0 -fno-common -falign-functions=16 -falign-loops=16 -Wall -g -I. $(shell sdl2-config --cflags)
LDFLAGS	= -g $(shell sdl2-config --libs) -lm
EXE	= newkind
ALLDEPS	= Makefile

all:
	$(MAKE) dep
	$(MAKE) $(EXE)

datafilebank.c: data/*
	data/datafile.sh > $@

.c.o: $(ALLDEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXE): $(OBJS) $(ALLDEPS)
	$(CC) -o $(EXE) $(OBJS) $(LDFLAGS)

dep:	datafilebank.c
	$(MAKE) $(DEPFILE)

$(DEPFILE): $(ALLDEPS) *.c *.h datafilebank.c
	$(CC) -MM $(CFLAGS) $(SRCS) > $(DEPFILE)

clean:
	rm -f $(OBJS) $(EXE)

distclean:
	$(MAKE) clean
	rm -f *.depend *~ *.swp a.out datafilebank.c

.PHONY: dep all clean distclean

ifneq ($(wildcard $(DEPFILE)),)
include $(DEPFILE)
endif
