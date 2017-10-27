#include "audio_alsa.h"

int main(int argc, char *argv[])
{
    // Playback control

    AudioAlsa::setAlsaMasterMute(false);

    AudioAlsa::setMasterVolumeLevel(80);

    // Capture control

    AudioAlsa::setAlsaMicrophoneMute(false);

    AudioAlsa::setMicrophoneVolumeLevel(80);

    return 0;
}