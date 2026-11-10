// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
// Retail 0x005634F7 (RVA 0x005634F7) size 202: particle renderobject draw ctor.
// Evidence: pinned ParticleModule005F2CA0 base 0x0055C86D then vtable 0xC1D4F4 plus 0x00C1C780 at +0x14 plus RenderObjectDrawModuleInfo at +0x18 with vtable 0xC1D4E4 then bytes dwords strings from info plus 8 at +0x58.
#include "ascii_string.h"

extern "C" const void *const __identifier("??_7Rva003AE6A9@@6BModuleInfoHeadBase_3AE6A9@@@")[];
extern "C" const void *const __identifier("??_7Rva003AE6A9@@6B@")[];
extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");

class ParticleModule005F2CA0
{
public:
	ParticleModule005F2CA0(void *a, void *b);
	virtual ~ParticleModule005F2CA0();

private:
	char m_base[0x10];
};

#include "../../../../Include/GameClient/RenderObjectDrawModuleInfo.h"
namespace FXParticleSystem
{

class RenderObjectDrawModuleInfoBase
{
};


}

struct DrawInfo2
{
	char m_pad[0xc];
	unsigned char m_0c;
	char m_pad0d[3];
	int m_10;
	unsigned char m_14;
	char m_pad15[3];
	AsciiString m_18;
	int m_1c;
	int m_20;
	int m_24;
	AsciiString m_28;
	int m_2c;
	int m_30;
	int m_34;
	AsciiString m_38;
	int m_3c;
	int m_40;
	int m_44;
};

class __declspec(novtable) Rva005634F7 : public ParticleModule005F2CA0
{
public:
	Rva005634F7(void *a, DrawInfo2 *b);

private:
	void *m_14;
	FXParticleSystem::RenderObjectDrawModuleInfo m_18;
	int m_58;
};

Rva005634F7::Rva005634F7(void *a, DrawInfo2 *drawInfo2)
	: ParticleModule005F2CA0(a, drawInfo2)
	, m_18()
{
	*(const void **)this = __identifier("??_7Rva003AE6A9@@6BModuleInfoHeadBase_3AE6A9@@@");
	m_14 = (void *)&__identifier("??_7Rva003F498ACallback@@6B@");
	*(const void **)((char *)this + 0x18) = __identifier("??_7Rva003AE6A9@@6B@");
	*(unsigned char *)((char *)this + 0x24) = drawInfo2->m_14;
	((StringBase<char> *)((char *)this + 0x28))->set(*(const StringBase<char> *)&drawInfo2->m_18);
	*(int *)((char *)this + 0x2c) = drawInfo2->m_1c;
	*(int *)((char *)this + 0x30) = drawInfo2->m_20;
	*(int *)((char *)this + 0x34) = drawInfo2->m_24;
	((StringBase<char> *)((char *)this + 0x38))->set(*(const StringBase<char> *)&drawInfo2->m_28);
	*(int *)((char *)this + 0x3c) = drawInfo2->m_2c;
	*(int *)((char *)this + 0x40) = drawInfo2->m_30;
	*(int *)((char *)this + 0x44) = drawInfo2->m_34;
	((StringBase<char> *)((char *)this + 0x48))->set(*(const StringBase<char> *)&drawInfo2->m_38);
	*(int *)((char *)this + 0x4c) = drawInfo2->m_3c;
	*(int *)((char *)this + 0x50) = drawInfo2->m_40;
	*(int *)((char *)this + 0x54) = drawInfo2->m_44;
	*(unsigned char *)((char *)this + 0x1c) = drawInfo2->m_0c;
	*(int *)((char *)this + 0x20) = drawInfo2->m_10;
	m_58 = 8;
}
