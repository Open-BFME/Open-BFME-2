// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// cl: /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc
// stlport
// AddUpgradeIcons: WB 1627540 names ArmyUnitIcon and this source (line189).
// Native5F4917..5F49F0 is the complete217-byte RET0 body. Unit+8,
// clip+C and upgrade list+10 agree with the factory and DoUpdate siblings.
// Unit upgrade flags+10 and template flags+404 have32 unsigned words;
// UpgradeTemplate image+90 is accessed only after a successful lookup.
// The unsigned bit test and retained unit pointer reproduce every native byte.
// List append uses the existing4-byte storage-ABI provider at2E01C6 through
// its already pinned pointer spelling; this does not assert science semantics
// or introduce another typed fold. Views describe accessed fields only.
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
namespace _STL {
template<unsigned int N> struct _Base_bitset {
 unsigned int words[N];
 bool _M_is_any() const;
 __forceinline bool test(unsigned int bit) const { return (words[bit >> 5] & (1U << (bit & 31))) != 0; }
};
}
class Rva00406F9C { public: bool rva00406F9C(const void *); };
struct UnitView { int unknown; AsciiString name; int unknown08; int rank; _STL::_Base_bitset<32> upgrades; char unknown90[0xB8-0x90]; int flagB8,flagBC,unknownC0; unsigned char valueC4; };
class ThingTemplate;
struct TemplateView { char unknown00[0x404]; _STL::_Base_bitset<32> upgrades; char unknown484[0x5C4-0x484]; int tooltip; };
#include "../../../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;
class UpgradeTemplate;
#include "../../../../Include/Common/Upgrade.h"
extern UpgradeCenter *TheUpgradeCenter;
class Image;
struct UpgradeView { char unknown00[0x90]; const Image *image; };
class AptMovieClipFrame;
namespace StrategicHUD { class ArmyUnitIconMovieClip { public: ArmyUnitIconMovieClip(AptMovieClipFrame *); void SetUpgradeIconImage(int,const Image *); private: char opaque[0x50]; }; class ArmyMemberIconMovieClip { public: void rva005FC9E0(const Image *); }; }
// Only the existing four-byte storage ABI is used; upgrade IDs do not
// acquire ScienceType semantics by calling this rowed vector provider.
enum ScienceType { SCIENCE_INVALID = -1 };
namespace _STL {
template <> void vector<ScienceType, allocator<ScienceType> >::push_back(const ScienceType &);
}
struct UnitUpgradeList {
 int *begin,*end,*capacity;
 __forceinline unsigned size() const { return end-begin; }
 __forceinline void push_back(int &id) { reinterpret_cast<_STL::vector<ScienceType> *>(this)->push_back(reinterpret_cast<const ScienceType &>(id)); }
};
struct TreeHintRef00217D4C;
class Rva005F41AF { public: virtual TreeHintRef00217D4C CreateMovieClip(AptMovieClipFrame *); virtual void DoUpdate(); void rva005F41AF(); };
struct UnitClipHolder { void *p; __forceinline void *get() const { return p; } __forceinline bool IsBound() const { return p!=0; } };
namespace StrategicInGameUI {
class ArmyUnitIcon : public virtual Rva005F41AF {
public: virtual TreeHintRef00217D4C CreateMovieClip(AptMovieClipFrame *); virtual void DoUpdate(); void AddUpgradeIcons();
private: int owner; UnitView *unit; UnitClipHolder clip; UnitUpgradeList upgrades; int unknown1c;
};
}
void StrategicInGameUI::ArmyUnitIcon::AddUpgradeIcons() {
 UnitView *entry = unit;
 const _STL::_Base_bitset<32> *bits = &entry->upgrades;
 if (!bits->_M_is_any()) return;
 const AsciiString &name = entry->name;
 if (((const StringBase<char> *)&name)->isEmpty()) return;
 const ThingTemplate *found = TheThingFactory->findTemplate(name);
 if (!found) return;
 const _STL::_Base_bitset<32> *available = &((const TemplateView *)found)->upgrades;
 if (!((Rva00406F9C *)bits)->rva00406F9C(available)) return;
 for (int id=0; id<1024; ++id) {
  if (bits->test(id) && available->test(id)) {
   const UpgradeTemplate *upgrade = TheUpgradeCenter->rva0026EEA0(id);
   if (!upgrade) continue;
   const Image *image = ((const UpgradeView *)upgrade)->image;
   if (!image) continue;
   ((StrategicHUD::ArmyUnitIconMovieClip *)clip.get())->SetUpgradeIconImage(upgrades.size(), image);
   upgrades.push_back(id);
   if (upgrades.size() >= 4) break;
  }
 }
}

