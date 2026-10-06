// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc
//
// ??1Rva004E16D9Record@@QAE@XZ, retail 0x004E1682, 87 bytes.
// Target evidence: ParseForceBattle 0x004E16D9 constructs a stack record
// (ctor pin 0x004E15FB) and destroys it here. The body stores 0x00C61A70 at
// +0x00, then tears down strings at +0x18, +0x0C, +0x08, +0x04 (0x00036410).
// The +0x00 store lands ahead of the EH state, which only a compiler vptr
// restore produces, so the record is polymorphic with a non-virtual dtor
// (pin spelling QAE; size 0x28 from ParseForceBattle.cpp). Its virtual
// slots are unrecovered; anchor() is a stand-in.

#include "ascii_string.h"

class Rva004E16D9Record
{
public:
	virtual void anchor();
	~Rva004E16D9Record();

private:
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0C;
	int m_10[2];
	AsciiString m_18;
	int m_1C[3];
};

Rva004E16D9Record::~Rva004E16D9Record()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?anchor@Rva004E16D9Record@@UAEXXZ=??_GRva004E16D9Record@@UAEPAXI@Z")
