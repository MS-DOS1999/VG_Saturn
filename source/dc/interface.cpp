#include "Interface.h"
#include <ctype.h>
#include <stdio.h>
#include <kos.h>
#include <dc/sound/sound.h>
extern "C" {
#include "libadx.h"
#include "snddrv.h"
}
SwitchOutputStream		gNullStream;
SwitchSoundEffect		gNullEffect;
int inc_load = 1;
int actually_playing = -666;

bool isMountedMusicRomDisk = false;

//SoLoud::Soloud soloud;

void INIT_SOLOUD()
{
	snd_init();
}

SwitchSoundEffect::SwitchSoundEffect(void)

{

	chn = -1;
	volume = 1.0f;
	repeat = false;
	name[0] = 0;
	isnd = SFXHND_INVALID;

	return;
}

//------------------------------------------------------------------------------
// 2018.10.22.
//------------------------------------------------------------------------------

void	 SwitchSoundEffect::setVolume(float vol)

{
	volume = vol;

	if (repeat) {
		if (chn >= 0) {
			//isnd->setVolume(volume);
			//ISoundUpdate(chn, volume, 1.0f, NULL, pan);
		}
	}

	return;
};

//------------------------------------------------------------------------------
// 2018.10.22. 2019.01.16.
//------------------------------------------------------------------------------

void	 SwitchSoundEffect::setPan(float p)
{
	pan = p;

	return;
};

//------------------------------------------------------------------------------
// 2019.01.16.
//------------------------------------------------------------------------------

void	 SwitchSoundEffect::setRepeat(bool rep)
{

	repeat = rep;

	return;
};

//------------------------------------------------------------------------------
// 2019.01.16.
//------------------------------------------------------------------------------

bool	 SwitchSoundEffect::isPlaying()

{
	//Not Used

	/*if (repeat) {
		if (chn >= 0)
			return (true);
		return (false);
	}

	return (ISoundIsPlaying(isnd));*/
	return false;
}

//------------------------------------------------------------------------------
// 2018.10.22. 2018.10.23. 2018.12.18. 2019.01.16.
//------------------------------------------------------------------------------

void	 SwitchSoundEffect::play(void)

{

	if (isnd != SFXHND_INVALID) {
		if (repeat) {
			//chn = ISoundStart(isnd, volume, 1.0f, NULL, pan);
			//isnd->setVolume(volume);
			//soloud.play(*isnd);
			float volumeConv = volume*250.0;

    		snd_sfx_play(isnd, (int)volumeConv, 128);
			chn = 1;
		}
		else {
			chn = -1;
			if (type == SINGLE)
			{
				//isnd->setVolume(volume);
				//soloud.play(*isnd);
				//ISoundPlaySingle(isnd, volume, 1.0f, NULL, pan);
				float volumeConv = volume*250.0;

    			snd_sfx_play(isnd, (int)volumeConv, 128);
			}
			else
			{
				//isnd->setVolume(volume);
				//soloud.play(*isnd);
				//ISoundPlay(isnd, volume, 1.0f, NULL, pan);
				float volumeConv = volume*250.0;

    			snd_sfx_play(isnd, (int)volumeConv, 128);
			}
				
		}
	}


	return;
}

//------------------------------------------------------------------------------
// 2019.01.16.
//------------------------------------------------------------------------------

void	 SwitchSoundEffect::stop(void)

{
	if (repeat) {
		if (chn >= 0) {
			//ISoundStop(chn);
			//isnd->stop();
			if(isnd == SFXHND_INVALID)
		    {
		        return;
		    }
		    snd_sfx_stop(isnd);
			chn = -1;
		}
	}

	return;
}

//------------------------------------------------------------------------------
// 2018.10.22. 2018.12.18.
//------------------------------------------------------------------------------

SoundEffectPtr OpenSoundEffect(int device, const char *fname, SoundEffectType type)

{
	SoundEffectPtr eff = new SwitchSoundEffect;
	//eff->isnd = new SoLoud::Wav;
	char compName[200];
	sprintf(compName, "cd/%s", fname);
	for (int i = 0; compName[i]; i++) {
		compName[i] = tolower(compName[i]);
	}

	uint32  spumem = snd_mem_available();
    printf("SPU MEM AVAILABLE %d\n", spumem);
	printf("Load sfx %s\n", compName);
	eff->isnd = snd_sfx_load(compName);

	if(eff->isnd == SFXHND_INVALID)
    {
        printf("Error during loading %s\n", compName);
        //while(1);
    }


	//CPathGetName((char *)fname, eff->name, 31);
	//CStrLwr(eff->name);

	//eff->isnd = (ISound *)IPackFind(ID_SOUND, eff->name);

	return (eff);
}

//------------------------------------------------------------------------------
// 2018.10.22.
//------------------------------------------------------------------------------


SwitchOutputStream::SwitchOutputStream(void)

{
	chn = -1;
	volume = 1.0f;
	repeat = false;
	name[0] = 0;
	isnd = 0;

	return;
};

//------------------------------------------------------------------------------
// 2018.10.22. 2019.01.16.
//------------------------------------------------------------------------------

void	 SwitchOutputStream::setVolume(float vol)

