// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// ?Rva0037BD2BGet@@YG_NPAX@Z @0x0037BD2B 29B. Wide +8-or-default to ArchiveFileSystem slot-11 check.
// Evidence: retail mov [esp+4]/[eax] test je load VA 0x00BBB5C4 else +8 push to rowed 0x006006A9; caller 0x0037C5B7; neighbour InGameUICreateReplayControl.
#include "unicode_string.h"

typedef unsigned short WideChar;

extern const WideChar TheNullChr[];

bool __stdcall Rva006006A9Get(const char *a1);

bool __stdcall Rva0037BD2BGet(void *holder)
{
	void *m = *(void * *)holder;
	const void *p = m ? (const void *)((char *)m + 8) : (const void *)TheNullChr;
	return Rva006006A9Get((const char *)p);
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?TheNullChr@@3QBGB=?g_Va007BB5C4@@3GA")
