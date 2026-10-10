// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// ?ResolveRegionOwnership@MyResolveRegionOwnershipChecklistItem@Impl@ResolveBattlesBehavior@StrategicInGameUI@@UAEXAAVRegionAwardDispute@@@Z @0x00576834 151B.
// Native 576834..5768CB RET4 (vtable 0x0086E7CC slot): once the dispute is unresolved and the viewer is the resolver, look up the HUD panel
// through the owner UI holder and push a new 0x005765D1 command object into the +0x40 list. Names are address-derived;
// owner/ui/panel views and the dispute resolved flag at +0x1C are target-read prefixes, not recovered classes.
// Codegen: the owner receiver must be a same-valued PHI ((owner?owner:owner)->...) for the two owner->player / owner->ui reads: it
// closes the native EBX/EDI role swap across the dispute and owner homes (plain owner-> gives 0.89).
#include <stdlib.h>
namespace _STL { void __cdecl free(void *); }
#define free _STL::free
#include <vector>
#undef free
class GameMessage;
namespace StrategicInGameUI { class ResolveBattlesBehavior { public: class Impl; }; }
class StrategicInGameUI::ResolveBattlesBehavior::Impl { public: class MyResolveRegionOwnershipChecklistItem; };
class Object;
class Rva00575674 { public: void rva00575674(Object *); };
class RegionAwardDispute { public: int GetResolvableBy(); };
class Rva00328A83PtrChaseField { public: int get() const; };
class Rva0042D6BAPtrChaseField { public: int get() const; };
class Rva0057C22FByteChaseField { public: unsigned char get() const; };
class Rva005765D1 {
public:
 Rva005765D1(void *,int,int);
 virtual ~Rva005765D1();
 char storage[8];
};
struct ResolveOwnershipDisputeView { char unknown[0x1C]; bool resolved; bool IsResolved() const { return resolved; } };
struct ResolveOwnershipPlayerView { char unknown[0x14]; int id; };
struct ResolveOwnershipImplView {
 char unknown00[0x10];
 void *ui;
 void *unknown14;
 ResolveOwnershipPlayerView *player;
};
struct ResolveOwnershipUIHolder {
 void *unknown00;
 Rva00328A83PtrChaseField *impl;
};
class StrategicInGameUI::ResolveBattlesBehavior::Impl::MyResolveRegionOwnershipChecklistItem {
public:
 virtual void ResolveRegionOwnership(RegionAwardDispute &);
 char unknown04[0x10];
 ResolveOwnershipImplView *owner;
};
// ?ResolveRegionOwnership@MyResolveRegionOwnershipChecklistItem@Impl@ResolveBattlesBehavior@StrategicInGameUI@@UAEXAAVRegionAwardDispute@@@Z
void StrategicInGameUI::ResolveBattlesBehavior::Impl::MyResolveRegionOwnershipChecklistItem::ResolveRegionOwnership(RegionAwardDispute &dispute)
{
 if(reinterpret_cast<ResolveOwnershipDisputeView *>(&dispute)->IsResolved()) return;
 int playerId = (owner?owner:owner)->player->id;
 if(dispute.GetResolvableBy()!=playerId) return;
 int hud=reinterpret_cast<ResolveOwnershipUIHolder *>((owner?owner:owner)->ui)->impl->get();
 int panel=reinterpret_cast<Rva0042D6BAPtrChaseField *>(hud)->get();
 if(panel && !reinterpret_cast<Rva0057C22FByteChaseField *>(panel)->get())
  reinterpret_cast<Rva00575674 *>(reinterpret_cast<char *>(owner)+0x40)->rva00575674(
   reinterpret_cast<Object *>(new Rva005765D1(owner,panel,reinterpret_cast<int>(&dispute))));
}
