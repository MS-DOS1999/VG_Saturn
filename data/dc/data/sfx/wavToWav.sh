#!/bin/bash
for f in *.wav
do
	ffmpeg -i $f -acodec pcm_s16le -ar 16000 -ac 1 -bitexact -map_metadata -1 -fflags +bitexact -flags:v +bitexact -flags:a +bitexact res/$f
	echo $f
	~/kos/utils/wav2adpcm/wav2adpcm -t res/$f res2/$f
done
