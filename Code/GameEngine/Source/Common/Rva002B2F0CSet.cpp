// cl: /O1 /G7 /DNDEBUG /MD
// Native2B2F0C..2B2F2121B RET4 is the pointer constructor used by
// LivingWorldAutoResolveUnit59B1EC after new ArmySummaryEntry. WB14D5A60
// independently initializes that four-byte owning member and increments
// its entry reference atB0. Its existing copy constructor4F6093 has the
// same pointer/count ABI. The original wrapper template name is unknown;
// preserve established opaque Rva004F6093Holder spelling. Constructor
// lifetime semantics are required: a method-call shim emits a different
// parent EH-state/store sequence even when this leaf's bytes agree.
class ArmySummaryEntry {public: char unknown00[0xB0]; int references;};
class Rva004F6093Holder {
public:
 Rva004F6093Holder(ArmySummaryEntry *);
 ArmySummaryEntry *entry;
};
Rva004F6093Holder::Rva004F6093Holder(ArmySummaryEntry *p):entry(p) {
 if(p) ++p->references;
}
