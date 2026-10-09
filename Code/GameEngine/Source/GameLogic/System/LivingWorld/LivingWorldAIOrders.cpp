// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii
// stlport
// Native4FB7B2..4FB8A8 supplies all246B, owner0 and20B records at80.
// WB131A480 names neighbouring SubmitOrders and establishes LivingWorldAI
// receiver identity; this member's original name remains unproven.
// Constructor4FB3F2 establishes134B receiver extent; remaining state is opaque.
// Native skip predicate differs from SubmitOrders, and this path clears80.
// The ordinary raw-pointer dispatch overload is P1's certified25B relocation
// twin at2B4076; CanMoveArmyMember retains its canonical struct Army spelling.
#include <vector>
#include "ascii_string.h"
struct Rva005B09D8Record {int words[5];};
class Rva005B129FVector {public: Rva005B09D8Record *erase(Rva005B09D8Record*,Rva005B09D8Record*); __forceinline void clear() {erase(first,finish);} Rva005B09D8Record *first,*finish,*limit;};
class Rva0020E89C;
class Rva0020EAF6View {public:Rva0020E89C *rva0020EAF6(int);};
struct LivingWorldArmy;
class LivingWorldLogic {public:
 bool CanMoveArmyMember(LivingWorldArmy*,int,int);
 __forceinline Rva0020EAF6View *getRegions() const {return (Rva0020EAF6View*)regions;}
 char unknown[0xB0];void *regions;
};
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002E0A9FElem {public:int rva002E0A9F(void*);};
class Rva00318F42 {public:bool rva00318F42();};
class Rva002B4076 {public:void rva002B4076(void*,int,void*);};
class Rva002B2702 {public:void rva002B2702(void*,void*,int);};
class LivingWorldAI {public:void rva004FB7B2();private:
 Rva002E0A9FElem *owner;char unknown4[0x80-4];
 _STL::vector<Rva005B09D8Record> orders80;
 char unknown8C[0x134-0x8C];
};
void LivingWorldAI::rva004FB7B2() {
 unsigned n=orders80.size();
 for(unsigned i=0;i<n;++i) {
  LivingWorldArmy *army=(LivingWorldArmy*)owner->rva002E0A9F((void*)orders80[i].words[0]);
  if(army && (((Rva00318F42*)army)->rva00318F42() || !((AsciiString*)((char*)army+0x18))->isEmpty()))continue;
  if(orders80[i].words[2]) {
   if(TheLivingWorldLogic->CanMoveArmyMember(army,orders80[i].words[3],owner->rva002E0A9F((void*)orders80[i].words[2])))
    ((Rva002B4076*)TheLivingWorldLogic)->rva002B4076((void*)army,orders80[i].words[3],(void*)owner->rva002E0A9F((void*)orders80[i].words[2]));
  } else ((Rva002B2702*)TheLivingWorldLogic)->rva002B2702(army,TheLivingWorldLogic->getRegions()->rva0020EAF6(orders80[i].words[4]),1);
 }
 ((Rva005B129FVector*)&orders80)->clear();
}
