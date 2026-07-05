#include "interface.h"

void INIT_SOLOUD() {}

SwitchSoundEffect::SwitchSoundEffect(int null_value) { (void)null_value; }
SwitchSoundEffect *SwitchSoundEffect::operator->() { return this; }
bool SwitchSoundEffect::operator==(const SwitchSoundEffect &other) const { (void)other; return true; }
bool SwitchSoundEffect::operator!=(const SwitchSoundEffect &other) const { (void)other; return false; }

void SwitchSoundEffect::setVolume(float vol) { (void)vol; }
void SwitchSoundEffect::setPan(float p) { (void)p; }
void SwitchSoundEffect::setRepeat(bool rep) { (void)rep; }
bool SwitchSoundEffect::isPlaying() { return false; }
void SwitchSoundEffect::play() {}
void SwitchSoundEffect::stop() {}

SoundEffectPtr OpenSoundEffect(int device, const char *fname, SoundEffectType type)
{
    (void)device;
    (void)fname;
    (void)type;
    return SoundEffectPtr();
}

SwitchOutputStream::SwitchOutputStream(int null_value) { (void)null_value; }
SwitchOutputStream *SwitchOutputStream::operator->() { return this; }
bool SwitchOutputStream::operator==(const SwitchOutputStream &other) const { (void)other; return true; }
bool SwitchOutputStream::operator!=(const SwitchOutputStream &other) const { (void)other; return false; }

void SwitchOutputStream::setVolume(float vol) { (void)vol; }
void SwitchOutputStream::setRepeat(bool rep) { (void)rep; }
void SwitchOutputStream::play() {}
void SwitchOutputStream::stop() {}

OutputStreamPtr OpenSound(int device, const char *name, bool streaming)
{
    (void)device;
    (void)name;
    (void)streaming;
    return OutputStreamPtr();
}
