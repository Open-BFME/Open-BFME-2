// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native319EF9 Take-unit adapter and2B3DE4/2B4076 dispatch pair.
// WB131AA30 calls2B4076 after CanMoveArmyMember; native pointer+20 owner,
// summary+78, entry-ref+AC and target-id+B8 accesses establish these views.
// Rva-address names retain uncertainty about original private operation names.
struct TargetRef00217D4C { void *vtable; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class ArmySummaryEntry { public: char pad00[0xAC]; TargetRef00217D4C ref; int padB4; int targetB8; };
class Rva004F6093Holder {
public:
 ArmySummaryEntry *entry;
 Rva004F6093Holder() : entry(0) {}
 Rva004F6093Holder(const Rva004F6093Holder &);
 ~Rva004F6093Holder() { if(entry)ReleaseTreeHintRef00217D4C(&entry->ref); }
};
struct ArmySummaryEntryRef { Rva004F6093Holder holder; };
class ArmySummary { public: ArmySummaryEntryRef GetEntry(int); };
class LivingWorldArmy {
public:
 void rva00319EF9(LivingWorldArmy *source,int key);
 char pad00[0x20]; int owner20; char pad24[0x78-0x24]; ArmySummary *summary78;
};
static __declspec(noinline) void rva002B3DE4(LivingWorldArmy *source,int key,LivingWorldArmy *target) {
 ArmySummaryEntryRef entry=source->summary78->GetEntry(key);
 if(entry.holder.entry) {
  if(entry.holder.entry->targetB8) {
   if(entry.holder.entry->targetB8==target->owner20)entry.holder.entry->targetB8=0;
  } else entry.holder.entry->targetB8=source->owner20;
  target->rva00319EF9(source,key);
 }
}
class Rva002B4076 { public: void rva002B4076(LivingWorldArmy *,int,LivingWorldArmy *); };
void Rva002B4076::rva002B4076(LivingWorldArmy *source,int key,LivingWorldArmy *target) {
 rva002B3DE4(source,key,target);
}
