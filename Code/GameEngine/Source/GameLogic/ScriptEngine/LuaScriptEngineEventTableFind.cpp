// cl: /Ireference/shims/bfme2_ascii /O1 /D_STLP_USE_STATIC_LIB /MD /EHsc /arch:SSE
// Donor: BFME1 SortedStrings2E1F80.cpp at34f59164; target171B33280B..3328B6 RET8.
// Target offsets4 sorted flag; vector8/C/10; key0 value4 flag8 stride12.
// Five-slot lower-bound repaired and rowed at331987; sort3327C5 is owned.
// The vector's end is captured inside the lower-bound call's argument list
// (last=entries.end()) so cl evaluates both range loads after the empty
// comparator temporary is built, as retail does.
// stlport
#include "ascii_string.h"
#include <vector>
struct S4SortElem12 { int key; AsciiString name; char flag; };
struct S4Cmp002E1690 {};
namespace _STL { template<class T,class C> void sort(T,T,C); }
struct S4LowerBoundLess {};
void *Rva00331987(void *,void *,const int *,S4LowerBoundLess,int *) throw();
struct StringEntry { int key; AsciiString value; bool flag; };
class Rva0033280B {
 unsigned field00; bool sorted; char pad05[3];
 _STL::vector<StringEntry> entries;
 bool empty() const {return entries.empty();}
 __forceinline void sort() {if(!sorted) _STL::sort((S4SortElem12 *)entries.begin(),(S4SortElem12 *)entries.end(),S4Cmp002E1690());sorted=true;}
public:
 const AsciiString &find(int key,bool *flag);
};
const AsciiString &Rva0033280B::find(int key,bool *flag)
{
 *flag=false;
 if(empty()) return AsciiString::TheEmptyString;
 sort();
 const int lookupKey=key;
 StringEntry search;
 search.key=lookupKey;
 StringEntry *last;
 StringEntry *found=(StringEntry *)Rva00331987(entries.begin(),(last=entries.end()),&search.key,S4LowerBoundLess(),0);
 if(found!=last && found->key==lookupKey) {
  *flag=found->flag;
  return found->value;
 }
 return AsciiString::TheEmptyString;
}
