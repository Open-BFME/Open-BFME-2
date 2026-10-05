// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /DNDEBUG /MD /EHsc
#include "ascii_string.h"
// ??0Rva001E125D@@QAE@XZ @0x001E1221 32B: ctor of Rva001E125D.
// Evidence: stores vtable 0x007DD95C at [this], zeroes +0x148 (AsciiString m_text=0 via inline default ctor, and [mem],0 under /O1), sets +0x04=9 (base m04); calls rowed base ??0Rva001DFEAABase@@QAE@XZ 0x001DFEAA; unblocks 0x001E1890.

class Rva001DFEAABase
{
public:
	Rva001DFEAABase();
	virtual ~Rva001DFEAABase();
	int m04;
private:
	char m_pad[0x148 - 8];
};

class Rva001E125D : public Rva001DFEAABase
{
public:
	Rva001E125D();
	virtual void dummy1();
	virtual void dummy2();
	virtual void rva001E0AA5(int a1, int a2);
private:
	AsciiString m_str148;
	char m_pad14C[0x160 - 0x14C];
	char m_str160[4];
};

Rva001E125D::Rva001E125D()
{
	m04 = 9;
}
class ParticleSystemManager;
extern ParticleSystemManager *TheParticleSystemManager;
class ParticleSystemTemplate;
class ParticleSystemManager
{
public:
	ParticleSystemTemplate *rva001F9343(const AsciiString &s, int i) const;
};
void Rva001E125D::rva001E0AA5(int a1, int a2)
{
	AsciiString tmp(m_str160);
	ParticleSystemTemplate *t = TheParticleSystemManager->rva001F9343(tmp, a1);
	(void)t;
	(void)a2;
}
