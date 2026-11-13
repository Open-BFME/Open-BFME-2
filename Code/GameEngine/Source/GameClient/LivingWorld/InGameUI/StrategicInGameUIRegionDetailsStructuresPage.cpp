// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc_alloconly
// stlport
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
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAURva005E2B0EElement@@U1@V?$allocator@URva005E2B0EElement@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva005E2B0EElement;
namespace _STL { template <> Rva005E2B0EElement * _STLP_alloc_proxy<Rva005E2B0EElement *,Rva005E2B0EElement,allocator<Rva005E2B0EElement> >::allocate(unsigned int); }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
struct RGBColor;
class Image;
class LivingWorldBuildPlot;
struct Rva005F0220In;
const Image *__cdecl Rva005F0220Get(Rva005F0220In *);
namespace StrategicInGameUI { const Image *__cdecl GetButtonImage(void *); }
__declspec(noinline) const Image *__cdecl Rva005F0318Get(void *);
class Rva005E261C { public: void rva005E261C(); };
// Native constructor 0x005E28FE proves a primary vptr/count pair and
// two four-byte observer bases at +8 and +C. The building-change vtable
// 0x00C77B04 takes the +C receiver; MSVC supplies that secondary this view.
// Base names below describe TU-scoped roles, not a canonical class contract.
class IconCountedBase {
public: virtual ~IconCountedBase(); int references;
};
class IconMouseObserver {
public: virtual void onUnknown(int); virtual void OnLeft(int); virtual void OnRight(int);
virtual void OnRollOut(int); virtual void OnRollOver(int); virtual void OnTypeRollOut(int); virtual void OnTypeRollOver(int);
};
class LivingWorldBuildPlotObserver {
public: virtual void OnBuildPlotBuildingChanged(LivingWorldBuildPlot &); virtual void onUnknown(LivingWorldBuildPlot &);
};
#include "../../../../Include/GameClient/Mouse.h"
extern Mouse *TheMouse;
#include "../../../../Include/Common/Rva005E2138.h"
class Rva004FC21AOwner { public: int rva004FC207(); };
namespace StrategicInGameUI {
enum LivingWorldBuildingType { LIVING_WORLD_BUILDING_TYPE_COUNT = 5 };
UnicodeString __cdecl GetTooltipText(LivingWorldBuildingType);
struct StructureTemplate { char pad00[0x28]; int totalBuildTime; LivingWorldBuildingType type; __forceinline LivingWorldBuildingType getType() const { return type; } };
struct Structure { char pad00[0x28]; StructureTemplate *definition; };
struct BuildPlot { char pad00[0x20]; Structure *building; char pad24[0x34-0x24]; bool constructing; };
struct Region { char pad00[0x170]; _STL::vector<BuildPlot *> plots; };
class StructureIconSlot {
public:
 virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
 virtual void SetImage(const Image *); virtual void slot05(); virtual void SetBuildingTypeImage(const Image *); virtual void slot07();
 virtual void ShowProgress(int total, int remaining);
 virtual void HideProgress();
};
}
// Retail 0x005F16F9 constructs this movie clip base (vtable 0x00C78EFC: the
// deleting destructor and four empty virtuals the page Impl overrides).
namespace StrategicHUD {
class RegionDetailsStructuresMovieClip {
public:
 RegionDetailsStructuresMovieClip(int level, const AsciiString &name, int iconSlotCount, int arg);
 virtual ~RegionDetailsStructuresMovieClip();
 virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04();
private:
 void *m_impl;
};
}
// Movie-clip accessors rowed under address-derived classes: the clip's icon
// slot count and the portrait image/flag setters.
class Rva005ED291 { public: int rva005F05D7() const; };
class Rva005F09E7 { public: void rva005F09E7(const Image *); };
class Rva005F09EF { public: void rva005F09EF(const Image *); };
class Rva005F09DF { public: void rva005F09DF(bool); };
const Image *__cdecl Rva005F01B8Get(int);
#include "../../../../Include/GameLogic/LivingWorldRegion.h"
class Rva005E2896Vector { public: void reserve(unsigned int); };
#include "../../../../Include/Common/PageContext.h"
// The .data word 0x00E066A4 (zero-initialised; only this ctor reads it).
int g_rva00E066A4StructuresClipArg;
namespace StrategicInGameUI {
struct TargetRef00217D4CIcon;
class RegionDetailsStructuresPage { public: class Impl; };
}
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
// The page's counted icon reference (vector element, push_back 0x005E2B0E).
struct Rva005E2B0EElement {
 Rva005E2B0EElement(void *icon) : pointer((int *)icon) { if (pointer) ++pointer[1]; }
 Rva005E2B0EElement(const Rva005E2B0EElement &other) : pointer(other.pointer) { if (pointer) ++pointer[1]; }
 ~Rva005E2B0EElement() { ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)pointer); }
 int *pointer;
};
// _M_clear is retail's shared 4-byte clear worker 0x00577EF1 (ICF), rowed as
// vector<Rva002B9062Element>::_M_clear; the same inline forwarder as
// StlportVectorInsertOverflowFamily.cpp, so this unit's growth-path copy matches it.
struct Rva002B9062Element;
namespace _STL { template <> void vector<Rva002B9062Element>::_M_clear(); }
struct Rva002B9062ClearAccess : _STL::vector<Rva002B9062Element> { __forceinline void clearWorker() { _M_clear(); } };
namespace _STL { template <> __declspec(dllimport) __forceinline void vector<Rva005E2B0EElement>::_M_clear() { ((Rva002B9062ClearAccess *)this)->clearWorker(); } }
namespace StrategicInGameUI {
class RegionDetailsStructuresPage::Impl : public StrategicHUD::RegionDetailsStructuresMovieClip {
public:
 class Icon;
 Impl(void *page, void *level, void *name, const PageContext &context);
 virtual ~Impl();
 virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04();
 void *page; Region *region; void *observer;
 _STL::vector<Rva005E2B0EElement> icons;
 int selected; int pendingSelection;
 struct Ref { Ref() : pointer(0) {} ~Ref() { if (pointer) ReleaseTreeHintRef00217D4C(pointer); } TargetRef00217D4C *pointer; } current;
 bool flag;
};
class RegionDetailsStructuresPage::Impl::Icon : public IconCountedBase, public IconMouseObserver, public LivingWorldBuildPlotObserver {
public:
 Icon(Impl &, int); void Update();
 virtual void OnBuildPlotBuildingChanged(LivingWorldBuildPlot &);
private:
 friend class Impl;
 Impl *owner; int index; char pad18[4]; bool hovered;
 BuildPlot *getBuildPlot() { return owner->region->plots[index]; }
};
void RegionDetailsStructuresPage::Impl::Icon::Update() {
 StructureIconSlot *clip=(StructureIconSlot *)((Rva005E2138 *)this)->GetBuildPlot();
 BuildPlot *plot=getBuildPlot();
 if (plot->constructing && plot->building) {
  int total=plot->building->definition->totalBuildTime;
  int remaining=((Rva004FC21AOwner *)plot)->rva004FC207();
  clip->ShowProgress(total,remaining);
 } else {
  clip->HideProgress();
 }
 if (hovered) {
  Structure *building=getBuildPlot()->building;
  if (building) {
   StructureTemplate *definition=building->definition;
   TheMouse->rva001EEA6D(GetTooltipText(definition->getType()),-1,0,1.0f);
  }
 }
}
}
// Retail 0x005F0318 is a five-byte cdecl tail call, not the Observable
// addObserver body suggested by the WorldBuilder call-site pairing. Both
// this page's constructor and building-change callback use it when the plot
// is empty; it forwards the plot's selection view to the rowed portrait query.
class Image;
struct Rva005D23BBSelection;
namespace StrategicInGameUI {
const Image *__cdecl GetSelectionPortrait(const Rva005D23BBSelection *selection);
}
__declspec(noinline) const Image *__cdecl Rva005F0318Get(void *plot) {
    return StrategicInGameUI::GetSelectionPortrait((const Rva005D23BBSelection *)plot);
}

