// ?Register@AIUpgradeScienceBuilder@@QAEXPAVObject@@PAX@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /MD /EHs /arch:SSE /G7 /Oi /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/Libraries/Include
// Banked compiler trial for native 00597C58..00597E30 RET8 (472 bytes).
// WB 01532AD0 names Register; second argument type unresolved (one unused stack word).
// Accessed offsets and record extents come from native and rowed constructor siblings.
// Typed pointer vector element choices are structural inferences; their fold pins
// are not admitted. This bank does not assert a matching body or complete class contract.
#include "Lib/Coord3D.h"
#include <stddef.h>
#include <string.h>
class Player; class AsciiString; class ModuleData;
template<class C> class StringBase { public: void set(const StringBase &); void *data; };
class Object { public: const AsciiString *rva00290E67() const; char pad00[0x38]; Coord3D position; float angle; char pad48[0x74-0x48]; unsigned id; char pad78[0x280-0x78]; float field280; float getField280() const { return field280; } };
class UpgradeTemplate { public: unsigned rva0026EF50(Player *,Object *) const; char pad00[8]; StringBase<char> name; char pad0C[0x98-0x0c]; int heuristic; };
class CommandButton { public: void *rva0035B570() const; char pad00[0x14]; int command; char pad18[0x24-0x18]; UpgradeTemplate *upgrade; };
class CommandSet { public: const CommandButton *getCommandButton(int) const; };
class Rva0031D5F8 { public: void *rva0031D5F8(const AsciiString *); };
class ControlBar; extern ControlBar *TheControlBar;
struct ScienceBuildTemplateView { char pad00[0x64]; StringBase<char> name; char pad68[0x116-0x68]; unsigned char bit116; char pad117[4]; unsigned char bit11B; };
class Rva0055B0CC { public: virtual ~Rva0055B0CC(); float delay; unsigned id; StringBase<char> name; char pad10[0x21-0x10]; bool registered; char pad22[0x2c-0x22]; };
class AIUpgrade : public Rva0055B0CC { public: unsigned cost; const CommandButton *command; };
class Rva005970ED : public AIUpgrade { public: Rva005970ED(); void rva0059717F(int); char pad34[0x44-0x34]; };
class Rva005DAAB6 : public Rva0055B0CC { public: Rva005DAAB6(); bool used; Coord3D position; float angle; const CommandButton *command; };
// ScienceType preserves the existing generic 4-byte vector provider ABI only;
// this vector stores the object identifier field and does not establish ScienceType semantics.
enum ScienceType { SCIENCE_DUMMY=0 };
namespace _STL { template<class T> class allocator {}; template<class T,class A=allocator<T> > class vector { public: void push_back(const T &); T *begin,*end,*limit; }; }
class AIUpgradeScienceBuilder { char pad00[0x14]; Player *owner; _STL::vector<ScienceType> objects; _STL::vector<AIUpgrade *> upgrades; _STL::vector<Rva0055B0CC *> buildings; public: bool rva0059764A(Object *); void Register(Object *,void *); };
void AIUpgradeScienceBuilder::Register(Object *object,void *)
{
 if (rva0059764A(object)) return;
 CommandSet *commands=(CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(object->rva00290E67());
 if (object->getField280() < 0.0f) {
  if (commands) for (int i=0;i<32;++i) {
   const CommandButton *button=commands->getCommandButton(i);
   Rva0055B0CC *item;
   if (!button) continue;
   UpgradeTemplate *upgrade=button->upgrade;
   if (upgrade) {
    unsigned cost=upgrade->rva0026EF50(owner,object);
    Rva005970ED *record=new Rva005970ED;
    item=record;
    record->cost=cost; record->id=object->id; record->command=button;
    record->name.set(upgrade->name); record->rva0059717F(upgrade->heuristic);
    upgrades.push_back((AIUpgrade *const &)item);
   } else if (button->command==1 && button->rva0035B570() &&
       !(((ScienceBuildTemplateView *)button->rva0035B570())->bit11B & 0x10) &&
       !(((ScienceBuildTemplateView *)button->rva0035B570())->bit116 & 0x40)) {
    Rva005DAAB6 *record=new Rva005DAAB6;
    item=record;
    record->command=button;
    record->name.set(((ScienceBuildTemplateView *)button->rva0035B570())->name);
    record->delay=-1.0f; record->position=object->position; memcpy(&record->angle,&object->angle,sizeof(float));
    record->id=object->id; record->registered=true;
    buildings.push_back(item);
   }
  }
 } else {
  unsigned id=object->id;
  objects.push_back((const ScienceType &)id);
 }
}
