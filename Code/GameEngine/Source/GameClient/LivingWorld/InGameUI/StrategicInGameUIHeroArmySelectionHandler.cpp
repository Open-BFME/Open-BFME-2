// cl: /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::HeroArmySelectionHandler (WorldBuilder
// StrategicInGameUIHeroArmySelectionHandler.cpp). Target facts for
// OnMouseoverRegionChanged 0x005D2006 (virtual; its pointer sits in the
// vtables at 0x0086E85C, 0x008750E4 and 0x0087577C; ret 8): caches in +0x10
// the result of the handler's own check 0x005D1F22 (unnamed in WorldBuilder,
// pinned address-named). The tracker type is viewed by name only.
class MouseoverRegionTracker;

namespace StrategicInGameUI
{
class HeroArmySelectionHandler
{
public:
	virtual void OnMouseoverRegionChanged(MouseoverRegionTracker &tracker, int region);
	bool rva005D1F22();

private:
	char m_pad04[0x10 - 0x04];
	bool m_10; // +0x10
};
}

void StrategicInGameUI::HeroArmySelectionHandler::OnMouseoverRegionChanged(MouseoverRegionTracker &tracker, int region)
{
	m_10 = rva005D1F22();
}