struct TargetRef00217D4C { void *vtable; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
 __declspec(dllimport) __forceinline TreeHintRef00217D4C(TargetRef00217D4C *p):m_ptr(p) { if(m_ptr) ++m_ptr->references; }
 __forceinline TreeHintRef00217D4C(const TreeHintRef00217D4C &other):m_ptr(other.m_ptr) { if(m_ptr) ++m_ptr->references; }
 ~TreeHintRef00217D4C() { if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
 TargetRef00217D4C *m_ptr;
};
#include "../../../../Include/Common/Rva002BED91.h"
#include "../../../../Include/GameClient/Rva005FC9F0.h"
#include "../../../../Include/GameClient/Rva0037E07C.h"
struct StrategicButtonImageView; struct Rva005F01D6In;
namespace StrategicInGameUI { const Image *GetButtonImage(const StrategicButtonImageView *,int); }
const Image *Rva005F01D6Get(Rva005F01D6In *);
// WB1626A60 names CreateMovieClip (this file, line103). Retail5F49F0
// is the complete171-byte counted-return factory; as an override of the
// virtual base's slot 2 its receiver is that base (+0x20), which is why the
// owner, unit and clip read at -1C/-18/-14. Its vtordisp thunk 0x005F4A9B is
// emitted by StrategicInGameUIArmyUnitIconLifetime.cpp. Allocates50 bytes via
// the established414-byte clip constructor, sets portrait/type/count through
// owned providers, then calls AddUpgradeIcons. Capturing each clip before its
// argument calls preserves retail evaluation order; the counted return inlines
// the reference increment and hidden result.
TreeHintRef00217D4C StrategicInGameUI::ArmyUnitIcon::CreateMovieClip(AptMovieClipFrame *frame) {
 TargetRef00217D4C *made = (TargetRef00217D4C *)new StrategicHUD::ArmyUnitIconMovieClip(frame);
 Rva002BED91 *holder = (Rva002BED91 *)&clip;
 holder->set(made);
 int player = *(int *)((char *)owner+0x54);
 StrategicHUD::ArmyMemberIconMovieClip *portrait = (StrategicHUD::ArmyMemberIconMovieClip *)*(void **)holder;
 portrait->rva005FC9E0(StrategicInGameUI::GetButtonImage((const StrategicButtonImageView *)unit,player));
 Rva005FC9F0 *type = (Rva005FC9F0 *)*(void **)holder;
 type->rva005FC9E8(Rva005F01D6Get((Rva005F01D6In *)unit));
 Rva005FC9F0 *quantity = (Rva005FC9F0 *)*(void **)holder;
 quantity->rva005FC9F0(((Rva0037E07C *)unit)->rva0037E07C());
 AddUpgradeIcons();
 return TreeHintRef00217D4C(*(TargetRef00217D4C **)holder);
}

class Rva001524CA { public: TreeHintRef00217D4C rva001524CA(); };
#include "../../../../Include/Common/Rva0037DCA5.h"
class InGameSimpleHelp {
public:
    InGameSimpleHelp(const UnicodeString &title, const UnicodeString &text);
private:
    char m_opaque[12];
};
// Complete171-byte help factory5F4254..5F42FF RET4. The secondary
// receiver accesses unit-C and owner-10; fallback consults vbptr-14 and
// calls the independently rowed18-byte empty-help provider1524CA. Original
// virtual method spelling is still unknown. A name accessor reproduces the
// retail retained field pointer; title comes from40C65D for owner playerID54,
// description from template40. Allocates the measured12-byte InGameSimpleHelp
// and returns the same counted-reference ABI used by the clip factory.
// ArmyHeroIcon's slot-3 override (its table C79468 reaches it through the
// vtordisp thunk 0x005F43A4 that ArmyHeroIconCtor.cpp emits). The receiver is
// the virtual base (+0x14), so this flat view keeps the base-relative reads.
namespace StrategicInGameUI {
class ArmyHeroIcon {
public:
    virtual TreeHintRef00217D4C rva005F4254();
    __forceinline const AsciiString &getName() const { return (*(UnitView **)((char *)this-0xc))->name; }
};
}
TreeHintRef00217D4C StrategicInGameUI::ArmyHeroIcon::rva005F4254()
{
    const AsciiString *key = &getName();
    if (!((const StringBase<char> *)key)->isEmpty()) {
        const ThingTemplate *found = TheThingFactory->findTemplate(*key);
        if (found) {
            void *owner = *(void **)((char *)this - 0x10);
            UnicodeString *title = (UnicodeString *)(*(Rva0037DCA5 **)((char *)this - 0xc))->GetDisplayNameStrategicGame(*(int *)((char *)owner + 0x54));
            if (!title->isEmpty()) {
                const UnicodeString &text = *(const UnicodeString *)((char *)found + 0x40);
                return TreeHintRef00217D4C((TargetRef00217D4C *)new InGameSimpleHelp(*title, text));
            }
        }
    }
    int offset = (*(int **)((char *)this - 0x14))[1];
    return ((Rva001524CA *)((char *)this + offset - 0x14))->rva001524CA();
}

#include "../../../../Include/GameClient/Rva005FC70A.h"
#include "../../../../Include/GameClient/Rva005FC71E.h"
#include "../../../../Include/GameClient/Rva005FC73BPtrChaseField.h"
class Rva005FD034 {public:void rva005FD034(int);};
class Rva005FD04B {public:void rva005FD04B(unsigned char);};
class Rva002A98A7DwordField {public:int get()const;};
struct RGBColor;
#include "../../../../Include/GameClient/Mouse.h"
extern Mouse *TheMouse;
#include "../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
namespace StrategicInGameUI { UnicodeString GetTooltipText(int); }

// WB1627180 identifies DoUpdate; retail5F4488..5F45AF is the complete295B body.
// Virtual-base receiver is icon+20, with unit8/clipC/list10. Native loads
// rankC, flagsB8/BC and valueC4, then template tooltip5C4 and upgrade label28.
// Named flag and final buffer values preserve retail register lifetimes.
void StrategicInGameUI::ArmyUnitIcon::DoUpdate() {
 Rva005F41AF::rva005F41AF();
 if(!clip.IsBound()) return;
 ((Rva005FD034 *)clip.get())->rva005FD034(unit->rank);
 int state=unit->flagB8;
 ((Rva005FC70A *)clip.get())->rva005FC70A(state!=0);
 unsigned char value=unit->valueC4;
 ((Rva005FC71E *)clip.get())->rva005FC71E(value);
 ((Rva005FD04B *)clip.get())->rva005FD04B(unit->flagBC!=0);
 if(((Rva005FC73BPtrChaseField *)clip.get())->get()) {
  const AsciiString *name=&unit->name;
  if(!((const StringBase<char> *)name)->isEmpty()) {
   TemplateView *thingTemplate=(TemplateView *)TheThingFactory->findTemplate(*name);
   if(thingTemplate) { int tooltip=thingTemplate->tooltip; TheMouse->rva001EEA6D(GetTooltipText(tooltip),-1,0,1.0f); }
  }
 }
 int index=((Rva002A98A7DwordField *)clip.get())->get();
 if(index<0) return;
 if((unsigned)index>=upgrades.size()) return;
 {
  int *first=upgrades.begin;
  const UpgradeTemplate *upgradeTemplate=TheUpgradeCenter->rva0026EEA0(first[index]);
  if(!upgradeTemplate) return;
  TheMouse->rva001EEA6D(TheGameText->fetch(*(const AsciiString *)((const char *)upgradeTemplate+0x28),0),-1,0,1.0f);
 }
}
