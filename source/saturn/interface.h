#ifndef VG_SATURN_INTERFACE_H
#define VG_SATURN_INTERFACE_H

#define SINGLE 0
#define MULTIPLE 1

extern bool STREAM_MUSIC;

void INIT_SOLOUD();

typedef int SoundEffectType;

class SwitchSoundEffect {
public:
    SwitchSoundEffect(int null_value = 0);
    SwitchSoundEffect *operator->();
    bool operator==(const SwitchSoundEffect &other) const;
    bool operator!=(const SwitchSoundEffect &other) const;
    void setVolume(float vol);
    void setPan(float p);
    void setRepeat(bool rep);
    bool isPlaying();
    void play();
    void stop();
    void reset() {}
};

typedef SwitchSoundEffect SoundEffectPtr;

SoundEffectPtr OpenSoundEffect(int device, const char *fname, SoundEffectType type);

class SwitchOutputStream {
public:
    SwitchOutputStream(int null_value = 0);
    SwitchOutputStream *operator->();
    bool operator==(const SwitchOutputStream &other) const;
    bool operator!=(const SwitchOutputStream &other) const;
    void setVolume(float vol);
    void setRepeat(bool rep);
    void play();
    void stop();
    void reset() {}
    bool isPlaying() { return false; }
    int getLength() { return 0; }
};

typedef SwitchOutputStream OutputStreamPtr;

OutputStreamPtr OpenSound(int device, const char *name, bool streaming = false);

#endif
