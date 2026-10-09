// cl: /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl (WorldBuilder
// StrategicInGameUIPlanRetreatsPhaseBehavior.cpp names its translateGameMessage, callgraph).
// Target facts for 0x005771F4: offers the message to its +0x14 retreat planner (when set, 0x005D1FD3), its ManualPhaseEnder +0x18 and its PlayerStatusDisplayer (0x005CD690) +0x28, consuming it
// (1) when one does, else defers to the base
// UserInputTranslator::translateGameMessage 0x005CBC95 (WorldBuilder name,
// pinned). Member types are the callees' views (inference).

enum GameMessageDisposition
{
	KEEP_MESSAGE,
	DESTROY_MESSAGE
};

class GameMessage;

struct ICoord2D
{
	int x;
	int y;
};

// WB calls IRegion2D::width/height on the click region; retail inlines both
// (the region.cpp rows 0x00004D4B/0x00004D51 are the out-of-line copies), so
// the extents are spelled out in the handler rather than defining second
// copies of those members.
struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

// The translator base (WB UserInputTranslator.cpp): translateGameMessage in
// slot 0, a deleting dtor in slot 1, then the input handlers, whose
// defaults are the shared stubs 0x005748B2 (slot 2 and slots 18..25) and
// 0x005748AD (slots 3..17). Only the slots this unit needs are named.
class UserInputTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);	// slot 0
	virtual ~UserInputTranslator();										// slot 1
	virtual void slot02(); virtual void slot03(); virtual void slot04();
	virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10();
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17();
	// Slot 18 takes the region and the integer argument the base
	// translateGameMessage fetches for it. int follows ZH, where the mouse
	// click messages carry TheKeyboard->getModifierFlags() (an Int) after
	// the region; retail cannot tell int from unsigned here.
	virtual int OnMouseLeftClick(const IRegion2D &region, int modifiers);	// slot 18 (+0x48)
};

// The translators behind the behavior (ManualPhaseEnder.cpp's and
// PlayerStatusDisplayer.cpp's units).
namespace StrategicInGameUI
{
class ManualPhaseEnder
{
public:
	GameMessageDisposition Translate(const GameMessage *msg); // 0x005CD8F7

private:
	char m_data[0x10];
};
}
namespace StrategicInGameUI
{
class PlayerStatusDisplayer
{
public:
	GameMessageDisposition rva005CD690(const GameMessage *msg); // 0x005CD690
};
}

// The retreat planner (rowed address-named, 0x005D1FD3).
class Rva005D1F45
{
public:
	int rva005D1FD3(GameMessage *msg);
};

namespace StrategicInGameUI
{
class PlanRetreatsPhaseBehavior
{
public:
	class Impl;
};
}

// The army selector the click handler builds on its stack (WB
// PlanRetreatsPhaseBehavior::Impl::ArmySelector, whose WB constructor
// 0x014CE700 is retail's rowed 0x0057709A), viewed under its rowed
// address-derived names: the constructor takes the Impl, the picker body
// 0x005CBB4A (WB 0x015B0E60 in LivingWorldThingPicker.cpp, whose diagnostic
// names LivingWorldThingPicker::operator()) is reached through its existing
// address-derived spelling, and the destructor is the rowed vptr reset
// 0x005CB9F3, inline here as in the picker's other callers 0x00574959 and
// 0x005757A5.
class Rva0005CB9F3DwordImmSetter
{
public:
	void apply();
};
class Rva00574815
{
public:
	void rva005CBB4A(int first, int second, int third);
};
class Rva0057709A
{
public:
	Rva0057709A(int v);
	__forceinline ~Rva0057709A()
	{
		((Rva0005CB9F3DwordImmSetter *)this)->apply();
	}

private:
	unsigned int m_layout[3];
};

class StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl : public UserInputTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	virtual int OnMouseLeftClick(const IRegion2D &region, int modifiers);

private:
	char m_pad04[0x10 - 0x04];
	void *m_viewer; // +0x10, the picker's first argument
	Rva005D1F45 *m_planner; // +0x14
	StrategicInGameUI::ManualPhaseEnder m_phaseEnder; // +0x18
	StrategicInGameUI::PlayerStatusDisplayer m_statusDisplayer; // +0x28
};

GameMessageDisposition StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl::translateGameMessage(const GameMessage *msg)
{
	if ((m_planner && m_planner->rva005D1FD3((GameMessage *)msg) == 1)
		|| m_phaseEnder.Translate(msg) == DESTROY_MESSAGE
		|| m_statusDisplayer.rva005CD690(msg) == DESTROY_MESSAGE)
		return DESTROY_MESSAGE;
	return UserInputTranslator::translateGameMessage(msg);
}

// StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl::OnMouseLeftClick,
// retail 0x0057723C (131 bytes, ret 8). A virtual: nothing calls it
// directly, and it fills slot 18 (+0x48) of the Impl vftable 0x00C6E8F8,
// whose slot 0 is translateGameMessage 0x005771F4 above and which the Impl
// destructor 0x005770F7 and constructor 0x005776A7 install. WB's table for
// this class (0x01F48908, slot 0 PlanRetreatsPhaseBehavior::Impl::
// translateGameMessage) holds WB 0x014CF2A0 in slot 18; that body measures
// its first argument with IRegion2D::width and ::height, returns 0 for a
// drag, otherwise keeps +0x14, builds the army selector on the Impl, runs the
// picker with +0x10, the region's low corner and 0, and reports whether +0x14
// changed. The slot's name is the base handler's (WB names the same slot's
// overrides in the two ResolveBattlesBehavior units OnMouseLeftClick); the
// second word is unused.
int StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl::OnMouseLeftClick(const IRegion2D &region, int modifiers)
{
	if (region.hi.x - region.lo.x > 0 || region.hi.y - region.lo.y > 0)
		return 0;
	Rva005D1F45 *old = m_planner;
	Rva0057709A selector((int)this);
	ICoord2D point;
	point.x = region.lo.x;
	point.y = region.lo.y;
	((Rva00574815 *)&selector)->rva005CBB4A((int)m_viewer, (int)&point, 0);
	// WB reads +0x14 into its own slot before comparing; comparing the member
	// directly schedules the compare differently from retail.
	Rva005D1F45 *current = m_planner;
	return current != old;
}
