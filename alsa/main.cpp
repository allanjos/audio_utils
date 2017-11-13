#include "audio_alsa.h"

int main(int argc, char *argv[])
{
    // Playback control

    AudioAlsa::setMasterMute(false);

    AudioAlsa::setMasterVolumeLevel(90);

    // Capture control

    AudioAlsa::setMicrophoneMute(false);

    AudioAlsa::setMicrophoneVolumeLevel(80);

    return 0;
}