CXX=g++
CXXFLAGS=-Wall
LDFLAGS=-lasound

all: audio_alsa

audio_alsa: audio_alsa.o main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

main.o: main.cpp audio_alsa.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

audio_alsa.o: audio_alsa.cpp audio_alsa.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f audio_alsa
