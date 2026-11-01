// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?invoke@Rva00222A8BTarget@@QAEHPAXPBDH10000@Z, retail 0x00222A8B (142B,
// thiscall, ret 0x20; this is unused). Calls an ActionScript function on an
// APT movie level: for a level below 14, build "/_level%d" and hand the
// function name, a static result buffer, that path, the argument count and up
// to four argument strings to the APT string call 0x006CCB80 (Apt.cpp, cdecl);
// return the buffer, which is empty for an out-of-range level. The callers
// (UiCallbackFirers.cpp and others) pass the level through a void* owner
// global and spell the method with a void return; that spelling is bound to
// this body below. Names stay address-derived.

#include "ascii_string.h"

void Rva006CCB80CallFunction(const char *function, char *result, const char *target,
	int nNumParams, ...);

#include "../../Include/Common/Rva00222A8BTarget.h"

#pragma comment(linker, "/alternatename:?invoke@Rva00222A8BTarget@@QAEXPAXPBDH10000@Z=?invoke@Rva00222A8BTarget@@QAEHPAXPBDH10000@Z")

int Rva00222A8BTarget::invoke(void *level, const char *function, int argc, const char *a0,
	void *a1, void *a2, void *a3, void *a4)
{
	static char s_result[256];
	s_result[0] = 0;
	if ((unsigned int)level >= 14)
		return (int)s_result;

	AsciiString path;
	path.format("/_level%d", level);
	Rva006CCB80CallFunction(function, s_result, path.str(), argc, a0, a1, a2, a3, a4);
	return (int)s_result;
}
