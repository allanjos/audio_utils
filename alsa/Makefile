CXX=g++
LDFLAGS=-lasound

audio_alsa: audio_alsa.o
	$(CXX) $? -o $@ $(LDFLAGS)

audio_alsa.o: audio_alsa.cpp
	$(CXX) -c $? -o $@

clean:
	rm -f *.o
	rm -f audio_alsa