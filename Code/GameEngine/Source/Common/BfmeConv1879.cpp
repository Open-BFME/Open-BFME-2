// cl: /O1
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv1879.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1).
// ??0BfmeDerivedZL@@QAE@PAV0@@Z @0x003ADC75 82B
// Copy ctor of Rva0055B52E: calls base copy ctors Rva0055BCD2 at 0x003ADDCD and
// Rva0055B32B at 0x003ADCC7, installs vtables g_00C1D11C, 0x00C1C780 and 0x00C1D10C,
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

// Retail table 0x00C1D10C (4 slots), the +0x0C secondary vftable this constructor
// stores. Its first word, the -0x0C deleting adjustor 0x003A5A48, reads as the
// bytes of "HZz", so the string literal stood in for it. Own the complete
// initialized table (Rva004DF324Dtor.cpp s_10 precedent): each slot names a
// matched row at retail's slot target, taken by address and never called
// through these erased signatures.
extern "C" {
void __identifier("??_ERva003ADFB2@@WM@AEPAXI@Z")();
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?Rva003AC930Get@@YAHXZ")();
void __identifier("?xfer@Rva0055B3D9@@WM@AEXPAVXfer@@@Z")();
}
static const void *const s_vtable0C[4] = {
	(const void *)&__identifier("??_ERva003ADFB2@@WM@AEPAXI@Z"), //  0 0x003A5A48
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva003AC930Get@@YAHXZ"), //  2 0x003AC930
	(const void *)&__identifier("?xfer@Rva0055B3D9@@WM@AEXPAVXfer@@@Z")  //  3 0x003AC936
};
BfmeDerivedZL::BfmeDerivedZL(BfmeDerivedZL *other)
	: Rva0055BCD2(*other), Rva0055B32B(*static_cast<Rva0055B32B *>(other))
{
	*(const void **)this = g_00C1D11C;
	*(void **)((char *)this + 8) = (void *)&__identifier("??_7Rva003F498ACallback@@6B@");
	*(const void **)((char *)this + 12) = s_vtable0C;

	m_bfmeAZL = other->m_bfmeAZL;
	m_bfmeBZL = other->m_bfmeBZL;
	m_bfmeCZL = other->m_bfmeCZL;
}
