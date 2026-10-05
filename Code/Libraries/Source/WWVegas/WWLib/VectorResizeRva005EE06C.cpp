// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /EHsc /MD /DNDEBUG
// Target Ghidra [5EE06C,5EE0D8),108B. Native signed stride20 and
// RET24 prove count plus a by-value20B record. UnicodeString owns word0;
// the remaining four words retain opaque semantics from the matched record
// copy45B5ED5F3. Shrink calls full51B erase5EDA8A; grow calls full258B
// fill5EDEF3; argument cleanup calls full133B wide release36E70.
// STLport resize supplies the algorithm; explicit extra count and /G7
// preserve native evaluation/register ordering. /G7 is also established
// by the matched fill provider. Original record/vector names are unproved.
// Scoped ABI views link to independently verified full providers below.
#include "unicode_string.h"
struct Rva005EE06CRecord {UnicodeString text;unsigned word0,word1,word2,word3; Rva005EE06CRecord():word0(0),word1(0),word2(~0u),word3(~0u){}};
class Rva005EE06CVector {public:
 unsigned size()const{return finish-start;} Rva005EE06CRecord*begin(){return start;} Rva005EE06CRecord*end(){return finish;}
 __declspec(noinline) void resize(unsigned,Rva005EE06CRecord); void resize(unsigned);
private:
 Rva005EE06CRecord*start;Rva005EE06CRecord*finish;Rva005EE06CRecord*limit;
 Rva005EE06CRecord*erase(Rva005EE06CRecord*,Rva005EE06CRecord*);
 void fill(Rva005EE06CRecord*,unsigned,const Rva005EE06CRecord&);
};
void Rva005EE06CVector::resize(unsigned count,Rva005EE06CRecord value) {
 if(count<size())erase(begin()+count,end());
 else {unsigned extra=count-size();fill(end(),extra,value);}
}



#pragma comment(linker, "/alternatename:?erase@Rva005EE06CVector@@AAEPAURva005EE06CRecord@@PAU2@0@Z=?EraseRange@Rva005EDA8AVector@@QAEPAUBfmeStringRecord005ED5F3@@PAU2@0@Z")

#pragma comment(linker, "/alternatename:?fill@Rva005EE06CVector@@AAEXPAURva005EE06CRecord@@IABU2@@Z=?_M_fill_insert@?$vector@UBfmeStringRecord005ED5F3@@V?$allocator@UBfmeStringRecord005ED5F3@@@_STL@@@_STL@@QAEXPAUBfmeStringRecord005ED5F3@@IABU3@@Z")

// Target Ghidra [5EE0F4,5EE11E),42B. RET4 proves one count argument.
// Native argument stores independently establish empty text and words
// 0;0;FFFFFFFF;FFFFFFFF before calling full108B by-value resize5EE06C.
// Original field roles remain opaque. Visible record construction preserves
// the native outgoing argument ownership without a private string view.
void Rva005EE06CVector::resize(unsigned count){resize(count,Rva005EE06CRecord());}
