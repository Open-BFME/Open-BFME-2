// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva0030062CGet@@YAPAVAsciiString@@XZ, retail 0x0030062C, 76 bytes.
// Function-local static AsciiString "LivingWorldScripts" with guard plus
// _atexit dtor registration; returns its address. Evidence: EH_prolog with
// funclet; guard byte at VA 0x009FF158 with object at VA 0x009FF154; ctor row
// ??0?$StringBase@D@@AAE@PBD@Z; _atexit row; three callers need its address;
// ret with caller cleanup.
#include "ascii_string.h"


AsciiString *__cdecl Rva0030062CGet(void)
{
	static AsciiString s("LivingWorldScripts");
	return &s;
}
