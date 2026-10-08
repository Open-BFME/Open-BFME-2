// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHs
//
// ??1Rva00B9AC2@@QAE@XZ, retail 0x000B9AC2, 61B, under the name its 3
// matched callers use. Target evidence: when the +0x14 pointer is set, the
// handle at its +0x28 goes to the rowed __fastcall release 0x0007DEEF; then
// the string at +0x10 is destroyed.
//
// The string belongs to a 20-byte base record, not to this class: retail's
// EH state 0 (FuncInfo 0x00D04AE4) unwinds through the funclet 0x00B61673,
// which calls the base record's own destructor 0x000B9AAA (rowed
// ??1Rva000B9AAA@@QAE@XZ, add ecx,0x10 / jmp to the string destructor) on
// `this`, while the body inlines that same destructor. The matching
// constructor 0x000B9AB2 builds the base record and nulls +0x14
// (Rva000B9AAACTor.cpp). Names are placeholders; the base keeps the name
// its rowed destructor has.
#include "ascii_string.h"

struct TargetRef00217D4C
{
	void *m_target;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);	// 0x0007DEEF

struct Rva00B9AC2Target
{
	unsigned char m_pad0[0x28];
	TargetRef00217D4C m_ref;		// +0x28
};

class Rva000B9AAA
{
public:
	~Rva000B9AAA() {}			// 0x000B9AAA out of line
private:
	unsigned char m_pad0[0x10];
	AsciiString m_x10;			// +0x10
};

class Rva00B9AC2 : public Rva000B9AAA
{
public:
	~Rva00B9AC2();
private:
	Rva00B9AC2Target *m_x14;		// +0x14
};

Rva00B9AC2::~Rva00B9AC2()
{
	if (m_x14)
		ReleaseTreeHintRef00217D4C(&m_x14->m_ref);
}
