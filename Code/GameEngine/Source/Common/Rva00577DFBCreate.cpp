// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ??0Rva00577DE1OwningCell@@QAE@HABVAsciiString@@@Z @0x00577DFB 67B
// Evidence: gap in FamilyDeletingDtors3.cpp between clear 0x00577DE1 and forwardClear 0x00577E3E;
// callee ctor 0x0057796E rowed. A constructor, not a method returning this:
// its one caller, StrategicHUD::HUD::Impl::OnRadialMenuStageLoaded 0x0042DD37, calls it
// on operator new(4)'s result inside the new-expression's delete-on-throw
// state, with the level int and an AsciiString temp.
#include "ascii_string.h"

class Rva0057796E
{
public:
	Rva0057796E(int a1, int a2, const AsciiString &a3);
private:
	int m_00;
	int m_04;
	AsciiString m_08;
	int m_0C;
	int m_10;
};

class Rva00577DE1OwningCell
{
public:
	Rva00577DE1OwningCell(int a1, const AsciiString &a2);
private:
	void *m_value;
};

Rva00577DE1OwningCell::Rva00577DE1OwningCell(int a1, const AsciiString &a2)
{
	m_value = new Rva0057796E((int)this, a1, a2);
}
