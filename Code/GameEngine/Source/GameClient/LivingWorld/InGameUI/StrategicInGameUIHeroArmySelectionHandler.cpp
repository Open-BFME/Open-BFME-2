// cl: /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::HeroArmySelectionHandler (WorldBuilder
// StrategicInGameUIHeroArmySelectionHandler.cpp). Target facts for
// OnMouseoverRegionChanged 0x005D2006 (virtual; its pointer sits in the
// vtables at 0x0086E85C, 0x008750E4 and 0x0087577C; ret 8): caches in +0x10
// the result of the handler's own check 0x005D1F22 (unnamed in WorldBuilder,
// pinned address-named). The tracker type is viewed by name only.
//
// ?rva005D1F22@HeroArmySelectionHandler@StrategicInGameUI@@QAE_NXZ, retail
// 0x005D1F22..0x005D1F45 (35 bytes): that check. When the +0x08 owner's +0x1C
// entry is set and TheLivingWorldLogic exists, it is the rowed
// LivingWorldLogic::rva002B27B5 test of the +0x0C army with that entry; else
// false.
class MouseoverRegionTracker;

struct LivingWorldArmy;
class Rva00318C32Ret;

class LivingWorldLogic
{
public:
	bool rva002B27B5(LivingWorldArmy *army, Rva00318C32Ret *entry);
};

extern LivingWorldLogic *TheLivingWorldLogic;

struct Rva005D1F22Owner
{
	char m_pad00[0x1C];
	Rva00318C32Ret *m_entry1C;				// +0x1C
};

namespace StrategicInGameUI
{
class HeroArmySelectionHandler
{
public:
	virtual void OnMouseoverRegionChanged(MouseoverRegionTracker &tracker, int region);
	__declspec(noinline) bool rva005D1F22();

private:
	char m_pad04[0x08 - 0x04];
	Rva005D1F22Owner *m_owner08;			// +0x08
	LivingWorldArmy *m_army0C;				// +0x0C
	bool m_10; // +0x10
};
}

void StrategicInGameUI::HeroArmySelectionHandler::OnMouseoverRegionChanged(MouseoverRegionTracker &tracker, int region)
{
	m_10 = rva005D1F22();
}

bool StrategicInGameUI::HeroArmySelectionHandler::rva005D1F22()
{
	Rva00318C32Ret *entry = m_owner08->m_entry1C;
	if (entry && TheLivingWorldLogic)
		return TheLivingWorldLogic->rva002B27B5(m_army0C, entry);
	return false;
}
