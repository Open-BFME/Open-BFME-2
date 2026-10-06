// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc

// ?Rva00412DD8Get@@YA?AVAsciiString@@PBD@Z, retail 0x00412DD8 158B.
// Free AsciiString(const char*) normalizer: null uses the "" literal at
// 0x00BBAC1C, skips one leading '/', strncpy 0x7fff into 32k stack buffer,
// rewrites '/' to '.', then RVO via StringBase copy 0x365F0 and temp
// teardown via releaseBuffer 0x36410. Caller at 0x0041196E passes hidden
// return plus path; PBD ctor is rowed 0x37BA0.

extern "C" __declspec(dllimport) char *__cdecl strncpy(char *dest, const char *source, unsigned int count);


#include "ascii_string.h"


AsciiString Rva00412DD8Get(const char *path)
{
	char buf[32768];
	if (path == 0)
		path = (char *)"";
	if (*path == '/')
		path++;
	strncpy(buf, path, 0x7fff);
	for (char *p = buf; *p != 0; p++) {
		if (*p == '/')
			*p = '.';
	}
	AsciiString tmp(buf);
	return tmp;
}

// ?Rva00412E76Get@@YA?AVAsciiString@@PBD@Z, retail 0x00412E76 158B.
// Sibling of Rva00412DD8Get above: same 32k buf plus strncpy 0x7fff and RVO
// via 0x365F0/0x36410/0x37BA0, but skips one leading '.' and rewrites '.'
// to '/'. Prev is 0x00412DD8 in this TU; unblocks 0x004104AB plus 4 more.

AsciiString Rva00412E76Get(const char *path)
{
	char buf[32768];
	if (path == 0)
		path = (char *)"";
	if (*path == '.')
		path++;
	strncpy(buf, path, 0x7fff);
	for (char *p = buf; *p != 0; p++) {
		if (*p == '.')
			*p = '/';
	}
	AsciiString tmp(buf);
	return tmp;
}
