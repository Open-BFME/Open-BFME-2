// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /EHsc /MD /DNDEBUG
// Target Ghidra [5FE974,5FE9E0),108B. Native signed stride12 and
// RET16 prove count plus a by-value12B record. The matched35B assignment
// 5FDEC7 copies opaque words0/4 and sets UnicodeString8. Native cleanup
// at argument+8 independently supports that string ownership.
// Shrink calls full51B erase5FE4E2; grow calls full258B fill5FE835;
// argument cleanup calls full133B wide release36E70. All are rowed.
// STLport resize supplies the algorithm; explicit extra count and /G7
// preserve native evaluation/register ordering. /G7 is also established
// by the matched fill provider. Original record/vector names are unproved.
// Scoped ABI views link to independently verified full providers below.
#include "unicode_string.h"
struct Rva005FE974Record {unsigned word0,word4;UnicodeString text08;Rva005FE974Record():word0(0),word4(0){}};
class Rva005FE974Vector {public:
 unsigned size()const{return finish-start;} Rva005FE974Record*begin(){return start;} Rva005FE974Record*end(){return finish;}
 void resize(unsigned,Rva005FE974Record);
 void rva005FE9E0(unsigned);
private:
 Rva005FE974Record*start;Rva005FE974Record*finish;Rva005FE974Record*limit;
 Rva005FE974Record*erase(Rva005FE974Record*,Rva005FE974Record*);
 void fill(Rva005FE974Record*,unsigned,const Rva005FE974Record&);
};
void Rva005FE974Vector::resize(unsigned count,Rva005FE974Record value) {
 if(count<size())erase(begin()+count,end());
 else {unsigned extra=count-size();fill(end(),extra,value);}
}

void Rva005FE974Vector::rva005FE9E0(unsigned count)
{
	resize(count, Rva005FE974Record());
}



#pragma comment(linker, "/alternatename:?erase@Rva005FE974Vector@@AAEPAURva005FE974Record@@PAU2@0@Z=?erase@?$vector@UBfmeContainerRecord005FDEC7@@V?$allocator@UBfmeContainerRecord005FDEC7@@@_STL@@@_STL@@QAEPAUBfmeContainerRecord005FDEC7@@PAU3@0@Z")

#pragma comment(linker, "/alternatename:?fill@Rva005FE974Vector@@AAEXPAURva005FE974Record@@IABU2@@Z=?_M_fill_insert@?$vector@UBfmeContainerRecord005FDEC7@@V?$allocator@UBfmeContainerRecord005FDEC7@@@_STL@@@_STL@@QAEXPAUBfmeContainerRecord005FDEC7@@IABU3@@Z")
