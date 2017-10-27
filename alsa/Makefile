CXX=g++
LDFLAGS=-lasound

all: audio_alsa

audio_alsa: audio_alsa.o main.o
	$(CXX) $^ -o $@ $(LDFLAGS)

main.o: main.cpp audio_alsa.o
	$(CXX) -c $< -o $@

audio_alsa.o: audio_alsa.cpp audio_alsa.h
	$(CXX) -c $< -o $@

clean:
	rm -f *.o
	rm -f audio_alsa
