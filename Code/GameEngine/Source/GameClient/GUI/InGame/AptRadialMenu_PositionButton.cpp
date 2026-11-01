// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc

#pragma comment(linker, "/alternatename:?Move@ButtonShell@Impl@AptRadialMenu@@QAEXVCoord2D@@0@Z=?Move@ButtonShell@Impl@AptRadialMenu@@QAEXHHHH@Z")

// stlport
// Split from AptRadialMenu.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// AptRadialMenu::Impl (WorldBuilder GameClient/Gui/InGame/AptRadialMenu.cpp).
// Target facts: PositionButton 0x00577E70 (ret 0xC) and EnableButtonInput
// 0x00577E94 (ret 8), slots 2 and 3 of the vtable at 0x0086EA28, forward to button i of the Impl's button shell array
// (+0x44): ButtonShell::EnableInput 0x00577D93 and ButtonShell::Move
// 0x00577CC5 (WorldBuilder names, pinned), the positions passed by value.
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
#include <vector>
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva00578425Element@@@_STL@@YAXPAURva00578425Element@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00578425Element;
namespace _STL { template <> void _Destroy<Rva00578425Element *>(Rva00578425Element *,Rva00578425Element *); }
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAURva00578425Element@@@_STL@@YAXPAURva00578425Element@@0ABU__false_type@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00578425Element;
namespace _STL { template <> void __destroy_aux<Rva00578425Element *>(Rva00578425Element *,Rva00578425Element *,__false_type const &); }
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

// Accessed holder payload: root +4 and StringBase<char> allocation +8.
// Only those fields are established; node and holder extents remain unknown.
struct RadialButtonPayload { char pad00[4]; void *root; char *nameAllocation; };
struct RadialButtonHolder { RadialButtonPayload *payload; };
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
int Rva00577C23AptCall(Rva00222A8BTarget *,void *,const char *,const char *,int *,bool *);

class AptRadialMenu
{
public:
	class Impl;
};

class AptRadialMenu::Impl
{
public:
	class ButtonShell
	{
	public:
		ButtonShell(Impl *,int);
        void EnableInput(bool enable);
		void Move(Coord2D position, Coord2D size);
    private:
        char m_pad00[8];
        Impl *m_impl;
        char m_pad0C[4];
        int m_index;
        char m_pad14[0x28-0x14];
        bool m_enabled;
	};

	virtual void vslot0();
	virtual void Show(int count);
	virtual void PositionButton(int button, const Coord2D &position, const Coord2D &size);
	virtual void EnableButtonInput(int button, bool enable);

private:
	char m_pad04[0x40 - 0x04];
    RadialButtonHolder *m_holder;
	ButtonShell **m_buttons; // +0x44
};


void AptRadialMenu::Impl::PositionButton(int button, const Coord2D &position, const Coord2D &size)
{
	m_buttons[button]->Move(position, size);
}

#include <new>
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva00578425Element {
    AptRadialMenu::Impl::ButtonShell *pointer;
    Rva00578425Element(AptRadialMenu::Impl::ButtonShell *p) : pointer(p) {
        if(p) ++*reinterpret_cast<int *>(reinterpret_cast<char *>(p)+4);
    }
    ~Rva00578425Element() {
        if(pointer) ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(pointer));
    }
};
struct BfmeE12 { char bytes[12]; };
namespace _STL {
template <> void vector<BfmeE12>::swap(vector<BfmeE12> &);
}
// Names this unit references that no unit defines under that spelling. Each is
// bound to the row that owns the pinned retail address (same address, same
// body); the pin keeps the name, the row supplies the definition.
#pragma comment(linker, "/alternatename:?Move@ButtonShell@Impl@AptRadialMenu@@QAEXVCoord2D@@0@Z=?Move@ButtonShell@Impl@AptRadialMenu@@QAEXHHHH@Z")
