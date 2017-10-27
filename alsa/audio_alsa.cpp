#include <iostream>
#include <alsa/asoundlib.h>
#include <alsa/control.h>
#include "audio_alsa.h"

int AudioAlsa::setAlsaMasterMute(bool mute)
{
    snd_mixer_t *mixer;

    if (snd_mixer_open(&mixer, 0) != 0) {
        return -1;
    }

    const char *card = "default";
    const char *elementName = "Master";

    snd_mixer_attach(mixer, card);
    snd_mixer_selem_register(mixer, NULL, NULL);
    snd_mixer_load(mixer);

    snd_mixer_selem_id_t *elementId;

    snd_mixer_selem_id_alloca(&elementId);
    snd_mixer_selem_id_set_index(elementId, 0);
    snd_mixer_selem_id_set_name(elementId, elementName);
    snd_mixer_elem_t* element = snd_mixer_find_selem(mixer, elementId);

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
    const char *elementName = "Master";

    snd_mixer_t *mixer;
    snd_mixer_selem_id_t *elementId;

    if (snd_mixer_open(&mixer, 0) != 0) {
        std::cerr << "Cannot open mixer 0" << std::endl;
        return -1;
    }

    snd_mixer_attach(mixer, hctl);
    snd_mixer_selem_register(mixer, NULL, NULL);
    snd_mixer_load(mixer);

    snd_mixer_selem_id_alloca(&elementId);
    snd_mixer_selem_id_set_index(elementId, 0);
    snd_mixer_selem_id_set_name(elementId, elementName);

    snd_mixer_elem_t* element = snd_mixer_find_selem(mixer, elementId);

    if (element == NULL) {
        std::cerr << "Cannot find element with ID " << elementId << std::endl;
        return -2;
    }

    long min, max;

    snd_mixer_selem_get_playback_volume_range(element, &min, &max);

    std::cerr << "Maximum volume: " << min << std::endl;
    std::cerr << "Minimum volume: " << max << std::endl;

    long volumeLevel = (float) volume * (float) max / 100.0;
    
    std::cout << "New volume: " << volumeLevel << std::endl;

    snd_mixer_selem_set_playback_volume_all(element, volumeLevel);

    snd_mixer_close(mixer);

    return 0;
}

int AudioAlsa::setAlsaMicrophoneMute(bool mute)
{
    snd_mixer_t *mixer;

    if (snd_mixer_open(&mixer, 0) != 0) {
        return -1;
    }

    snd_mixer_selem_id_t *elementId;
    const char *hctl = "default";
    const char *elementName = "Capture";

    snd_mixer_attach(mixer, hctl);
    snd_mixer_selem_register(mixer, NULL, NULL);
    snd_mixer_load(mixer);

    snd_mixer_selem_id_alloca(&elementId);
    snd_mixer_selem_id_set_index(elementId, 0);
    snd_mixer_selem_id_set_name(elementId, elementName);

    snd_mixer_elem_t* element = snd_mixer_find_selem(mixer, elementId);

    if (element == NULL) {
        return -2;
    }

    if (snd_mixer_selem_has_capture_switch(element)) {
        snd_mixer_selem_set_capture_switch_all(element, mute ? 0 : 1);
    }

    snd_mixer_close(mixer);

    return 0;
}

int AudioAlsa::setMicrophoneVolumeLevel(int volume)
{
    const char *hctl = "default";
    const char *elementName = "Capture";

    snd_mixer_t *mixer;
    snd_mixer_selem_id_t *elementId;

    if (snd_mixer_open(&mixer, 0) != 0) {
        return -1;
    }

    snd_mixer_attach(mixer, hctl);
    snd_mixer_selem_register(mixer, NULL, NULL);
    snd_mixer_load(mixer);

    snd_mixer_selem_id_alloca(&elementId);
    snd_mixer_selem_id_set_index(elementId, 0);
    snd_mixer_selem_id_set_name(elementId, elementName);

    snd_mixer_elem_t* element = snd_mixer_find_selem(mixer, elementId);

    if (element == NULL) {
        return -2;
    }

    long min, max;

    snd_mixer_selem_get_capture_volume_range(element, &min, &max);

    long volumeLevel = (float) volume * (float) max / 100.0;
    
    std::cout << "New volume: " << volumeLevel << std::endl;

    snd_mixer_selem_set_capture_volume_all(element, volumeLevel);

    snd_mixer_close(mixer);

    return 0;
}