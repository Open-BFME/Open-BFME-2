// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /Oy- /DNDEBUG /MD /EHsc
//
// CreateMovieClip identity: WorldBuilder 0x016262D0 names this method in
// StrategicInGameUIArmyHeroIcon.cpp (assertion 53: !m_clip.IsBound()).
// Native 0x005F43B4..0x005F4455 is 161B, RET8 including its hidden result.
// Receiver is the virtual base at icon+0x14. Owner at icon+4 supplies ID+0x54;
// hero at icon+8 supplies templateName+4 and level+0x90; holder is icon+0x0C.
// Allocate the proven 0x1C hero clip through its existing constructor, attach
// using the existing reference setter, populate portrait/type/level and return
// an owning reference (+4 count). HeroClipReference is a TU-scoped ABI view of
// that result, not a recovered original type name. The allocation-only clip
// declaration records its native extent; provider TU defines its inheritance.
// Keep clip snapshots before lookups: lookup may replace the holder. Retail
// uses these snapshots for each image setter. Ordinary new supplies EH state0.
// No donor implementation for this living-world method at BFME1 0bef414b52;
// WB/retail and already matched providers establish this reconstruction.
//
// StrategicInGameUI::ArmyHeroIcon (WorldBuilder
// StrategicInGameUIArmyHeroIcon.cpp names DoUpdate; the name is not
// confirmed by a retail string). Target facts for 0x005F42FF: an override
// reached through the virtual base at +0x14 (this - 0x14 is the icon, whose
// vbtable +4 locates the base whose rowed update 0x005F41AF it runs first);
// the icon's movie clip is at +0x0C and the hero record at +0x08. With a
// clip it replays the hero's +0xB8 flag (0x005FC70A) and +0xC4 byte
// (0x005FC71E); while the clip reports 0x005FC73B and the hero's template
// name (+0x04) is set and found by TheThingFactory, TheMouse shows the
// template's +0x5C4 tooltip (0x005F027D, WorldBuilder
// StrategicInGameUI::GetTooltipText) with no colour and full alpha.
// Member and base names follow WorldBuilder and the callees (inference).
#include "ascii_string.h"
#include "unicode_string.h"

// The clip's rowed setters and query (address-named views).
#include "../../../../Include/GameClient/Rva005FC70A.h"
class Rva005FC71E
{
public:
	void rva005FC71E(unsigned char value);
};
#include "../../../../Include/GameClient/Rva005FC73BPtrChaseField.h"

class ArmyHeroIconMovieClip;
class Image;
class AptMovieClipFrame;
#include "../../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva002BED91 { TargetRef00217D4C *m_ptr; void set(TargetRef00217D4C *); };
class HeroClipReference {
public:
 __forceinline HeroClipReference(ArmyHeroIconMovieClip *armyHeroIconMovieClip) : m_ptr(armyHeroIconMovieClip) {
  if(armyHeroIconMovieClip) ++((TargetRef00217D4C *)armyHeroIconMovieClip)->references;
 }
 __forceinline HeroClipReference(const HeroClipReference &heroClipReference) : m_ptr(heroClipReference.m_ptr) {
  if(m_ptr) ++((TargetRef00217D4C *)m_ptr)->references;
 }
 ~HeroClipReference() { if(m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr); }
private: ArmyHeroIconMovieClip *m_ptr;
};
struct HeroOwnerView { char pad[0x54]; int playerID; };
struct StrategicButtonImageView;
struct Rva005F01D6In;
const Image *__cdecl Rva005F01D6Get(Rva005F01D6In *);
namespace StrategicInGameUI {
const Image *GetButtonImage(const StrategicButtonImageView *,int);
}
#include "../../../../Include/GameClient/ArmyMemberIconMovieClip.h"
namespace StrategicHUD {
class ArmyHeroIconMovieClip { public: ArmyHeroIconMovieClip(AptMovieClipFrame *); private: char storage[0x1c]; };
}
#include "../../../../Include/GameClient/Rva005FC9F0.h"

