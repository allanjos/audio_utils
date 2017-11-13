#ifndef AUDIO_ALSA_H
#define AUDIO_ALSA_H

class AudioAlsa {
public:
    static int setMasterMute(bool mute);

    static int setMasterVolumeLevel(int volume);

    static int setMicrophoneMute(bool mute);

    static int setMicrophoneVolumeLevel(int volume);
};

#endif /* AUDIO_ALSA_H */