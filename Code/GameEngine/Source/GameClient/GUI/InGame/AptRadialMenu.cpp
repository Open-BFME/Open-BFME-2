// cl: /O1 /DNDEBUG /MD /EHsc
//
// AptRadialMenu::Impl (WorldBuilder GameClient/Gui/InGame/AptRadialMenu.cpp).
// Target facts: PositionButton 0x00577E70 (ret 0xC) and EnableButtonInput
// 0x00577E94 (ret 8), slots 2 and 3 of the vtable at 0x0086EA28, forward to button i of the Impl's button shell array
// (+0x44): ButtonShell::EnableInput 0x00577D93 and ButtonShell::Move
// 0x00577CC5 (WorldBuilder names, pinned), the positions passed by value.
#include "../../../../../Libraries/Include/Lib/Coord2D.h"

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
	virtual void vslot1();
	virtual void PositionButton(int button, const Coord2D &position, const Coord2D &size);
	virtual void EnableButtonInput(int button, bool enable);

private:
	char m_pad04[0x40 - 0x04];
    RadialButtonHolder *m_holder;
	ButtonShell **m_buttons; // +0x44
};

void AptRadialMenu::Impl::EnableButtonInput(int button, bool enable)
{
	m_buttons[button]->EnableInput(enable);
}

void AptRadialMenu::Impl::PositionButton(int button, const Coord2D &position, const Coord2D &size)
{
	m_buttons[button]->Move(position, size);
}

// Native 00577D93..00577DE1 RET4; WB014C6FF0 EnableInput asserts342.
// Existing caller EnableButtonInput and its method pin establish this receiver.
// The helper125B at577C23 only reads the bool pointer; snapshot its value
// in the changed-state branch so the post-call store follows retail.
void AptRadialMenu::Impl::ButtonShell::EnableInput(bool enable)
{
    if (enable != m_enabled) {
        const bool requested=enable;
        RadialButtonPayload *payload=m_impl->m_holder->payload;
        const char *prefix=payload->nameAllocation ? payload->nameAllocation+8 : "";
        Rva00577C23AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager,
            payload->root,prefix,"EnableButtonInput",&m_index,&enable);
        m_enabled=requested;
    }
}
