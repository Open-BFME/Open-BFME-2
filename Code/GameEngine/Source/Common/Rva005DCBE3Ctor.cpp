// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /MD
// ??0Rva005DCBE3@@QAE@ABVAsciiString@@H@Z @0x005DCBC7 28B
// Evidence: pin ??0Rva005DCBE3@@QAE@ABVAsciiString@@H@Z; caller 0x005AAA06 in Rva004ECECDTacticCtors.cpp; callee pin ??0Rva004ECECD@@QAE@ABVAsciiString@@H@Z; gap between rows in Rva004EDCE9Derived.cpp.
#include "ascii_string.h"

class Rva004ECECD
{
public:
	Rva004ECECD(const AsciiString &s, int n);
	virtual ~Rva004ECECD();
};

class Rva005DCBE3 : public Rva004ECECD
{
public:
	Rva005DCBE3(const AsciiString &s, int n);
	virtual ~Rva005DCBE3();
};

// ??0Rva005DCBE3@@QAE@ABVAsciiString@@H@Z
Rva005DCBE3::Rva005DCBE3(const AsciiString &s, int n) : Rva004ECECD(s, n)
{
}
