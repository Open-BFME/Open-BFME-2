// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/GameEngine/Include /I.
// Semantic donor: GeneralsMD BattlePlanUpdate.cpp::paralyzeTroop at BFME1
// 9cbfb551fe20dae985f91f2319d8997287b6a705. The donor name is not asserted
// as a target fact: native setBattlePlan 497AE8 supplies this callback address.
// Target boundary: preceding isTurretInNaturalPosition ends at4977B5;
// this callback's final RET is4977F7 and matched getActiveBattlePlan starts4977F8.
// Native callback reads two 28-byte KindOf masks at data54/70, frame50,
// returns int1, and uses the existing Thing query and Object disable providers.
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
template<int N> class BitFlags { public: unsigned int m_bits[7]; };
class Thing { public: bool isAnyKindOf(const BitFlags<69> &) const; };
enum DisabledType { DISABLED_PARALYZED=4 };
class Object { public: void setDisabledUntil(DisabledType,unsigned); };
struct BattlePlanParalyzeDataView {
 char pad[0x50];
 unsigned m_paralyzeFrames;
 BitFlags<69> m_validMemberKindOf,m_invalidMemberKindOf;
};
int Rva004977B5(Object *obj,void *userData) {
 const BattlePlanParalyzeDataView *data=(const BattlePlanParalyzeDataView *)userData;
 if (((Thing *)obj)->isAnyKindOf(data->m_validMemberKindOf)) {
  if (!((Thing *)obj)->isAnyKindOf(data->m_invalidMemberKindOf)) {
   obj->setDisabledUntil(DISABLED_PARALYZED,TheGameLogic->getFrame()+data->m_paralyzeFrames);
  }
 }
 return 1;
}
