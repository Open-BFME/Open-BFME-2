// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// ?rva0037BD2B@FileSystem@@QAE_NABVUnicodeString@@@Z @0x0037BD2B 29B. Wide +8-or-default to ArchiveFileSystem slot-11 check.
// FileSystem member ABI: native caller37C5A9 loads TheFileSystem E06A48
// in ECX before passing the UnicodeString address. The member does not read
// this; it forwards to the ArchiveFileSystem global dispatcher6006A9.
// This replaces the neutral free-function spelling without a second pin.
// Evidence: retail mov [esp+4]/[eax] test je load VA 0x00BBB5C4 else +8 push to rowed 0x006006A9; caller 0x0037C5B7; neighbour RecorderClass::initControls (0x0037BD81).
#include "unicode_string.h"

typedef unsigned short WideChar;


class FileSystem
{
public:
	bool rva0037BD2B(const UnicodeString &path);
	bool rva006006A9(const WideChar *path);	// 0x006006A9, same receiver
};

bool FileSystem::rva0037BD2B(const UnicodeString &path)
{
	void *m = *(void * const *)&path;
	const void *p = m ? (const void *)((char *)m + 8) : (const void *)L"";
	return rva006006A9((const WideChar *)p);
}
