// cl: /O1 /DNDEBUG /MD /EHsc
// Target Ghidra5FEA62..5FEAAF77B RET4; a thiscall by-value result
// is produced from virtual slot1. Native first receives a one-word handle,
// stores its pointer into the caller's result, raises pointee+4, then releases
// the temporary through the fully rowed24B ReleaseTreeHintRef00217D4C.
// Original owner, virtual method name, pointee and handle spellings are unknown.
// The distinct temporary/result source views preserve the observed copy and
// cleanup; their original type relationship is not asserted. Target evidence,
// rather than the BFME1 16-bit RefCountedHandleGetters donor's names/layout,
// establishes the32-bit count and release ABI used here.
// The TargetRef00217D4C prefix agrees with its existing provider: slot0 takes
// flags and returns the allocation, with a signed32-bit count at offset4.
struct TargetRef00217D4C {virtual void *destroy(unsigned flags);int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class Rva005FEA62VirtualValue {
public:
 // ?Rva005FEA62VirtualValue::~Rva005FEA62VirtualValue present-unmatched
 ~Rva005FEA62VirtualValue(){if(value)ReleaseTreeHintRef00217D4C(value);}
 TargetRef00217D4C *value;
};
class Rva005FEA62Value {
public:
 // ?Rva005FEA62Value::Rva005FEA62Value present-unmatched
 Rva005FEA62Value(const Rva005FEA62VirtualValue &other):value(other.value) {if(value)++value->references;}
 // ?Rva005FEA62Value::~Rva005FEA62Value present-unmatched
 ~Rva005FEA62Value(){if(value)ReleaseTreeHintRef00217D4C(value);}
private: TargetRef00217D4C *value;
};
class Rva005FEA62 {
public:
 virtual void unknownSlot0();
 virtual Rva005FEA62VirtualValue virtualValue();
 Rva005FEA62Value copyVirtualValue();
};
Rva005FEA62Value Rva005FEA62::copyVirtualValue(){Rva005FEA62VirtualValue tmp=virtualValue();return tmp;}

// Complete native 0x60052C..0x600579 RET4 repeats the same measured
// virtual-slot-1 return ABI, one-word handle, signed32-bit pointee count
// at +4, and matched fastcall release 0x7DEEF. The original owner and
// concrete pointee remain unknown; these value types describe that ABI.
class Rva0060052C {
public:
 virtual void unknownSlot0();
 virtual Rva005FEA62VirtualValue virtualValue();
 Rva005FEA62Value copyVirtualValue();
};
Rva005FEA62Value Rva0060052C::copyVirtualValue()
{
 Rva005FEA62VirtualValue tmp = virtualValue();
 return tmp;
}
