// cl: /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::PlanningPhaseBehavior::Impl (WorldBuilder
// StrategicInGameUIPlanningPhaseBehavior.cpp names its translateGameMessage, vtable match).
// Target facts for 0x00575C15: offers the message to its +0x28 sub-translator (when set, vslot 2), its ManualPhaseEnder +0x30 and its PlayerStatusDisplayer (0x005CD690) +0x40, consuming it
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
	virtual int OnMouseLeftClick(const IRegion2D &region, unsigned modifiers);	// slot 18 (+0x48)
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

// A nullable sub-translator viewed by slot: vslot 2 translates.
class Rva00575C15SubTranslator
{
public:
	virtual void vslot0();
	virtual void vslot1();
	virtual GameMessageDisposition Translate(const GameMessage *msg);
};

namespace StrategicInGameUI
{
class PlanningPhaseBehavior
{
public:
	class Impl;
};
}

// The picker the click handler runs on the Impl itself (rowed
// address-named, 0x005757A5; WB 0x014D35E0): it takes the picked pixel and
// may replace the +0x28 sub-translator.
class Rva005757A5
{
public:
	void rva005757A5(int point);
};

class StrategicInGameUI::PlanningPhaseBehavior::Impl : public UserInputTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	virtual int OnMouseLeftClick(const IRegion2D &region, unsigned modifiers);

private:
	char m_pad04[0x28 - 0x04];
	Rva00575C15SubTranslator *m_sub; // +0x28
	char m_pad2C[0x30 - 0x2C];
	StrategicInGameUI::ManualPhaseEnder m_phaseEnder; // +0x30
	StrategicInGameUI::PlayerStatusDisplayer m_statusDisplayer; // +0x40
};

GameMessageDisposition StrategicInGameUI::PlanningPhaseBehavior::Impl::translateGameMessage(const GameMessage *msg)
{
	Rva00575C15SubTranslator *sub;
	if (((sub = m_sub) != 0 && sub->Translate(msg) == DESTROY_MESSAGE)
		|| m_phaseEnder.Translate(msg) == DESTROY_MESSAGE
		|| m_statusDisplayer.rva005CD690(msg) == DESTROY_MESSAGE)
		return DESTROY_MESSAGE;
	return UserInputTranslator::translateGameMessage(msg);
}

// StrategicInGameUI::PlanningPhaseBehavior::Impl::OnMouseLeftClick, retail
// 0x00575C5D (73 bytes, ret 8). A virtual: nothing calls it directly, and it
// fills slot 18 (+0x48) of the Impl vftable 0x00C6E720, whose slot 0 is
// translateGameMessage 0x00575C15 above and which the Impl destructor
// 0x00575F38 (rowed as Rva00575F38) and constructor 0x0057621A install.
// WB's table for this class (0x01F49638, slot 0
// PlanningPhaseBehavior::Impl::translateGameMessage) holds WB 0x014D3FD0 in
// slot 18; that body measures its first argument with IRegion2D::width and
// ::height, returns 0 for a drag, otherwise hands the region's low corner to
// WB 0x014D35E0 (retail 0x005757A5) and reports whether +0x28 changed. The
// slot's name is the base handler's (WB names the same slot's overrides in
// the two ResolveBattlesBehavior units OnMouseLeftClick); the second word is
// unused.
int StrategicInGameUI::PlanningPhaseBehavior::Impl::OnMouseLeftClick(const IRegion2D &region, unsigned modifiers)
{
	if (region.hi.x - region.lo.x > 0 || region.hi.y - region.lo.y > 0)
		return 0;
	Rva00575C15SubTranslator *old = m_sub;
	ICoord2D point;
	point.x = region.lo.x;
	point.y = region.lo.y;
	((Rva005757A5 *)this)->rva005757A5((int)&point);
	return m_sub != old;
}
