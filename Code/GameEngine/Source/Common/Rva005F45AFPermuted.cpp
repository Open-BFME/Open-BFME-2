// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
//
// ?appendUpgradeList@@YAXAAVUnicodeString@@PBUUpgradeRecordView@@@Z, retail 0x005f45af, 353 bytes. Banked partial (score 0.9886685552407932) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
#include "ascii_string.h"
#include "unicode_string.h"
#include <bitset>
template<> bool _STL::_Base_bitset<24>::_M_is_any() const;
#include "../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
class UpgradeTemplate;
#include "../../Include/Common/Upgrade.h"
extern UpgradeCenter *TheUpgradeCenter;
struct UpgradeLabelView { char pad[0x2c]; AsciiString label; };
struct UpgradeRecordView { char pad[0x10]; _STL::_Base_bitset<32> flags; };
static __declspec(noinline) void appendUpgradeList(UnicodeString &out,const UpgradeRecordView *record)
{
 const _STL::_Base_bitset<32> &flags=record->flags;
 if(flags._M_is_any()) {
  UnicodeString names;
  UnicodeString separator=TheGameText->fetch("LW:ListSeparator");
  for(int i=0;i<1024;++i) {
   if(flags._M_w[(unsigned int)i>>5] & (1UL<<(i&31))) {
    const UpgradeTemplate *upgrade=TheUpgradeCenter->rva0026EEA0(i);
    if(upgrade) {
     const AsciiString &label=((const UpgradeLabelView*)upgrade)->label;
     if(!label.isEmpty()) {
      if(*(void**)&names && *(unsigned short*)((char*)*(void**)&names+4)!=0) names.concat(separator);
      names.concat(TheGameText->fetch(label));
     }
    }
   }
  }
  if(*(void**)&names && *(unsigned short*)((char*)*(void**)&names+4)!=0) {
   UnicodeString title=TheGameText->fetch("LW:UnitUpgradeListHeader");
   title.format(&title,names.str());
   out.concat((const unsigned short*)L"\n\n");
   out.concat(title);
  }
 }
}
void useUpgradeList(UnicodeString &out,const UpgradeRecordView *record){appendUpgradeList(out,record);}

// Retail 0x005F4710, 268 bytes: help factory abutting appendUpgradeList.
// Same receiver family as rowed Rva005F4254::rva005F4254 (entry-18,
// owner-1C, fallback receiver-20 instead of -0xC/-0x10/-0x14), plus a
// description tail: GetArmySummaryEntryDescription result, newline plus the
// template text at +0x40 when non-empty, then the same-TU appendUpgradeList.
#include "../../Include/Common/Rva0037DCA5.h"
UnicodeString GetArmySummaryEntryDescription(Rva0037DCA5 *entry,int rule);
class InGameSimpleHelp {
public:
 InGameSimpleHelp(const UnicodeString &title,const UnicodeString &text);
private:
 char m_opaque[12];
};
struct EntryNameView4710 { int unknown; AsciiString name; };
class ThingTemplate;
#include "../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva001524CA { public: TreeHintRef00217D4C rva001524CA(); };
// StrategicInGameUI::ArmyUnitIcon's slot-3 override of its virtual base
// (C794AC slot 3 reaches it through the vtordisp thunk 0x005F4889, which
// StrategicInGameUIArmyUnitIconLifetime.cpp emits). Its receiver is that
// virtual-base subobject (+0x20), so this flat view keeps retail's
// base-relative reads: owner -1C, unit -18, vbptr -20; the fallback calls the
// base's own slot-3 body 0x001524CA through the vbptr.
namespace StrategicInGameUI {
class ArmyUnitIcon {
public:
 virtual TreeHintRef00217D4C rva005F4710();
 __forceinline const AsciiString &getName() const { return (*(EntryNameView4710 **)((char *)this-0x18))->name; }
};
}
TreeHintRef00217D4C StrategicInGameUI::ArmyUnitIcon::rva005F4710()
{
 const AsciiString *key=&getName();
 if(!((const StringBase<char> *)key)->isEmpty()) {
  const ThingTemplate *found=TheThingFactory->findTemplate(*key);
  if(found) {
   void *owner=*(void **)((char *)this-0x1c);
   UnicodeString *title=(UnicodeString *)(*(Rva0037DCA5 **)((char *)this-0x18))->GetDisplayNameStrategicGame(*(int *)((char *)owner+0x54));
   if(!title->isEmpty()) {
    UnicodeString desc=GetArmySummaryEntryDescription(*(Rva0037DCA5 **)((char *)this-0x18),0);
    const UnicodeString &text=*(const UnicodeString *)((char *)found+0x40);
    if(!text.isEmpty()) {
     desc.concat((const unsigned short *)L"\n");
     desc.concat(text);
    }
    appendUpgradeList(desc,(const UpgradeRecordView *)*(void **)((char *)this-0x18));
    return TreeHintRef00217D4C((TargetRef00217D4C *)new InGameSimpleHelp(*title,desc));
   }
  }
 }
 int offset=(*(int **)((char *)this-0x20))[1];
 return ((Rva001524CA *)((char *)this+offset-0x20))->rva001524CA();
}
