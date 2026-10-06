// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
// Retail 0x005634F7 (RVA 0x005634F7) size 202: particle renderobject draw ctor.
// Evidence: pinned ParticleModule005F2CA0 base 0x0055C86D then vtable 0xC1D4F4 plus s_slot3E4first at +0x14 plus RenderObjectDrawModuleInfo at +0x18 with vtable 0xC1D4E4 then bytes dwords strings from info plus 8 at +0x58.
#include "ascii_string.h"

extern const void *const g_00C1D4F4[];
extern const void *const g_00C1D4E4[];
extern "C" int s_slot3E4first;

class ParticleModule005F2CA0
{
public:
	ParticleModule005F2CA0(void *a, void *b);
	~ParticleModule005F2CA0();

private:
	char m_base[0x14];
};

namespace FXParticleSystem
{

class RenderObjectDrawModuleInfoBase
{
};

class RenderObjectDrawModuleInfo : public RenderObjectDrawModuleInfoBase
{
public:
	RenderObjectDrawModuleInfo();
	virtual ~RenderObjectDrawModuleInfo();

private:
	bool m_enabled;
	float m_type;
	bool m_flag;
	AsciiString m_name0;
	unsigned int m_value00;
	float m_value01;
	int m_value02;
	AsciiString m_name1;
	unsigned int m_value10;
	float m_value11;
	int m_value12;
	AsciiString m_name2;
	unsigned int m_value20;
	float m_value21;
	int m_value22;
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

Rva005634F7::Rva005634F7(void *a, DrawInfo2 *b)
	: ParticleModule005F2CA0(a, b)
	, m_18()
{
	*(const void **)this = g_00C1D4F4;
	m_14 = (void *)&s_slot3E4first;
	*(const void **)((char *)this + 0x18) = g_00C1D4E4;
	*(unsigned char *)((char *)this + 0x24) = b->m_14;
	((StringBase<char> *)((char *)this + 0x28))->set(*(const StringBase<char> *)&b->m_18);
	*(int *)((char *)this + 0x2c) = b->m_1c;
	*(int *)((char *)this + 0x30) = b->m_20;
	*(int *)((char *)this + 0x34) = b->m_24;
	((StringBase<char> *)((char *)this + 0x38))->set(*(const StringBase<char> *)&b->m_28);
	*(int *)((char *)this + 0x3c) = b->m_2c;
	*(int *)((char *)this + 0x40) = b->m_30;
	*(int *)((char *)this + 0x44) = b->m_34;
	((StringBase<char> *)((char *)this + 0x48))->set(*(const StringBase<char> *)&b->m_38);
	*(int *)((char *)this + 0x4c) = b->m_3c;
	*(int *)((char *)this + 0x50) = b->m_40;
	*(int *)((char *)this + 0x54) = b->m_44;
	*(unsigned char *)((char *)this + 0x1c) = b->m_0c;
	*(int *)((char *)this + 0x20) = b->m_10;
	m_58 = 8;
}
