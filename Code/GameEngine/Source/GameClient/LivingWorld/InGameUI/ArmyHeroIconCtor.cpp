// ArmyHeroIconCtor
// partial score=0.99 date=2026-10-11
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
#include "../../../../Include/GameClient/Rva005FC71E.h"
#include "../../../../Include/GameClient/Rva005FC73BPtrChaseField.h"

class ArmyHeroIconMovieClip;
class Image;
class AptMovieClipFrame;
#include "../../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
#include "../../../../Include/Common/Rva002BED91.h"
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

// Rows retail's tables hold in the shared virtual base's slots (0x00879448, 0x00877C50).
#include "../../../../Include/Common/Rva001524CA.h"
#include "../../../../Include/GameClient/Rva005F41AF.h"
class Rva005F3FF4 { public: void rva005F3FF4(); };
#include "../../../../Include/Common/Rva005F3F6B.h"
// Retail's details-portion rows. A vtordisp thunk enters them with the virtual base's pointer and they adjust it
// themselves, so these forward by jump: a cast to a class would subtract the base's offset a second time.
extern "C" {
void __identifier("?fwd@Rva005E3AA2Mid@@QAEXXZ")();
void __identifier("?rva005E51D3@Rva005E51D3@@QAEXXZ")();
void __identifier("?rva005E4389@Rva005E4389@@QAEXXZ")();
void __identifier("?rva005E3E41@Rva005E3E41@@QAEXXZ")();
}
// Their destructors enter with the virtual base's pointer, 0x14 past this class's start.
class Rva005F422C { public: virtual ~Rva005F422C(); };
class Rva005E3A76 { public: virtual ~Rva005E3A76(); };
class Rva005F3F73 { public: Rva005F3F73(void *, void *) throw(); private: char storage[0x18]; };
class Rva005F4096 { public: void clear(); Rva005F4096(Rva005F3F73 *p) : p(p) {} private: Rva005F3F73 *p; };
#include "../../../../Include/Common/Rva005F4179Base.h"
class Rva005F4179 : public Rva005F4179Base {
public:
 Rva005F4179(void *clip); virtual ~Rva005F4179();
 virtual void slot1()=0;
 virtual HeroClipReference CreateMovieClip(AptMovieClipFrame *)=0;
 __declspec(noinline) virtual TreeHintRef00217D4C rva005F4254() { return ((Rva001524CA *)this)->rva001524CA(); }
 __declspec(noinline) virtual void DoUpdate() { ((Rva005F41AF *)this)->rva005F41AF(); }
 virtual void slot5() {}
 __declspec(noinline) virtual void rva005F3FF4() { ((Rva005F3FF4 *)this)->rva005F3FF4(); }
 __declspec(noinline) virtual void rva005F3F6B() { ((Rva005F3F6B *)this)->rva005F3F6B(); }
private: Rva005F4096 leaf;
};
struct HeroClipHolder { ArmyHeroIconMovieClip *p; HeroClipHolder():p(0){} };
namespace StrategicInGameUI {
class ArmyHeroIcon : public virtual Rva005F4179 {
public:
 ArmyHeroIcon(void *owner,void *clip,void *entry);
 __declspec(noinline) virtual ~ArmyHeroIcon() { ((Rva005F422C *)((char *)this + 0x14))->Rva005F422C::~Rva005F422C(); }
 virtual void DoUpdate();
 virtual HeroClipReference CreateMovieClip(AptMovieClipFrame *);
 __declspec(noinline) virtual TreeHintRef00217D4C rva005F4254();
private: HeroOwnerView *m_owner; Rva005F42FFHero *m_hero; HeroClipHolder m_clip;
};
}
StrategicInGameUI::ArmyHeroIcon::ArmyHeroIcon(void *owner,void *clip,void *hero):Rva005F4179(clip),m_owner((HeroOwnerView*)owner),m_hero((Rva005F42FFHero*)hero),m_clip() {}

// The hero composite (Rva005F422CDtor.cpp's Rva005E4202: this icon plus the
// 16-byte details portion, sharing the virtual base at +0x24) reaches the
// three ArmyHeroIcon overrides through vtordisp thunks with a further -0x10
// (0x005E3C6F/7A/85, slots 2-4 of its virtual-base table 0x00877C74): the
// icon expects its virtual base at +0x14. A TU-local view of the composite
// emits them; only the thunks, named after ArmyHeroIcon, are claimed.
namespace {
class HeroDetailsPortion : public virtual Rva005F4179 {
public:
 HeroDetailsPortion() : Rva005F4179(0) {}
 __declspec(noinline) virtual ~HeroDetailsPortion() { ((Rva005E3A76 *)((char *)this + 0x14))->Rva005E3A76::~Rva005E3A76(); }
 __declspec(noinline) virtual void slot1() { __identifier("?fwd@Rva005E3AA2Mid@@QAEXXZ")(); }
 __declspec(noinline) virtual void slot5() { __identifier("?rva005E51D3@Rva005E51D3@@QAEXXZ")(); }
 __declspec(noinline) virtual void rva005F3FF4() { __identifier("?rva005E4389@Rva005E4389@@QAEXXZ")(); }
 __declspec(noinline) virtual void rva005F3F6B() { __identifier("?rva005E3E41@Rva005E3E41@@QAEXXZ")(); }
private: char m_unrecovered[12];
};
struct EmitVtableTag;
class HeroComposite : public StrategicInGameUI::ArmyHeroIcon, public HeroDetailsPortion {
public:
 HeroComposite(EmitVtableTag *);
};
}
// ?<HeroComposite::HeroComposite> absent-from-retail
HeroComposite::HeroComposite(EmitVtableTag *) : Rva005F4179(0), StrategicInGameUI::ArmyHeroIcon(0,0,0) {}
typedef char HeroCompositeHas48Bytes[sizeof(HeroComposite)==0x30?1:-1];