namespace StrategicInGameUI {
// WorldBuilder lines 372: &buildPlot == &GetBuildPlot(). Retail's 128-byte
// RET4 body ignores the asserted reference, updates the two clip images and
// refreshes the page when this slot is selected. Empty plots use the rowed
// portrait thunk, rather than the mispaired Observable template.
void RegionDetailsStructuresPage::Impl::Icon::OnBuildPlotBuildingChanged(LivingWorldBuildPlot &buildPlot) {
    BuildPlot *plot=getBuildPlot();
    const Image *image=plot->building ? StrategicInGameUI::GetButtonImage(plot->building) : Rva005F0318Get(plot);
    StructureIconSlot *clip=(StructureIconSlot *)((Rva005E2138 *)this)->GetBuildPlot();
    clip->SetImage(image);
    const Image *typeImage=Rva005F0220Get((Rva005F0220In *)getBuildPlot());
    clip=(StructureIconSlot *)((Rva005E2138 *)this)->GetBuildPlot();
    clip->SetBuildingTypeImage(typeImage);
    if(owner->selected==index) ((Rva005E261C *)owner)->rva005E261C();
}
}

// Page Impl constructor, native 0x005E2B45..0x005E2C9D (344B, RET10), called
// by the page ctor 0x005E2C9D with this, two pointer words and the context
// (pin spelling). Target facts: base movie clip built with min(plot count, the
// .rdata 4 at 0x00BC6C20) and the .data word 0x00E066A4; vtable 0x00C77B2C;
// fields +8 page, +C region, +10 observer, +14 counted-icon vector (empty base
// ctor 0x00211E58), +20/+24 = -1, +28 counted ref (EH state), +2C flag. Icons
// are built per clip slot (0x005F05D7) after reserve 0x005E2896; the slot whose
// plot equals context.page becomes +24. A non-empty fortress portrait sets the
// clip's portrait images and flag. WorldBuilder 15F3100 is the debug twin
// (same order, std::min over a global const). Field names are TU-local roles.
namespace StrategicInGameUI {
static const int kMaxStructureIconSlots = 4;
RegionDetailsStructuresPage::Impl::Impl(void *page, void *level, void *name, const PageContext &context)
 : StrategicHUD::RegionDetailsStructuresMovieClip((int)level, *(const AsciiString *)name,
     _STL::min((int)((Region *)context.region)->plots.size(), kMaxStructureIconSlots), g_rva00E066A4StructuresClipArg),
   page(page), region((Region *)context.region), observer(context.owner), selected(-1), pendingSelection(-1), flag(false)
{
 int count = ((const Rva005ED291 *)this)->rva005F05D7();
 ((Rva005E2896Vector *)&icons)->reserve(count);
 for (int i = 0; i < count; ++i) {
  Rva005E2B0EElement icon(new Icon(*this, i));
  icons.push_back(icon);
  if (((Icon *)icon.pointer)->getBuildPlot() == context.page)
   pendingSelection = i;
 }
 const Image *portrait = ((LivingWorldRegion *)region)->GetFortressPortrait();
 if (portrait) {
  ((Rva005F09E7 *)this)->rva005F09E7(portrait);
  ((Rva005F09EF *)this)->rva005F09EF(Rva005F01B8Get(1));
  ((Rva005F09DF *)this)->rva005F09DF(true);
 }
}
}

