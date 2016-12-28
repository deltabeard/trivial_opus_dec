/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE libopusfile SOFTWARE CODEC SOURCE CODE. *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE libopusfile SOURCE CODE IS (C) COPYRIGHT 1994-2012           *
 * by the Xiph.Org Foundation and contributors http://www.xiph.org/ *
 *                                                                  *
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <opus/opusfile.h>

int main(int _argc, const char **_argv){
	OggOpusFile  *of;
	int           ret;

	if(_argc!=2){
		fprintf(stderr,"Usage: %s <file.opus>\n",_argv[0]);
		return EXIT_FAILURE;
	}

	of=op_open_file(_argv[1],&ret);
	if(of==NULL){
		fprintf(stderr,"Failed to open file '%s': %i\n",_argv[1],ret);
		return EXIT_FAILURE;
	}

	for(;;){
		opus_int16    pcm[120*48*2];

		/*Although we would generally prefer to use the float interface, WAV
		  files with signed, 16-bit little-endian samples are far more
		  universally supported, so that's what we output.*/
		ret = op_read_stereo(of, pcm, sizeof(pcm));

		if(ret<0){
			fprintf(stderr,"\nError decoding '%s': %i\n",_argv[1],ret);
			ret=EXIT_FAILURE;
			break;
		}

		if(ret<=0){
			ret=EXIT_SUCCESS;
			break;
		}

		/* times 2 for stereo I presume. */
		if(!fwrite(pcm, ret * sizeof(opus_int16) * 2, 1, stdout)){
			fprintf(stderr,"\nError writing decoded audio data: %s\n",
					strerror(errno));
			ret=EXIT_FAILURE;
			break;
		}
	}
	op_free(of);
	return ret;
}
