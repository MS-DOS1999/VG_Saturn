
#include "globals.h"

static int gDialogueLengthVO = 0;
static OutputStreamPtr gDialogueSound = NULL;
 
//

// The following define enables VO dialogue samples if set to 1.
// If it is 0, the default time code is used and no samples are being loded and played.
#define DIALOGUE_SAMPLES_ACTIVE (0)

// The define below divides the sample length in frames so we get a
// millisecond value that is being used to show the dialogue.
// If we assume all samples are 44100 kHz, a value of 44 gives us
// roughly the length of the sample in milliseconds. Is the value
// smaller the dialogues will be shown a bit longer.
#define DIALOGUE_SAMPLE_FRAME_DIV (38)

//

#define PLAY_DIALOGUE( LEFT_RIGHT, TEXT, AUDIO_PATH )	\
{														\
    sprintf( counter[ LEFT_RIGHT ].word, TEXT );		\
    PlayDialogue( AUDIO_PATH );							\
} /* PLAY_DIALOGUE */

//SoundEffectPtr door_open(OpenSoundEffect(device, "data/SFX/victory.wav", SINGLE));
//OutputStreamPtr end_snd(OpenSound(device, "data/SFX/song1.ogg", STREAM_MUSIC));        // Title screen    

//////////////////
// PlayDialogue //
//////////////////

void PlayDialogue( const char * fileName )
{
    gDialogueSound    = NULL; // We need to reset this here to NULL
	gDialogueLengthVO = 0;

#if DIALOGUE_SAMPLES_ACTIVE == 0
	return;
#endif

    char strName[ 256 ];
	char strFolder[ 10 ];

	// We're using format "VO-01-02" and want "01" which are the folders for the VO's.
	// For the example above we are creating the string "01/"
	strFolder[ 0 ] = fileName[ 3 ];
	strFolder[ 1 ] = fileName[ 4 ];
	strFolder[ 2 ] = '/';
	strFolder[ 3 ] = '\0';

    strcpy( strName, "data/VO/" );
    strcat( strName, strFolder );
    strcat( strName, fileName );
    strcat( strName, ".ogg" );

//  SoundEffectPtr  dialogue( OpenSoundEffect( device, strName, SINGLE ) );
    OutputStreamPtr dialogue( OpenSound(       device, strName, false ) );

	if( dialogue == (OutputStreamPtr)NULL )
	{
#if DEMO_MODE == 0
	    char strError[ 256 ];
	    sprintf( strError, "Dialogue VO sample load error!\n\nFile: \"%s\"", strName );
	 	MessageBox( NULL, strError, "", MB_OK );
#endif // DEMO_MODE

	    return; // WE HAD AN ERROR LOADING THE VO!
	} // if //

    dialogue->setVolume( sfx_volume );
    dialogue->play();

	gDialogueLengthVO = dialogue->getLength() / DIALOGUE_SAMPLE_FRAME_DIV;

	if( gDialogueLengthVO == 0 )
	{
#if DEMO_MODE == 0
		MessageBox( NULL, "Unable to get VO dialogue length!", "", MB_OK );
#endif // DEMO_MODE
	}
	else
	{
//	 	sprintf( strName, "Dialogue length = %i", gDialogueLengthVO );
//	 	MessageBox( NULL, strName, "### Debug info ###", MB_OK );
	} // else //

	gDialogueSound = dialogue;
} // PlayDialogue //
