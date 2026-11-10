// cl: /DNDEBUG /MD /EHs
// ??0Rva0055F218@@QAE@IAAUSrc0055F218@@@Z, retail 0x0055F218, 120 bytes.
// UInt-plus-template ctor: forwards the dword to the rowed base
// ??0Rva0055EFE1@@QAE@I@Z at 0x0055EFE1, subobject defaults at +0xC/+0x10/+0x14/+0x15,
// final vtables +0 0x00C1D1D4 plus +8 0x00C1C780 plus +0xC 0x00C1D1E4,
// float via rowed GameClientRandomVariable::getValue 0x002341A1, flag bytes
// from +0x3C/+0x3D. Same shape as sibling 0x005646BC. Caller at 0x003ACF96.

#include "../../Include/GameClient/GameClientRandomVariable.h"

extern "C" const void *const __identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")[];
extern "C" const void *const __identifier("??_7V3Vt01111D90@@6B@")[];

class Rva0055EFE1
{
public:
	Rva0055EFE1(unsigned int a);
	// The ctor's unwind funclet 0x00799A95 destroys this base through the
	// 24-byte two-table restore at 0x003A583E (V3InlineTemplateDtor.cpp):
	// +8 null-guarded to 0x00C1C780, then +0 to 0x00C1B320.
	~Rva0055EFE1()
	{
		unsigned char *b08 = this ? (unsigned char *)this + 8 : 0;
		*(volatile unsigned int *)b08 = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
		*(volatile unsigned int *)this = ((unsigned int)__identifier("??_7V3Vt01111D90@@6B@"));
	}
private:
	void *m_v0;
	unsigned int m_arg4;
	void *m_v8;
};

extern "C" const void *const __identifier("??_7Rva003ADE58@@6BV3Vt01111D90@@@")[];
extern "C" const void *const __identifier("??_7Rva003ADE58@@6B@")[];
extern "C" const void *const __identifier("??_7Snapshot@@6B@")[];
extern "C" const void *const __identifier("??_7Rva003ADE98@@6B@")[];
extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");

struct Src0055F218
{
	char m_pad0[0x30];
	GameClientRandomVariable m_var30;
	unsigned char m_3C;
	unsigned char m_3D;
};

struct Rva0055F218Sub
{
	Rva0055F218Sub() : m_v((void *)__identifier("??_7Rva003ADE98@@6B@")), m_f(0.0f), m_b14(0), m_b15(0) {}
	// Unwind funclet 0x00799A9D destroys this subobject (at +0xC) through the
	// folded Snapshot destructor 0x0049B47C: restore the Snapshot table.
	~Rva0055F218Sub() { m_v = (void *)__identifier("??_7Snapshot@@6B@"); }
	void *m_v;
	float m_f;
	unsigned char m_b14;
	unsigned char m_b15;
};

class Rva0055F218 : public Rva0055EFE1, public Rva0055F218Sub
{
public:
	Rva0055F218(unsigned int a, struct Src0055F218 &src);
	~Rva0055F218();
};

Rva0055F218::Rva0055F218(unsigned int a, struct Src0055F218 &src)
	: Rva0055EFE1(a), Rva0055F218Sub()
{
	*(void **)this = (void *)__identifier("??_7Rva003ADE58@@6BV3Vt01111D90@@@");
	*(void **)((char *)this + 8) = (void *)&__identifier("??_7Rva003F498ACallback@@6B@");
	m_v = (void *)__identifier("??_7Rva003ADE58@@6B@");
	float v = src.m_var30.getValue();
	m_f = v;
	m_b14 = src.m_3C;
	m_b15 = src.m_3D;
}

