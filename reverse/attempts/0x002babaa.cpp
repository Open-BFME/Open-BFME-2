// ?ExtractArmyDataFromSwapArmyMembersMessage@@YA_NPBVGameMessage@@PAHPAPAULivingWorldArmy@@PAUArmyMemberIDVector@@@Z
// partial score=1.0 date=2026-10-09
// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /I.
// stlport
// Bank-only context dependency: LivingWorldLogic.cpp at BFME2 f45b03792c.
// Artificial compiler caller below is SCRATCH ONLY, not a recovered function.
// This attempt may not be copied into Code without a real matching caller.
#include "Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldLogic.cpp"
// Scratch ABI view: use the already-rowed four-byte ScienceType vector
// providers. This is not a claim that army member IDs are sciences.
enum ScienceType;
namespace _STL {
template <> void vector<ScienceType, allocator<ScienceType> >::reserve(unsigned int);
template <> void vector<ScienceType, allocator<ScienceType> >::push_back(const ScienceType &);
template <> ScienceType *vector<ScienceType, allocator<ScienceType> >::erase(ScienceType *,ScienceType *);
}
struct ArmyMemberIDVector {
 int *begin, *end, *capacity;
 void clear(){ reinterpret_cast<_STL::vector<ScienceType> *>(this)->clear(); }
 void reserve(unsigned int n){reinterpret_cast<_STL::vector<ScienceType> *>(this)->reserve(n);}
 void push(const int &n){reinterpret_cast<_STL::vector<ScienceType> *>(this)->push_back(reinterpret_cast<const ScienceType &>(n));}
};
static __declspec(noinline) Bool ExtractArmyDataFromSwapArmyMembersMessage(const GameMessage *msg,Int *argIndex,LivingWorldArmy **army,ArmyMemberIDVector *ids)
{
 if(!getArmyFromMessage(army,msg,(*argIndex)++))return false;
 if(!validateMessageArgumentIndex(msg,*argIndex))return false;
 int count=msg->getArgument((*argIndex)++)->integer;
 if(count<0 || *argIndex+count>(int)msg->getArgumentCount())return false;
 ids->clear();
 ids->reserve(count);
 while(count>0){
  int entryID;
  if(!getArmySummaryEntryIDFromMessage(&entryID,msg,(*argIndex)++,*army))return false;
  ids->push(entryID);
  --count;
 }
 return true;
}
// Only a scratch compiler context; not a recovered caller.
Bool ScratchSwapParserContext(const GameMessage *msg,Int *index,LivingWorldArmy **army,ArmyMemberIDVector *ids){return ExtractArmyDataFromSwapArmyMembersMessage(msg,index,army,ids);}
