#ifndef AUDIO_ALSA_H
#define AUDIO_ALSA_H

class AudioAlsa {
public:
    static int setAlsaMasterMute(bool mute);

    static int setMasterVolumeLevel(int volume);

    static int setAlsaMicrophoneMute(bool mute);

    static int setMicrophoneVolumeLevel(int volume);
};

#endif /* AUDIO_ALSA_H */