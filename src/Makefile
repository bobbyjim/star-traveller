SOURCES = main.c astrogation.c command_menu.c common.c emplacement.c gamestate.c map.c menu.c missions.c player.c ship.c shipyard.c splash.c starport.c trade.c

PROGRAM = STARTRAV
CC65_TARGET = cx16

CC	= cl65 
CFLAGS 	= --cpu 65c02 -t $(CC65_TARGET) --create-dep $(<:.c=.d) -Ors 
LDFLAGS	= -t $(CC65_TARGET) -m $(PROGRAM).map
OBJDIR  = .obj

#############################################
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

.SUFFIXES: 
all: $(PROGRAM)

ifneq (($MAKECMDGOALS),clean)
-include $(SOURCES:.c=.d)
endif

clean:
	$(RM) $(OBJECTS) $(SOURCES:.c=.d) $(PROGRAM) $(PROGRAM).map

.PHONY: all clean

$(PROGRAM): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJECTS): $(OBJDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
