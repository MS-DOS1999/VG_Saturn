#define SINGLE 0
#define MULTIPLE 1

void INIT_SOLOUD();

typedef int SoundEffectType;

class SwitchSoundEffect {
public:
	int			chn;
	float		volume;
	bool		repeat;
	float		pan;
	int 		isnd;
	char		name [32];
	SoundEffectType	type;

	SwitchSoundEffect (void);

	void setVolume (float vol);
	void setPan (float p);
	void setRepeat (bool rep);
	bool isPlaying ();
	void play (void);
	void stop (void);
	void reset () {};
};

typedef SwitchSoundEffect *SoundEffectPtr;

SoundEffectPtr OpenSoundEffect (int device, const char *fname, SoundEffectType type);

class SwitchOutputStream {
public:
	int			chn;
	float		volume;
	bool		repeat;
	float		pan;
	int 		isnd;
	char		name[100];
	char		name_img[100];
	SoundEffectType	type;

	SwitchOutputStream (void);

	void setVolume (float vol);
	void setRepeat (bool rep);
	void play (void);
	void stop (void);

	void reset () {};
	bool isPlaying () { return (chn > -1 ? true : false); };
	int getLength () { return (0); };
};

typedef SwitchOutputStream *OutputStreamPtr;

OutputStreamPtr OpenSound (int device, const char *name, bool streaming = false);