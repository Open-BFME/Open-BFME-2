// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// Open-BFME5: FXParticleSystem::ParticleSystemTemplate copy ctor + virtual dtor.
//
// TARGET facts (retail game.dat, read-only pefile+capstone this round):
// - 0x001FCE6B 102B export ??0ParticleSystemTemplate@FXParticleSystem@@QAE@ABV01@@Z,
//   Ghidra agrees (102B ParticleSystemTemplate): SEH prologue, base copy call to
//   rowed 0x00002459, vtable store 0x00BE1A28, StringBase<char> copy call to
//   export 0x000365F0 with members at +0x9c, `and [esi+0xa0],0`, tail copy call
//   to 0x001FC3BF with member at +0xa4, ret 4. Zero functions.csv rows overlap.
// - 0x001FBF4D 80B export ??1ParticleSystemTemplate@FXParticleSystem@@UAE@XZ,
//   Ghidra agrees (80B ~ParticleSystemTemplate): SEH prologue, vtable store
//   0x00BE1A28, tail call to 0x001FBEB7 with ecx=[esi+0xa4], string teardown
//   call to ICF-folded 0x00036410 with ecx=[esi+0x9c], base dtor call to rowed
//   0x0000240E. Rowed vector deleting dtor 0x001FC052 (element 0xD4, vtable
//   0x00BE1A28#0) and scalar deleting dtor 0x001FC036 both call it. Zero
//   functions.csv rows at the address itself.
// DONOR facts (BFME1 6583b3c1, clean thunks, lead only):
// - ParticleSystemTemplateCopyCtorThunk.cpp (/DNDEBUG /MD /EHsc): base copy,
//   m_name(other.m_name), m_slaveTemplate(0), m_tail(other.m_tail). Base pad
//   0x94 there; BFME2 retail members sit 4 higher (+0x9c/+0xa0/+0xa4), so the
//   BFME2 base subobject is 0x9c (INFERENCE: size placeholder only).
// - FXParticleSystem_ParticleSystemTemplateDestructorThunk.cpp: base + string
//   + member teardown shape; offsets quoted +0x98/+0xa0 are DONOR facts, retail
//   proves +0x9c/+0xa4 here.
// INFERENCE (guidance only): tail type/symbol names are opaque BFME2-local
// shims sized by 0xD4-0xa4; pins map them to the retail call targets above.

#include "ascii_string.h"

class Xfer;

// Snapshot shape mirrors the rowed ParticleSystemInfo destructor TU so the
// derived vtable extends the same four-slot layout; the vtable itself is
// emitted with this TU's derived class (no other TU defines it).
// class-gate: allow Snapshot rowed-ParticleSystemInfo-TU-order-crc-loadPostProcess-xfer-matching-siblings-byte-exact
class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
	virtual void xfer(Xfer *xfer) = 0;
};

namespace FXParticleSystem
{

// Base subobject: vtable + pad = 0x9c so m_name lands at retail +0x9c.
// Copy/dtor are the rowed 0x2459/0x240E COMDATs (same decorated names).
class __declspec(novtable) ParticleSystemInfo : public Snapshot
{
public:
	ParticleSystemInfo(const ParticleSystemInfo &other);
	virtual ~ParticleSystemInfo();

private:
	unsigned char m_pad[0x98];
};

// Tail subobject at +0xa4, 0x30 bytes to the 0xD4 element size proven by the
// rowed vector deleting dtor. Out-of-line copy/dtor pinned to the retail
// call targets (see symbols.csv); no donor identity is claimed for it.
class ParticleSystemTemplateTail
{
public:
	ParticleSystemTemplateTail(const ParticleSystemTemplateTail &other);
	~ParticleSystemTemplateTail();

private:
	unsigned char m_pad[0x30];
};

class ParticleSystemTemplate : public ParticleSystemInfo
{
public:
	ParticleSystemTemplate(const ParticleSystemTemplate &other);
	virtual ~ParticleSystemTemplate();

private:
	AsciiString m_name; // +0x9c
	int m_slaveTemplate; // +0xa0
	ParticleSystemTemplateTail m_tail; // +0xa4
};

// ??0ParticleSystemTemplate@FXParticleSystem@@QAE@ABV01@@Z
ParticleSystemTemplate::ParticleSystemTemplate(const ParticleSystemTemplate &other) :
	ParticleSystemInfo(other),
	m_name(other.m_name),
	m_slaveTemplate(0),
	m_tail(other.m_tail)
{
}

// ??1ParticleSystemTemplate@FXParticleSystem@@UAE@XZ
ParticleSystemTemplate::~ParticleSystemTemplate()
{
}

}
