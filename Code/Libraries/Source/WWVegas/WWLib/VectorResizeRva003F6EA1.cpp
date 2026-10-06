// cl: /EHsc /MD /DNDEBUG
// Native 108B by-value resize: RET32; opaque record width28.
// Callees: erase3F6975; fill3F6BDB; dtor3F60C8.
// Target Ghidra [3F6EA1,3F6F0D),108B. Native division by28 and
// RET32 independently prove record width28 and a by-value record argument.
// Shrink erases [start+count;finish); grow inserts count-size copies at end.
// The local extra count retains the target evaluation/register ordering.
// Fields remain opaque; destructor60B3F60C8 owns the by-value argument.
// All three callees are independently rowed and fully byte verified.
// Original vector/element names are unproved; no donor type equivalence
// is inferred merely from width. The258B fill provider's EvaMessageInfo
// spelling is used only as a linker alias for this exact native call ABI.
struct Rva003F6EA1Record {~Rva003F6EA1Record();unsigned char consumed[28];};
class Rva003F6EA1Vector {public:
 unsigned size()const{return finish-start;} Rva003F6EA1Record*begin(){return start;} Rva003F6EA1Record*end(){return finish;}
 void resize(unsigned,Rva003F6EA1Record);
private:
 Rva003F6EA1Record*start;Rva003F6EA1Record*finish;Rva003F6EA1Record*limit;
 Rva003F6EA1Record*erase(Rva003F6EA1Record*,Rva003F6EA1Record*);
 void fill(Rva003F6EA1Record*,unsigned,const Rva003F6EA1Record&);
};
void Rva003F6EA1Vector::resize(unsigned count,Rva003F6EA1Record value) {
 if(count<size())erase(begin()+count,end());
 else {unsigned extra=count-size();fill(end(),extra,value);}
}

#pragma comment(linker, "/alternatename:??1Rva003F6EA1Record@@QAE@XZ=??1BfmeStringRecord00111ACF@@QAE@XZ")

#pragma comment(linker, "/alternatename:?erase@Rva003F6EA1Vector@@AAEPAURva003F6EA1Record@@PAU2@0@Z=?erase@Rva003F6975Vector@@QAEPAURva003F6975Record@@PAU2@0@Z")

#pragma comment(linker, "/alternatename:?fill@Rva003F6EA1Vector@@AAEXPAURva003F6EA1Record@@IABU2@@Z=?_M_fill_insert@?$vector@UEvaMessageInfo@@V?$allocator@UEvaMessageInfo@@@_STL@@@_STL@@QAEXPAUEvaMessageInfo@@IABU3@@Z")
