#include <alsa/asoundlib.h>

class AudioAlsa {
public:
    static int setAlsaMasterMute(bool mute);

    static int setMasterVolumeLevel(int volume);

    static int setAlsaMicrophoneMute(bool mute);

    static int setMicrophoneVolumeLevel(int volume);
};

int AudioAlsa::setAlsaMasterMute(bool mute)
{
    snd_mixer_t *mixer;
    snd_mixer_selem_id_t *element_id;
    const char *card = "default";
    const char *selem_name = "Master";

    if (snd_mixer_open(&mixer, 0) != 0) {
        return -1;
    }

    snd_mixer_attach(mixer, card);
    snd_mixer_selem_register(mixer, NULL, NULL);
    snd_mixer_load(mixer);

    snd_mixer_selem_id_alloca(&element_id);
    snd_mixer_selem_id_set_index(element_id, 0);
    snd_mixer_selem_id_set_name(element_id, selem_name);
    snd_mixer_elem_t* element = snd_mixer_find_selem(mixer, element_id);

    if (element == NULL) {
        return -2;
    }

    if (snd_mixer_selem_has_playback_switch(element)) {
        snd_mixer_selem_set_playback_switch_all(element, mute ? 0 : 1);
    }

    snd_mixer_close(mixer);

    return 0;
}

int AudioAlsa::setMasterVolumeLevel(int volume)
{
    const char *hctl = "default";
    const char *selem_name = "Master";

    snd_mixer_t *mixer;
    snd_mixer_selem_id_t *element_id;

    if (snd_mixer_open(&mixer, 0) != 0) {
        return -1;
    }

    snd_mixer_attach(mixer, hctl);
    snd_mixer_selem_register(mixer, NULL, NULL);
    snd_mixer_load(mixer);

    snd_mixer_selem_id_alloca(&element_id);
    snd_mixer_selem_id_set_index(element_id, 0);
    snd_mixer_selem_id_set_name(element_id, selem_name);
    snd_mixer_elem_t* element = snd_mixer_find_selem(mixer, element_id);

    if (element == NULL) {
        return -2;
    }

    long min, max;

    snd_mixer_selem_get_capture_volume_range(element, &min, &max);
    snd_mixer_selem_set_capture_volume_all(element, volume * max / 100);

    snd_mixer_close(mixer);

    return 0;
}

int AudioAlsa::setAlsaMicrophoneMute(bool mute)
{
    snd_mixer_t *mixer;
    snd_mixer_selem_id_t *element_id;
    const char *hctl = "default";
    const char *selem_name = "Capture";

    if (snd_mixer_open(&mixer, 0) != 0) {
        return -1;
    }

    snd_mixer_attach(mixer, hctl);
    snd_mixer_selem_register(mixer, NULL, NULL);
    snd_mixer_load(mixer);

    snd_mixer_selem_id_alloca(&element_id);
    snd_mixer_selem_id_set_index(element_id, 0);
    snd_mixer_selem_id_set_name(element_id, selem_name);
    snd_mixer_elem_t* element = snd_mixer_find_selem(mixer, element_id);

    if (element == NULL) {
        return -2;
    }

    if (snd_mixer_selem_has_playback_switch(element)) {
        snd_mixer_selem_set_playback_switch_all(element, mute ? 0 : 1);
    }

    snd_mixer_close(mixer);

    return 0;
}

int AudioAlsa::setMicrophoneVolumeLevel(int volume)
{
    const char *hctl = "default";
    const char *selem_name = "Capture";

    snd_mixer_t *mixer;
    snd_mixer_selem_id_t *element_id;

    if (snd_mixer_open(&mixer, 0) != 0) {
        return -1;
    }

    snd_mixer_attach(mixer, hctl);
    snd_mixer_selem_register(mixer, NULL, NULL);
    snd_mixer_load(mixer);

    snd_mixer_selem_id_alloca(&element_id);
    snd_mixer_selem_id_set_index(element_id, 0);
    snd_mixer_selem_id_set_name(element_id, selem_name);
    snd_mixer_elem_t* element = snd_mixer_find_selem(mixer, element_id);

    if (element == NULL) {
        return -2;
    }

    long min, max;

    snd_mixer_selem_get_capture_volume_range(element, &min, &max);
    snd_mixer_selem_set_capture_volume_all(element, volume * max / 100);

    snd_mixer_close(mixer);

    return 0;
}

int main(int argc, char *argv[])
{
    AudioAlsa::setAlsaMasterMute(false);

    AudioAlsa::setMicrophoneVolumeLevel(100);

    AudioAlsa::setMasterVolumeLevel(80);

    AudioAlsa::setAlsaMicrophoneMute(true);

    return 0;
}