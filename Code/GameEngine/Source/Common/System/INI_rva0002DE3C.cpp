// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /DNDEBUG /MD /GX /Oi-
// ?rva0002DE3C@INI@@SAXPAV1@PAX1PBX@Z @0x0002DE3C 60B. Static INI parse proc
// storing block-accumulate result via rowed 0x0002D6F8 plus set plus dtor.
// Evidence: chain from just-landed 0x0002D6F8 plus same 60B temp-set-dtor
// shape as sibling INI_parseAsciiString.cpp at 0x0002F11E.
#include "ascii_string.h"
class INI
{
public:
	AsciiString rva0002D6F8();
	static void rva0002DE3C(INI *ini, void *instance, void *store, const void *userData);
};
void INI::rva0002DE3C(INI *ini, void *instance, void *store, const void *userData)
{
	*(AsciiString *)store = ini->rva0002D6F8();
}
