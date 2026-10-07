// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
// Address-named bool wrapper at 0x003006C4, 29 bytes. The packet's int pin
// conflicts with the bool return of the called helper; owner identity is unproven.
#include "ascii_string.h"

extern bool __stdcall Rva00600695Get(const char *);

class Rva003006C4
{
public:
	bool rva003006C4(const AsciiString &);
};

bool Rva003006C4::rva003006C4(const AsciiString &value)
{
	return Rva00600695Get(value.str());
}
