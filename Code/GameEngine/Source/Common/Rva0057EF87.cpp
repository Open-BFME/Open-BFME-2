// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0057EF87@Rva0057EE5C@@QAEXXZ @0x0057EF87 123B
// Shutdown of the AptMpGameSetup +0xD0 member: refresh via pinned 0x0057EF18,
// clear +0x58 target +8, resize Drawable vector +0x7C to 10, rowed clear
// 0x0052493F, close AptMpGameRules::InitGadgets screen, erase voidptr vectors
// +0x64/+0x70. Evidence: pin name, caller 0x0043DE41 in AptMpGameSetup::InitGadgets,
// prev/next Rva0057EE5C.cpp // cl: /O1 /DNDEBUG /MD /GX, all callees rowed/pinned.
#include "ascii_string.h"

#include "../GameClient/GUI/GUICallbacks/Apt/AptMpGameRulesView.h"

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
};

class AptMpGameRules
{
public:
	void rva0057EF18();
};

class Rva0052493F
{
public:
	void rva0052493F();
};

void _bfme_closeAptScreen(const AsciiString &name);

class Rva0057EE5C : public Rva005248D0
{
public:
	virtual void vslot1(int a, int b);
	void rva0057EA0F();
	void rva0057EF87();
private:
	char m_pad04[0x58 - 4];
	Rva0043DA65 *m_holder; // +0x58: refcounted referent
	int m_5C;
	int m_60;
	_STL::vector<void *> m_64; // +0x64
	_STL::vector<void *> m_70; // +0x70
	_STL::vector<Drawable *> m_7C; // +0x7C
	char m_pad88[0x8C - 0x88];
	int m_8C[10];
};

void Rva0057EE5C::rva0057EF87()
{
	((AptMpGameRules *)this)->rva0057EF18();
	m_holder->m_08 = 0;
	m_7C.resize(10, (Drawable *)0);
	((Rva0052493F *)this)->rva0052493F();
	_bfme_closeAptScreen(AsciiString("AptMpGameRules::InitGadgets"));
	_STL::vector<void *> &v64 = m_64;
	v64.erase(v64.begin(), v64.end());
	_STL::vector<void *> &v70 = m_70;
	v70.erase(v70.begin(), v70.end());
}
