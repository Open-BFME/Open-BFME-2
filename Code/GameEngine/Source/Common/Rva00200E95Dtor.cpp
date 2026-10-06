// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva00200E95@@UAE@XZ retail 0x00200E95 79B
// Compiler-generated dtor (no own vptr store): the AsciiString at +0x3C
// (EH state 1), then the second base at +0x10 (null-checked this adjust) whose
// inline dtor releases its AsciiString at +4 (state 0), then the rowed first
// base dtor ??1Rva001E3624@@UAE@XZ 0x001E3624. Caller: rowed ??_G 0x00200E79
// (vtable 0x00BE2BA4). Names address-derived.

#include "ascii_string.h"

class Rva001E3624
{
public:
	virtual ~Rva001E3624();

private:
	unsigned char m_pad04[0x10 - 4];
};

class Rva00200E95Second
{
public:
	int m_00;
	AsciiString m_name; // +0x04
};

class Rva00200E95 : public Rva001E3624, public Rva00200E95Second
{
public:
	Rva00200E95(int tag);

private:
	unsigned char m_pad18[0x3C - 0x18];
	AsciiString m_text; // +0x3C
};

// The implicit virtual dtor is emitted with the vtable this helper ctor needs.
// ?<Rva00200E95::Rva00200E95> absent-from-retail
Rva00200E95::Rva00200E95(int)
{
}
