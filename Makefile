
OBJECTS= action.o person.o floor.o elevator.o building.o elevsim.o kbhit.o tsargs.o


CC  = g++ # Flag for implicit rules
CXX = g++ # Flag for implicit rules
CFLAGS = -g # Flag for implicit rules. Turn on debug info
LDFLAGS= -lncurses

DEPS := $(OBJS:.o=.d)

sim0teste: $(OBJECTS)
	$(CC)  $^ -o $@ $(LDFLAGS)


-include $(DEPS)

%.o : %.cpp $(DEPS)
	$(CC) -MMD $(CFLAGS)  $(CPPFLAGS) -c -o $@ $< 


clean:
	rm *.o
	rm *.d
	rm sim0teste


