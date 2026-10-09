// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
// WorldBuilder StrategicInGameUIRegionDetailsStructuresPage.cpp:261..285 names
// Icon::Update and supplies the construction-progress/hover-tooltip purpose.
// Retail 0x005E22A0..0x005E2338 supplies the complete 152-byte RET0 body,
// owner/index/hover fields +10/+14/+1C, plot +20/+34 and template +28/+2C.
// These record structures are TU-scoped target views; their member labels follow
// WorldBuilder assertions and uses, rather than a donor class-layout claim.
// Icon callbacks in Rva005E2338Wrap.cpp use its secondary base at +8; this
// routine receives the complete icon; Update is non-virtual because the
// primary vtable at 0x00C77B28 contains only the scalar deleting destructor. The rowed +10/+14 movie-clip forwarder,
// countdown query and Mouse tooltip consumer retain their existing spellings.
// No compatible clean reference implementation was available at BFME1 9cbfb551.
#include "unicode_string.h"
struct RGBColor;
class Image;
class LivingWorldBuildPlot;
struct Rva005F8F96 { Rva005F8F96() : pointer(0) {} ~Rva005F8F96(); void *pointer; };
struct Rva002BA8F1Listener;
class Rva005A0B4CList { public: void append(Rva002BA8F1Listener *); };
struct Rva005F0220In;
const Image *__cdecl Rva005F0220Get(Rva005F0220In *);
namespace StrategicInGameUI { const Image *__cdecl GetButtonImage(void *); }
const Image *__cdecl Rva005F0318Get(void *);
class Rva005E261C { public: void rva005E261C(); };
// Native constructor 0x005E28FE proves a primary vptr/count pair and
// two four-byte observer bases at +8 and +C. The building-change vtable
// 0x00C77B04 takes the +C receiver; MSVC supplies that secondary this view.
// Base names below describe TU-scoped roles, not a canonical class contract.
class IconCountedBase {
public: IconCountedBase() : references(0) {} virtual ~IconCountedBase(); int references;
};
class IconMouseObserver {
public: ~IconMouseObserver(); virtual void onUnknown(int); virtual void OnLeft(int); virtual void OnRight(int);
virtual void OnRollOut(int); virtual void OnRollOver(int); virtual void OnTypeRollOut(int); virtual void OnTypeRollOver(int);
};
class LivingWorldBuildPlotObserver {
public: ~LivingWorldBuildPlotObserver(); virtual void OnBuildPlotBuildingChanged(LivingWorldBuildPlot &); virtual void onUnknown(LivingWorldBuildPlot &);
};
class Mouse { public: void rva001EEA6D(UnicodeString, int, const RGBColor *, float); };
extern Mouse *TheMouse;
class Rva005E2138 { public: void *rva005E2138(); };
class Rva004FC21AOwner { public: int rva004FC207(); };
namespace StrategicInGameUI {
enum LivingWorldBuildingType { LIVING_WORLD_BUILDING_TYPE_COUNT = 5 };
UnicodeString __cdecl GetTooltipText(LivingWorldBuildingType);
struct StructureTemplate { char pad00[0x28]; int totalBuildTime; LivingWorldBuildingType type; __forceinline LivingWorldBuildingType getType() const { return type; } };
struct Structure { char pad00[0x28]; StructureTemplate *definition; };
struct BuildPlot { char pad00[0x20]; Structure *building; char pad24[0x34-0x24]; bool constructing; };
struct Region { char pad00[0x170]; BuildPlot **plots; };
class StructureIconSlot {
public:
 virtual void AddObserver(IconMouseObserver *); virtual void slot01(); virtual void SetState(int); virtual void slot03();
 virtual void SetImage(const Image *); virtual void slot05(); virtual void SetBuildingTypeImage(const Image *); virtual void slot07();
 virtual void ShowProgress(int total, int remaining);
 virtual void HideProgress();
};
class RegionDetailsStructuresPage { public: class Impl; };
class RegionDetailsStructuresPage::Impl {
public:
 class Icon;
 char pad00[0x0c]; Region *region; char pad10[0x20-0x10]; int selected;
};
class RegionDetailsStructuresPage::Impl::Icon : public IconCountedBase, public IconMouseObserver, public LivingWorldBuildPlotObserver {
public:
 Icon(Impl &, int); virtual ~Icon(); void Update();
 virtual void OnBuildPlotBuildingChanged(LivingWorldBuildPlot &);
private:
 Impl *owner; int index; Rva005F8F96 help; bool hovered;
 BuildPlot *getBuildPlot() { return owner->region->plots[index]; }
};
}
// Retail 0x005F0318 is a five-byte cdecl tail call, not the Observable
// addObserver body suggested by the WorldBuilder call-site pairing. Both
// this page's constructor and building-change callback use it when the plot
// is empty; it forwards the plot's selection view to the rowed portrait query.
namespace StrategicInGameUI {
}

namespace StrategicInGameUI {
RegionDetailsStructuresPage::Impl::Icon::Icon(Impl &page, int slotIndex) : owner(&page), index(slotIndex), hovered(false) {
    BuildPlot &plot=*getBuildPlot();
    ((Rva005A0B4CList *)((char *)&plot+8))->append((Rva002BA8F1Listener *)(LivingWorldBuildPlotObserver *)this);
    StructureIconSlot &clip=*(StructureIconSlot *)((Rva005E2138 *)this)->rva005E2138();
    clip.AddObserver(this);
    clip.SetImage(plot.building ? StrategicInGameUI::GetButtonImage(plot.building) : Rva005F0318Get(&plot));
    const Image *typeImage=Rva005F0220Get((Rva005F0220In *)&plot);
    clip.SetBuildingTypeImage(typeImage);
    clip.SetState(1);
}
}
