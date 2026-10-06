// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva0020182B@@UAE@XZ retail 0x0020182B 79B
// Compiler-generated dtor (no own vptr store): the AsciiString at +0x18
// (EH state 1), then the second base at +0x10 (null-checked this adjust) whose
// inline dtor releases its AsciiString at +4 (state 0), then the rowed first
// base dtor ??1Rva001E3624@@UAE@XZ 0x001E3624. Caller: rowed ??_G 0x0020180F
// (vtable 0x00BE3070). Names address-derived.

#include "ascii_string.h"

class Rva001E3624
{
public:
	virtual ~Rva001E3624();

private:
	unsigned char m_pad04[0x10 - 4];
};

class Rva0020182BSecond
{
public:
	int m_00;
	AsciiString m_name; // +0x04
};

class Rva0020182B : public Rva001E3624, public Rva0020182BSecond
{
public:
	Rva0020182B(int tag);

private:
	AsciiString m_text; // +0x18
};

// The implicit virtual dtor is emitted with the vtable this helper ctor needs.
// ?<Rva0020182B::Rva0020182B> absent-from-retail
Rva0020182B::Rva0020182B(int)
{
}
