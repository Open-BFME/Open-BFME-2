// cl: /O1 /DNDEBUG /MD /EHsc
//
// AptRadialMenu::Impl (WorldBuilder GameClient/Gui/InGame/AptRadialMenu.cpp).
// Target facts: PositionButton 0x00577E70 (ret 0xC) and EnableButtonInput
// 0x00577E94 (ret 8), slots 2 and 3 of the vtable at 0x0086EA28, forward to button i of the Impl's button shell array
// (+0x44): ButtonShell::EnableInput 0x00577D93 and ButtonShell::Move
// 0x00577CC5 (WorldBuilder names, pinned), the positions passed by value.
#include "../../../../../Libraries/Include/Lib/Coord2D.h"

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
	};

	virtual void vslot0();
	virtual void vslot1();
	virtual void PositionButton(int button, const Coord2D &position, const Coord2D &size);
	virtual void EnableButtonInput(int button, bool enable);

private:
	char m_pad04[0x44 - 0x04];
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
