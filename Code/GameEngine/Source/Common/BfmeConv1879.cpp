// cl: /O1
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv1879.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1).
// ??0BfmeDerivedZL@@QAE@PAV0@@Z @0x003ADC75 82B
// Copy ctor of Rva0055B52E: calls base copy ctors Rva0055BCD2 at 0x003ADDCD and
// Rva0055B32B at 0x003ADCC7, installs vtable g_00C1D11C, 0x00C1C780, and "HZz",
// then copies trailing fields.

extern const void *const g_00C1D11C[];
extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");

class Rva0055BCD2
{
public:
	Rva0055BCD2(const Rva0055BCD2 &other);

	void *m_bfmeVft0ZL;
	unsigned char m_bfmePad0ZL[4];
	void *m_bfmeVft1ZL;
};

class Rva0055B32B
{
public:
	Rva0055B32B(const Rva0055B32B &other);

	void *m_bfmeVft2ZL;
	unsigned char m_bfmePad1ZL[0x40];
};

class BfmeDerivedZL : public Rva0055BCD2, public Rva0055B32B
{
public:
	BfmeDerivedZL(BfmeDerivedZL *other);

	int m_bfmeAZL;
	int m_bfmeBZL;
	int m_bfmeCZL;
};

BfmeDerivedZL::BfmeDerivedZL(BfmeDerivedZL *other)
	: Rva0055BCD2(*other), Rva0055B32B(*static_cast<Rva0055B32B *>(other))
{
	*(const void **)this = g_00C1D11C;
	*(void **)((char *)this + 8) = (void *)&__identifier("??_7Rva003F498ACallback@@6B@");
	*(const void **)((char *)this + 12) = (const void *)"HZz";

	m_bfmeAZL = other->m_bfmeAZL;
	m_bfmeBZL = other->m_bfmeBZL;
	m_bfmeCZL = other->m_bfmeCZL;
}