struct Rva005F42FFHero
{
	char m_pad00[0x04];
	AsciiString m_templateName; // +0x04
	char m_pad08[0x90 - 0x08];
 int m_level; // +0x90
 char m_pad94[0xB8 - 0x94];
	int m_flagB8; // +0xB8
	char m_padBC[0xC4 - 0xBC];
	unsigned char m_byteC4; // +0xC4
};

struct Rva005F42FFTemplate
{
	char m_pad[0x5C4];
	int m_tooltip; // +0x5C4
};

class ThingTemplate;
#include "../../../../Include/Common/ThingFactory.h"
class ThingFactory;
extern ThingFactory *TheThingFactory; // findTemplate viewed as the rowed 0x002D06CA

struct RGBColor;
#include "../../../../Include/GameClient/Mouse.h"
extern Mouse *TheMouse;

namespace StrategicInGameUI {
UnicodeString __cdecl GetTooltipText(int id); // 0x005F027D (pinned)
}

// The virtual base: its update 0x005F41AF (rowed, address-named).
class Rva005F41AF
{
public:
	virtual void DoUpdate();
 virtual HeroClipReference CreateMovieClip(AptMovieClipFrame *);
	void rva005F41AF();
};

namespace StrategicInGameUI {
class ArmyHeroIcon : public virtual Rva005F41AF
{
public:
	virtual void DoUpdate();
 virtual HeroClipReference CreateMovieClip(AptMovieClipFrame *);

private:
	HeroOwnerView *m_owner; // +0x04
	Rva005F42FFHero *m_hero; // +0x08
	ArmyHeroIconMovieClip *m_clip; // +0x0C
	int m_10; // +0x10
};
}

void StrategicInGameUI::ArmyHeroIcon::DoUpdate()
{
	Rva005F41AF::rva005F41AF();
	if (!m_clip)
		return;
	((Rva005FC70A *)m_clip)->rva005FC70A(m_hero->m_flagB8 != 0);
	unsigned char value = m_hero->m_byteC4;
	((Rva005FC71E *)m_clip)->rva005FC71E(value);
	if (!((Rva005FC73BPtrChaseField *)m_clip)->get())
		return;
	const AsciiString *name = &m_hero->m_templateName;
	if (((const StringBase<char> *)name)->isEmpty())
		return;
	Rva005F42FFTemplate *tmpl = (Rva005F42FFTemplate *)TheThingFactory->findTemplate(*name);
	if (!tmpl)
		return;
	int tooltip = tmpl->m_tooltip;
	TheMouse->rva001EEA6D(StrategicInGameUI::GetTooltipText(tooltip), -1, 0, 1.0f);
}

HeroClipReference StrategicInGameUI::ArmyHeroIcon::CreateMovieClip(AptMovieClipFrame *frame) {
 ((Rva002BED91 *)&m_clip)->set((TargetRef00217D4C *)new StrategicHUD::ArmyHeroIconMovieClip(frame));
 int playerID=m_owner->playerID;
 ArmyHeroIconMovieClip *portrait=m_clip;
 ((StrategicHUD::ArmyMemberIconMovieClip *)portrait)->rva005FC9E0(GetButtonImage((const StrategicButtonImageView *)m_hero,playerID));
 ArmyHeroIconMovieClip *typeClip=m_clip;
 ((Rva005FC9F0 *)typeClip)->rva005FC9E8(Rva005F01D6Get((Rva005F01D6In *)m_hero));
 ((Rva005FC9F0 *)m_clip)->rva005FC9F0(m_hero->m_level);
 return HeroClipReference(m_clip);
}

// Native005F43AC..005F43B4 is the eight-byte C79468 slot4 vtordisp
// adapter to the exact165B DoUpdate above. The stored displacement at
// virtual receiver-4 removes the actual/nominal virtual-base difference;
// primary icon is then14 bytes earlier. The qualified override call passes
// its nominal virtual-base receiver and compiles to the native tail jump.
// This address-derived view names only the adapter's no-argument ABI.
class Rva005F43AC { public: void update(); };
void Rva005F43AC::update()
{
    StrategicInGameUI::ArmyHeroIcon *icon = (StrategicInGameUI::ArmyHeroIcon *)
        ((char *)this - *(int *)((char *)this - 4) - 0x14);
    icon->StrategicInGameUI::ArmyHeroIcon::DoUpdate();
}
