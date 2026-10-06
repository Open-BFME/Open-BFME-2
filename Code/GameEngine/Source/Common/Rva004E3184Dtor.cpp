// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /Ireference/shims/moduledata
//
// ??1Rva004E3184@@UAE@XZ @ 0x004E3184 (201B).
// ModuleData-style dtor: stores vtable 0x00861F28 at +0 then tears down
// AsciiStrings at +0x50 +0x34 +0x30 +0x2C +0x28 +0x1C +0x18 +0x14 +0x10
// +0x0C +0x08 +0x04 via pinned 0x00036410 and the vector at +0x38 via
// pinned 0x0002CC70 then restores Snapshot base vtable 0x00BBB554.
// Layout from the teardown EH states 0xC-0. Shape follows
// GateOpenAndCloseBehaviorModuleDataDtor (Snapshot base plus opaque vector
// and string members).

#include "ascii_string.h"
#include "Common/Snapshot.h"

class RvaVecAscii
{
public:
	~RvaVecAscii();

private:
	int m_x[3];
};

class Rva004E3184 : public Snapshot
{
public:
	virtual ~Rva004E3184();

private:
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0c;
	AsciiString m_10;
	AsciiString m_14;
	AsciiString m_18;
	AsciiString m_1c;
	char m_pad20[8];
	AsciiString m_28;
	AsciiString m_2c;
	AsciiString m_30;
	AsciiString m_34;
	RvaVecAscii m_vec38;
	char m_pad44[12];
	AsciiString m_50;
};

Rva004E3184::~Rva004E3184()
{
}
