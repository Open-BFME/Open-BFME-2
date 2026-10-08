// cl: /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ob2 /EHsc /MD
// stlport
// ?rva005C802B@Rva005C802B@@QAE@HH@Z @0x005C802B 74B -> child 0x60 via 0x005C7D4A
// ?rva005D19F8@Rva005D19F8@@QAE@HH@Z @0x005D19F8 74B -> child 0x1C via 0x005D18E2
// ?rva005FF912@Rva005FF912@@QAE@HH@Z @0x005FF912 74B -> child 0x40 via 0x005FF675
// Two-arg factory constructors: install the class vtable ([this] = 0x00C74ACC
// / 0x00C75688 / 0x00C7A530, pinned ??_7 each), then m_04 = new Child(this, a,
// b) over the fixed-size POD child (0x60/0x1C/0x40 pushed literally by
// sizeof). The pinned child entries are the constructors themselves: the
// three stack pushes plus ecx=newptr are the ctor call, the EH frame with
// the [ebp-10] new-pointer slot is the scalar new-trap deleting on ctor
// throw, and the post-call mov [esi+4],eax stores the ctor's return (this).
// operator new is declared nothrow (Rva001E1890Parse.cpp precedent) so the
// compiler emits the observed null check; the reference still mangles as
// ??2@YAPAXI@Z and resolves to rowed 0x0002FDA0. Owner and child identities
// remain unproven for the first two children. Native005FF675 independently
// proves the third child is the named Impl and its last word is an AsciiString
// reference; the owner factory retains its existing neutral signature.
void *__cdecl operator new(unsigned int s) throw();

class Rva005C802B;

struct Rva005C802BChild
{
	Rva005C802BChild(Rva005C802B *o, int a, int b);
	char m_data[0x60];
};

class Rva005C802B
{
public:
	Rva005C802B(int a, int b);
	virtual ~Rva005C802B();
private:
	Rva005C802BChild *m_04;
};

Rva005C802B::Rva005C802B(int a, int b)
{
	m_04 = new Rva005C802BChild(this, a, b);
}

class Rva005D19F8;

struct Rva005D19F8Child
{
	Rva005D19F8Child(Rva005D19F8 *o, int a, int b);
	char m_data[0x1C];
};

class Rva005D19F8
{
public:
	Rva005D19F8(int a, int b);
	virtual ~Rva005D19F8();
private:
	Rva005D19F8Child *m_04;
};

Rva005D19F8::Rva005D19F8(int a, int b)
{
	m_04 = new Rva005D19F8Child(this, a, b);
}

#include "BattlePromptMovieClipView.h"

#include "BattlePromptArmyPanelClipImplView.h"

Rva005FF912::Rva005FF912(int a, int b)
{
	m_04 = new StrategicHUD::BattlePromptArmyPanelMovieClip::Impl(this, a, *(const AsciiString *)b);
}
