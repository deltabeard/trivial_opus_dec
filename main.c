#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "trivial_example.c"

int main(int _argc,const char **_argv)
{
#if defined(_WIN32)
	win32_utf8_setup(&_argc,&_argv);
#endif
	if(_argc != 3)
	{
		fprintf(stderr,"Usage: %s <in.opus> <out.wav>\n",_argv[0]);
		return EXIT_FAILURE;
	}

	return convOpus(_argv[1], _argv[2]);
}
