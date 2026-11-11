// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native319EF9 Take-unit adapter and2B3DE4/2B4076 dispatch pair.
// WB131AA30 calls2B4076 after CanMoveArmyMember; native pointer+20 owner,
// summary+78, entry-ref+AC and target-id+B8 accesses establish these views.
// Rva-address names retain uncertainty about original private operation names.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
#include "../../Include/Common/ArmySummaryEntry.h"
class Rva004F6093Holder {
public:
 ArmySummaryEntry *entry;
 Rva004F6093Holder() : entry(0) {}
 Rva004F6093Holder(const Rva004F6093Holder &);
 ~Rva004F6093Holder() { if(entry)ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(static_cast<Rva0007DF07 *>(entry))); }
};
struct ArmySummaryEntryRef { Rva004F6093Holder holder; };
#include "../../Include/GameLogic/ArmySummary.h"
#include "../../Include/GameLogic/LivingWorldArmy.h"
// WorldBuilder MoveArmyMember, WB VA 0x00D90830 (callgraph lead, score 2.0).
static __declspec(noinline) void MoveArmyMember(LivingWorldArmy *source,int key,LivingWorldArmy *target) {
 ArmySummaryEntryRef entry=source->field78->GetEntry(key);
 if(entry.holder.entry) {
  if(entry.holder.entry->m_b8) {
   if(entry.holder.entry->m_b8==target->field20)entry.holder.entry->m_b8=0;
  } else entry.holder.entry->m_b8=source->field20;
  target->rva00319EF9(source,key);
 }
}
class Rva002B4076 { public:
 void rva002B4076(LivingWorldArmy *,int,LivingWorldArmy *);
 void rva002B4076(void *,int,void *);
};
void Rva002B4076::rva002B4076(LivingWorldArmy *source,int key,LivingWorldArmy *target) {
 MoveArmyMember(source,key,target);
}

struct Rva002B3E50Range { int *first,*finish,*limit; };
static __declspec(noinline) void rva002B3E50(Rva002B3E50Range *range,LivingWorldArmy *source,LivingWorldArmy *target) {
 int *end=range->finish;
 for(int *i=range->first;i!=end;++i)MoveArmyMember(source,*i,target);
}
class Rva002B2FCBElem { public: virtual void notify(int,int,int,int); };
class Rva002B6194List {
public:
 void forEach(void(Rva002B2FCBElem::*)(int,int,int,int),int,int,int,int);
};
class Rva002B6D85 {
public:
 void rva002B6D85(void *source,Rva002B3E50Range *first,void *target,Rva002B3E50Range *second);
private:
 char pad[0x7C];
 Rva002B6194List listeners;
};
void Rva002B6D85::rva002B6D85(void *source,Rva002B3E50Range *first,void *target,Rva002B3E50Range *second) {
 listeners.forEach(&Rva002B2FCBElem::notify,(int)source,(int)first,(int)target,(int)second);
 rva002B3E50(first,(LivingWorldArmy*)source,(LivingWorldArmy*)target);
 rva002B3E50(second,(LivingWorldArmy*)target,(LivingWorldArmy*)source);
}

// Neutral pointer ABI bridge for callers whose established army spelling is
// struct LivingWorldArmy. Both pointers retain the native source/target roles.
void Rva002B4076::rva002B4076(void *source,int key,void *target) {
 MoveArmyMember((LivingWorldArmy*)source,key,(LivingWorldArmy*)target);
}
