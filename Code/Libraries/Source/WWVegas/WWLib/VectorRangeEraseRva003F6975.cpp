// cl: /O1 /MD /DNDEBUG
// The already-covered29B copy wrapper at3F6619 is rehomed here.
// Its legacy ledger name is a code-generation alias; object-symbol names
// the address-derived C++ definition below. Native29 ignores the fourth
// argument and delegates to the rowed50B3F6477 copy loop with a tag and
// null distance pointer. The declaration consumes only that proven ABI.
// Record width28 follows the copy loop; full application layout/name and
// the original empty-tag parameter spelling are unproved. This view passes
// a const-reference tag as the range-erase caller3F6975 visibly does.
// Existing STLport donor source still emits an exact copy of the old wrapper;
// the row moves once and does not claim a second retail range.
struct Rva003F6975Record {~Rva003F6975Record();unsigned char consumed[28];};
struct Rva003F6975Empty {};
// ?Rva003F6477Tag::Rva003F6477Tag absent-from-retail
// Empty dispatch-tag constructor is inlined; there is no retail body.
struct Rva003F6477Tag {Rva003F6477Tag(){}};
Rva003F6975Record* rva003F6477Copy(Rva003F6975Record*,Rva003F6975Record*,Rva003F6975Record*,const Rva003F6477Tag&,int*);
// ??$__copy_ptrs@PAUBfmeAssignRecord28@@PAU1@@_STL@@YAPAUBfmeAssignRecord28@@PAU1@00U__false_type@0@@Z
__declspec(noinline) Rva003F6975Record* rva003F6619Copy(Rva003F6975Record*first,Rva003F6975Record*last,Rva003F6975Record*out,const Rva003F6975Empty&) {
 return rva003F6477Copy(first,last,out,Rva003F6477Tag(),0);
}

#pragma comment(linker, "/alternatename:?rva003F6477Copy@@YAPAURva003F6975Record@@PAU1@00ABURva003F6477Tag@@PAH@Z=??$__copy@PAUBfmeAssignRecord28@@PAU1@H@_STL@@YAPAUBfmeAssignRecord28@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z")


// Native [3F6975,3F69A8) range erase: copy the surviving tail into first;
// destroy vacated28B records; update finish; return first. RET8 proves
// two pointer arguments. Record fields remain opaque. Visible copy wrapper
// proves the empty dispatch argument unused and preserves native temp placement.
void rva003F6636Destroy(Rva003F6975Record*,Rva003F6975Record*);
class Rva003F6975Vector {public:Rva003F6975Record* erase(Rva003F6975Record*first,Rva003F6975Record*last);
private:Rva003F6975Record*start;Rva003F6975Record*finish;Rva003F6975Record*limit;};
Rva003F6975Record* Rva003F6975Vector::erase(Rva003F6975Record*first,Rva003F6975Record*last) {
 Rva003F6975Record*result=rva003F6619Copy(last,finish,first,Rva003F6975Empty());
 rva003F6636Destroy(result,finish);finish=result;return first;
}

#pragma comment(linker, "/alternatename:?rva003F6636Destroy@@YAXPAURva003F6975Record@@0@Z=??$_Destroy@PAUBfmeStringRecord00111ACF@@@_STL@@YAXPAUBfmeStringRecord00111ACF@@0@Z")
