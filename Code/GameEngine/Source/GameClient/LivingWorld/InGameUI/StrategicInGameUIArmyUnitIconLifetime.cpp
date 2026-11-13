// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native constructor005F481C..005F4879 and destructor005F4891..005F48EC
// share the eight-slot C794AC interface. Its update thunk005F4881 reaches
// WB-named ArmyUnitIcon::DoUpdate005F4488; the existing AddUpgradeIcons and
// movie-clip factory corroborate owner04/unit08/clip0C/upgrade IDs10.
// C794CC is its two-word vbtable, with the shared12-byte base at20 and
// compiler vtordisp at1C. The base's existing78B constructor and54B
// destructor establish Rva005F4179; only the observed interface is declared.
// Slots without recovered spellings remain declarations; the pointer argument
// spellings are ABI views, not recovered original types. sizeof is44.
// A real vector<int> owns the upgrade IDs. The established30830 game-free
// declaration preserves the native state0 cleanup of the counted clip during
// vector deallocation. No byte lift or new address pin is used.
// STLport4.5.3 comes from this repo's vendor tree with its bfmealloc shim;
// the pinned BFME1 cee35b7d supplies the MSVC7.1 toolchain inputs. Layout and
// class relationship come from retail stores, vtables and the already named
// ArmyUnitIcon siblings rather than an application-source donor.
#include <cstdlib>
void __cdecl Rva00030830FreeAllocation(void *);
#include <vector>
namespace _STL {
template<> inline void allocator<int>::deallocate(int *__p, size_type) const
{
	if (__p != 0) Rva00030830FreeAllocation((void *)__p);
}
}
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C;
class AptMovieClipFrame;
#include "../../../../Include/Common/Rva005F3F9A.h"
class Rva005F3F14 { public: void rva005F3F14(); };
class Rva005F4179 {
public:
 Rva005F4179(void *);
 virtual ~Rva005F4179();
 virtual void slot01()=0;
 virtual TreeHintRef00217D4C CreateMovieClip(AptMovieClipFrame *)=0;
 virtual TreeHintRef00217D4C rva005F4710();
 virtual void DoUpdate();
 // Slots 5-7 of retail's table 0x00C794AC: the shared empty body 0x000B3FD0
 // and the two +8 forwarders 0x005F3FF4 / 0x005F3F6B (rowed as
 // Rva005F3FF4::rva005F3FF4 and Rva005F3F6B::rva005F3F6B).
 virtual void slot05() {}
 virtual void slot06() { ((Rva005F3F9A *)leaf)->rva005F3F9A(); }
 virtual void slot07() { ((Rva005F3F14 *)leaf)->rva005F3F14(); }
private:int count;void *leaf;
};
struct ClipRef {
 ClipRef():ptr(0){}
 ~ClipRef(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
 TargetRef00217D4C *ptr;
};
struct UnitView;
namespace StrategicInGameUI {
class ArmyUnitIcon:public virtual Rva005F4179 {
public:
 ArmyUnitIcon(void *owner,void *clip,UnitView *unit);
 virtual ~ArmyUnitIcon();
 virtual TreeHintRef00217D4C CreateMovieClip(AptMovieClipFrame *);
 virtual TreeHintRef00217D4C rva005F4710();
 virtual void DoUpdate();
private:
 void *m_owner;
 UnitView *m_unit;
 ClipRef m_clip;
 _STL::vector<int> m_upgrades;
};
}
StrategicInGameUI::ArmyUnitIcon::ArmyUnitIcon(void *owner,void *clip,UnitView *unit)
 :Rva005F4179(clip),m_owner(owner),m_unit(unit){}
StrategicInGameUI::ArmyUnitIcon::~ArmyUnitIcon(){}
typedef char ArmyUnitIconHas44Bytes[sizeof(StrategicInGameUI::ArmyUnitIcon)==44 ? 1 : -1];

