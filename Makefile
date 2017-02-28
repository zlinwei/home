all: client rf433

rf433: rf433.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi

client: client.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lmosquitto

clean:
	$(RM) *.o rf433 client
