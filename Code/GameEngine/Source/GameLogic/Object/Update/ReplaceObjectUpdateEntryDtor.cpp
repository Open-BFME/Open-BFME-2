// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva004B2B2F@@QAE@XZ, retail 0x004B2B2F, 53 bytes.
//
// Heap element of ReplaceObjectUpdateModuleData's +0xC8 vector (outer ctor
// 0x004B2AC4 news 0xE0 via factory 0x0024FCEA; vtable 0x00C56C78). Element
// is 0x10 bytes: filter at +0 via rowed 0x00360D26 plus AsciiString vector
// at +4 via rowed 0x0002CC70. Created by new 0x10 plus ctor 0x004B2B14 in
// 0x004B2B64 then push_back into +0xC8 via rowed 0x004DFCB0. Destroyed by
// this dtor then operator delete in the scalar-deleting 0x004B2BE4 and in
// the outer dtor 0x004B2C9A loop (pinned ??1ReplaceObjectUpdateModuleData).
// Members die reverse: +4 vector first (state 0) then +0 filter (or -1).
// True type name unproven; Rva004B2B2F claims only the address. Shape
// follows ProductionModifierEntry 53B precedent.

#include <vector>

#include "ascii_string.h"

class Rva00360D26Member
{
public:
	Rva00360D26Member();
	~Rva00360D26Member();
private:
	unsigned m_unknown;
};

class Rva004B2B2F
{
public:
	Rva004B2B2F();
	~Rva004B2B2F();
private:
	Rva00360D26Member m_filter; // +0
	_STL::vector<AsciiString> m_vec; // +4
};

Rva004B2B2F::Rva004B2B2F()
{
}

Rva004B2B2F::~Rva004B2B2F()
{
}
