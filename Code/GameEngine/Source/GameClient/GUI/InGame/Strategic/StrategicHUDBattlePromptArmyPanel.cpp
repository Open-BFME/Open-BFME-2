// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// StrategicHUD::AbstractBattlePromptArmyPanelFactory (WorldBuilder
// StrategicHUDBattlePromptArmyPanel.cpp names CreateArmyPanel; the name is
// not confirmed by a retail string). Target facts: 0x00600579 (ret 0xC,
// hidden return slot) asks the factory's vslot 2 for the panel with the
// level and name and returns that reference counted handle (count +0x04 of
// the referent, released through the rowed 0x0007DEEF). Called by
// BattlePromptPlayerPageMovieClip::Impl::OnArmyPanelLoaded 0x005FFD77 for
// the garrison and hero panel slots (Common/Rva005FFCCBAppend.cpp).
#include "ascii_string.h"

// The panel handle (TreeHintRef00217D4C: assignment 0x002174A4 rowed in
// WWLib/stlport_rb_tree_hint_00218022.cpp).
#include "../../../../../../Libraries/Source/Apt/AptRefTarget.h"
// Inline release body for this unit; the header only declares the destructor.
inline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
	if (m_ptr)
		ReleaseTreeHintRef00217D4C(m_ptr);
}

namespace StrategicHUD {
class AbstractBattlePromptArmyPanelFactory
{
public:
	virtual ~AbstractBattlePromptArmyPanelFactory();
	virtual void slot1();
	// Slot 2: build the panel movie clip (name inferred from the caller).
	virtual TreeHintRef00217D4C CreateArmyPanelMovieClip(int level, const AsciiString &name) = 0;

	TreeHintRef00217D4C CreateArmyPanel(int level, const AsciiString &name);
};
}

TreeHintRef00217D4C StrategicHUD::AbstractBattlePromptArmyPanelFactory::CreateArmyPanel(int level, const AsciiString &name)
{
	TreeHintRef00217D4C panel = CreateArmyPanelMovieClip(level, name);
	return panel;
}
