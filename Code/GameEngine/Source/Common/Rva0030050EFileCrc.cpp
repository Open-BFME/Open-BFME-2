// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?Rva0030050EGet@@YAIVAsciiString@@0@Z retail 0x0030050E 286B
// File CRC: copy second arg string via _mbscpy using empty global fallback, strip 4-char extension, set local path, open via TheFileSystem, loop read plus BFMEComputeCRC; first arg unused but destroyed; callers 0x00304FDD.
#include "ascii_string.h"
class File;
class FileSystem
{
public:
	File *openFile(const char *path, int a, int b);
};
class File
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void closeFile();
	virtual int readFile(void *buf, int len);
};
extern FileSystem *TheFileSystem;
extern const char g_Rva0107301CEmptyString[];
unsigned int __cdecl BFMEComputeCRC(const unsigned char *data, unsigned int len, unsigned int crc);
extern "C" char *__cdecl _mbscpy(char *dst, const char *src);
extern "C" unsigned int __cdecl strlen(const char *s);
extern "C" void *__cdecl memset(void *dst, int c, unsigned int n);
extern "C" __declspec(dllimport) char *__cdecl strncpy(char *dst, const char *src, unsigned int n);
unsigned int __cdecl Rva0030050EGet(AsciiString a, AsciiString b)
{
	char buf1[260];
	char buf2[260];
	char filebuf[4096];
	AsciiString path;
	char *t = *(char * const *)&b;
	const char *s = t ? t + 8 : g_Rva0107301CEmptyString;
	_mbscpy(buf1, s);
	unsigned int len = strlen(buf1);
	if ((int)len >= 4) {
		memset(buf2, 0, 260);
		strncpy(buf2, buf1, len - 4);
	}
	((StringBase<char> *)&path)->set(*(const StringBase<char> *)&b);
	char *pt = *(char * const *)&path;
	const char *ps = pt ? pt + 8 : g_Rva0107301CEmptyString;
	unsigned int crc = 0;
	File *f = TheFileSystem->openFile(ps, 1, 0);
	if (f) {
		int n;
		while ((n = f->readFile(filebuf, 4096)) > 0)
			crc = BFMEComputeCRC((const unsigned char *)filebuf, (unsigned int)n, crc);
		f->closeFile();
	}
	return crc;
}
