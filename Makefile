
OBJECTS= action.o person.o floor.o elevator.o building.o elevsim.o kbhit.o tsargs.o


CC  = g++ # Flag for implicit rules
CXX = g++ # Flag for implicit rules
CFLAGS = -g # Flag for implicit rules. Turn on debug info
LDFLAGS= -lncurses

DEPS := $(OBJS:.o=.d)

sim0teste: $(OBJECTS)
	$(CC)  $^ -o $@ $(LDFLAGS)

simulate: sim0teste
	./sim0teste -l 10 -p 350 -m 10 -y 1 -t 2 -R 600


-include $(DEPS)

%.o : %.cpp $(DEPS)
	$(CC) -MMD $(CFLAGS)  $(CPPFLAGS) -c -o $@ $< 


clean:
	rm *.o
	rm *.d
	rm sim0teste


