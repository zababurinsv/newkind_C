DEPFILE	= newkind.depend
CC	= gcc
SRCS	= alg_gfx.c alg_main.c docked.c elite.c intro.c planet.c shipdata.c shipface.c sound.c space.c swat.c threed.c vector.c random.c trade.c options.c stars.c missions.c pilot.c file.c keyboard.c
OBJS	= $(SRCS:.c=.o)
CFLAGS	= -std=c90 -pipe -Ofast -ffast-math -fno-common -falign-functions=16 -falign-loops=16 -Wall -g -I. $(shell allegro-config --cflags) -DHACKING -DHACKING_SUN_IS_POSITIVE
LIBS	= -g $(shell allegro-config --libs)
EXE	= newkind

all:
	$(MAKE) $(DEPFILE)
	$(MAKE) $(EXE)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXE): $(OBJS) Makefile
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