{
	if(isnd == -1)
		return;
	volume = vol;

	if(this->isnd != actually_playing)
		return;

	int newvol = (int)(volume*250.0);
    if(newvol > 250)
    {
        newvol = 250;
    }
    else if(newvol < 0)
    {
        newvol = 0;
    }

    if(chn != -1)
    {	//printf("%s Enter Set Vol :", this->name);
  		if(snddrv.drv_status == SNDDRV_STATUS_STREAMING)
  		{
 			//printf(" %d\n", newvol);
    		snddrv_volume_set(newvol);
  		}
    }

	return;
};

//------------------------------------------------------------------------------
// 2018.10.22.
//------------------------------------------------------------------------------

void	 SwitchOutputStream::setRepeat(bool rep)

{
	if(isnd == -1)
		return;
	repeat = rep;

	return;
};

//------------------------------------------------------------------------------
// 2018.10.22.
//------------------------------------------------------------------------------

bool mount_romdisk(char *filename, char *mountpoint)
{
	void *buffer;
	ssize_t size = fs_load(filename, &buffer);

	printf("Load %s %d\n", filename, size);

	if (size != 1)
	{
		fs_romdisk_mount(mountpoint, (uint8*)buffer, 1);
		
		printf("Load Inside %s %d\n", mountpoint, size);
		return true;

	} else return false;
}

#include "ram_tracking.h"
void	 SwitchOutputStream::play(void)

{

	char		fname[256];

	//if (playing)
		//return;
	if (chn != -1)
		return;

	if(isnd == -1)
		return;

	
	adx_stop();
	fs_romdisk_unmount("/rd");

	print_ram_stats();
	mount_romdisk(this->name_img, "/rd");

	
		
		int newvol = (int)(volume*250.0);
	    if(newvol > 250)
	    {
	        newvol = 250;
	    }
	    else if(newvol < 0)
	    {
	        newvol = 0;
	    }

	    adx_dec(this->name, repeat ? 1 : 0);
	    while( snddrv.drv_status != SNDDRV_STATUS_STREAMING)
        	thd_pass(); 
	    snddrv_volume_set(newvol);
	    actually_playing = this->isnd;
	    //printf("Start Stream with volume %d actually %d\n", newvol, actually_playing);

	    chn = 0;

	return;
};

//------------------------------------------------------------------------------
// 2018.10.22.
//------------------------------------------------------------------------------

void	 SwitchOutputStream::stop(void)

{
	if(isnd == -1)
		return;
	if (chn != -1) {


		//isnd->stop();
		//ISoundStreamStop();
		//printf("Stop this->isnd = %d actually = %d\n", this->isnd == actually_playing);
		if(snddrv.drv_status == SNDDRV_STATUS_STREAMING && this->isnd == actually_playing)
			adx_stop();
		

		chn = -1;
	}

	return;
};

//------------------------------------------------------------------------------
// 2018.10.21. 2018.10.22.
//------------------------------------------------------------------------------
void rename_adx_img(char *filename, int size) {
    for(int i=0; i< size; i++)
    {
    	if(filename[i] == 'r' && filename[i+1] == 'd' && filename[i+2] == '/')
    	{
    		filename[i] = 'c';
    		filename[i+1] = 'd';
    		
    	}
    	if(filename[i] == '.' && filename[i+1] == 'a' && filename[i+2] == 'd' && filename[i+3] == 'x')
    	{
    		filename[i+1] = 'i';
    		filename[i+2] = 'm';
    		filename[i+3] = 'g';
    	}
    }
}

OutputStreamPtr OpenSound(int device, const char *name, bool streaming)

{

	OutputStreamPtr stream = new SwitchOutputStream;

	//CPathGetName((char *)name, stream->name, 31);
	//CStrLwr(stream->name);

	//stream->isnd = new SoLoud::Wav;

	char compName[200];
	char imgName[200];
	sprintf(compName, "rd/%s", name);
	for (int i = 0; compName[i]; i++) {
		compName[i] = tolower(compName[i]);
	}

	if(strstr(compName, "blank."))
	{
		stream->isnd = -1;
		strcpy(stream->name, "error");
		strcpy(stream->name_img, "error");
		return (stream);
	}
	else if(strstr(compName, "vg_amb_car1."))
	{
		stream->isnd = -1;
		strcpy(stream->name, "error");
		strcpy(stream->name_img, "error");
		return (stream);
	}
	else if(strstr(compName, "vg_amb_car2."))
	{
		stream->isnd = -1;
		strcpy(stream->name, "error");
		strcpy(stream->name_img, "error");
		return (stream);
	}
	else if(strstr(compName, "vg_amb_duel."))
	{
		stream->isnd = -1;
		strcpy(stream->name, "error");
		strcpy(stream->name_img, "error");
		return (stream);
	}
	else if(strstr(compName, "vg_amb_prison."))
	{
		stream->isnd = -1;
		strcpy(stream->name, "error");
		strcpy(stream->name_img, "error");
		return (stream);
	}
	else if(strstr(compName, "vg_amb_subway."))
	{
		stream->isnd = -1;
		strcpy(stream->name, "error");
		strcpy(stream->name_img, "error");
		return (stream);
	}
	else if(strstr(compName, "vg_amb_traffic."))
	{
		stream->isnd = -1;
		strcpy(stream->name, "error");
		strcpy(stream->name_img, "error");
		return (stream);
	}


	strcpy(imgName, compName);
	rename_adx_img(imgName, 200);

	stream->isnd = inc_load;
	strcpy(stream->name, compName);
	strcpy(stream->name_img, imgName);
	inc_load++;

	//printf("open music %s\n", compName);
	//stream->isnd->load(compName);

	return (stream);

}
