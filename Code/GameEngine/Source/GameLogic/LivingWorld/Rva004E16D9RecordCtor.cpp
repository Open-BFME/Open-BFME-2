// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??0Rva004E16D9Record@@QAE@XZ @0x004E15FB 135B (pinned; dtor row 0x004E1682
// in Rva004E16D9RecordDtor.cpp; caller ParseForceBattle 0x004E16D9).
// Stores vtable 0x00C61A70, copies AsciiString::TheEmptyString into +0x04
// and +0x18 through the rowed StringBase copy 0x000365F0, default-constructs
// +0x08/+0x0C and releases them in the body (0x00036410), zeroes two float
// pairs at +0x10 and +0x20 with xorps/movss and two bytes at +0x1C/+0x1D.
// Retail's unwind map destroys narrow strings at +4, +8, +0xC and +0x18.
// The +0x20 floats are a second pair member like +0x10: as two loose floats
// the byte stores scheduled after the state-3 store (the banked 0.95 attempt).
#include "ascii_string.h"
struct Rva004E16D9Pair {
	float x;
	float y;
	Rva004E16D9Pair() : x(0.0f), y(0.0f) {}
};
class Rva004E16D9Record {
public:
	virtual void anchor();
	Rva004E16D9Record();
	~Rva004E16D9Record();
private:
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0C;
	Rva004E16D9Pair m_10;
	AsciiString m_18;
	unsigned char m_1C;
	unsigned char m_1D;
	char m_pad1E[2];
	Rva004E16D9Pair m_20;
};
Rva004E16D9Record::Rva004E16D9Record() : m_04(AsciiString::TheEmptyString), m_10(), m_18(AsciiString::TheEmptyString), m_1C(0), m_1D(0), m_20()
{
	m_08.clear();
	m_0C.clear();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?anchor@Rva004E16D9Record@@UAEXXZ=??_GRva004E16D9Record@@UAEPAXI@Z")
