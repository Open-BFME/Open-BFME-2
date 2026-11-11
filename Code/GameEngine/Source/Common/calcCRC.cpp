// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?calcCRC@@YAIVAsciiString@@0@Z retail 0x0030050E 286B
// File CRC: copy second arg string via _mbscpy using empty global fallback, strip 4-char extension, set local path, open via TheFileSystem, loop read plus ComputeCRC; first arg unused but destroyed; callers 0x00304FDD.
#include <string.h>
#include "ascii_string.h"
class File;
#include "../../Include/Common/FileSystem.h"
#include "../../Include/Common/File.h"
extern FileSystem *TheFileSystem;
unsigned int __cdecl ComputeCRC(const unsigned char *data, unsigned int len, unsigned int crc);
// Retail calls the game's _mbscpy import thunk through REL32, so read
// <mbstring.h> without dllimport.
#define _CRTIMP
#include <mbstring.h>
#undef _CRTIMP
unsigned int __cdecl calcCRC(AsciiString a, AsciiString fileName)
{
	char buf1[260];
	char buf2[260];
	char filebuf[4096];
	AsciiString path;
	char *t = *(char * const *)&fileName;
	const char *s = t ? t + 8 : "";
	_mbscpy((unsigned char *)buf1, (const unsigned char *)s);
	unsigned int len = strlen(buf1);
	if ((int)len >= 4) {
		memset(buf2, 0, 260);
		strncpy(buf2, buf1, len - 4);
	}
	((StringBase<char> *)&path)->set(*(const StringBase<char> *)&fileName);
	char *pt = *(char * const *)&path;
	const char *ps = pt ? pt + 8 : "";
	unsigned int crc = 0;
	File *file = TheFileSystem->openFile(ps, 1, 0);
	if (file) {
		int m_BytesRead;
		while ((m_BytesRead = file->read(filebuf, 4096)) > 0)
			crc = ComputeCRC((const unsigned char *)filebuf, (unsigned int)m_BytesRead, crc);
		file->close();
	}
	return crc;
}
