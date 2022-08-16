CXXFLAGS=-DRPI -DRCSwitchDisableReceiving -DDisableProtocolB

all: send

send: RCSwitch.o send.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lpthread -lcrypt -lrt

clean:
	$(RM) *.o send
