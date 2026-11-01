// cl: /DNDEBUG /MD /EHs-c- /Oy-
//
// _purecall, retail 0x0003B810 (62 bytes): Zero Hour's debug_purecall.cpp,
// the debug library's replacement for MSVCRT's _purecall. Its body is
// DCRASH_RELEASE("Pure virtual function called."); return 0; and BFME's
// release form of that macro is the out-of-line call-site recorder
// (0x00038790, kind 1) followed by SkipNext (slot 0x60), CrashBegin(0, 0, 0)
// (0x6C), the const char * stream operator (0x38) and CrashDone(1) (0x4C),
// each a virtual through theDebug (0x00DE0880). Retail does not import
// _purecall from MSVCR71; 2,396 .rdata vtable slots point here instead.

#include "../../../GameEngine/Source/Common/debug.h"

extern Debug *theDebug;
void _bfme_debugRecordCallsite(int kind);

// Pure virtual function called
extern "C" int __cdecl _purecall(void)
{
	_bfme_debugRecordCallsite(1);
	theDebug->SkipNext();
	(theDebug->CrashBegin(0, 0, 0) << "Pure virtual function called.").CrashDone(1);
	return 0;
}