// Page Impl vtable 0x00C77B2C slot 1, native 0x005E2644..0x005E270E (202B,
// RET0); WorldBuilder 15F3AB0 is the debug twin. After the movie clip base's
// empty slot-1 hook (shared RET 0x000B3FD0, the sibling slot-2 body
// Rva005E21C2Wrap.cpp's spelling), the page builds its counted fortress help
// once from the region's fortress display name and description, then hands
// the counted reference (+0x28) to the observer at +0x10 through the rowed
// 4-byte slot-0 forwarder 0x001FF3A9. The help/counted-reference views are
// the ones StrategicInGameUIBuildQueueIconSelect.cpp uses for the same
// pattern; the slot name is TU-local.
class __declspec(novtable) Rva005398CDRefCounted {
public:
 Rva005398CDRefCounted() : m_refCount(0) {}
 virtual ~Rva005398CDRefCounted(); int m_refCount;
};
class InGameSimpleHelp : public Rva005398CDRefCounted {
public:
 class Impl;
 InGameSimpleHelp(const UnicodeString &,const UnicodeString &);
 virtual ~InGameSimpleHelp();
private: Impl *m_impl;
};
class Rva002BED91 { public: TargetRef00217D4C *m_ptr; void set(TargetRef00217D4C *); };
struct TreeHintRef00217D4C;
class Rva001FF3A9 { public: void rva001FF3A9(const TreeHintRef00217D4C &); };
#include "../../../../Include/Common/Rva000B3FD0Empty.h"
namespace StrategicInGameUI {
void RegionDetailsStructuresPage::Impl::slot01()
{
 ((Rva000B3FD0Empty *)this)->rva000B3FD0Empty();
 if (!current.pointer)
  ((Rva002BED91 *)&current)->set((TargetRef00217D4C *)new InGameSimpleHelp(((LivingWorldRegion *)region)->GetFortressDisplayName(), ((LivingWorldRegion *)region)->GetFortressDisplayDescription()));
 ((Rva001FF3A9 *)observer)->rva001FF3A9(*(const TreeHintRef00217D4C *)&current);
}
}

// Page Impl vftable 0x00C77B2C: slot 0 is the scalar deleting dtor 0x005E2AF2, whose dtor call is
// 0x005E29CD; slots 2-4 are the rowed bodies 0x005E21C2, 0x005E218F and 0x005E219D.
#pragma comment(linker, "/alternatename:??1Impl@RegionDetailsStructuresPage@StrategicInGameUI@@UAE@XZ=??1Rva005E29CD@@UAE@XZ")
#pragma comment(linker, "/alternatename:?slot02@Impl@RegionDetailsStructuresPage@StrategicInGameUI@@UAEXXZ=?rva005E21C2@Rva005E21C2@@QAEXXZ")
#pragma comment(linker, "/alternatename:?slot03@Impl@RegionDetailsStructuresPage@StrategicInGameUI@@UAEXXZ=?rva005E218F@Rva005E218F@@UAEXXZ")
#pragma comment(linker, "/alternatename:?slot04@Impl@RegionDetailsStructuresPage@StrategicInGameUI@@UAEXXZ=?rva005E219D@Rva005E218F@@UAEXXZ")
