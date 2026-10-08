// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG
// Target Ghidra [5DE7D1,5DE833),98B. RET12 and signed stride8
// independently prove count plus a by-value8B record. The shared
// UnicodeString owns the first word; second word semantics remain opaque.
// Shrink uses full51B erase381B1F; grow uses full260B fill5DE651;
// argument cleanup calls full133B wide release36E70. These providers and
// full27B record copy5DDD40 support the consumed ABI. Original names are
// unproved; use scoped address-derived views and real linker providers.
// Clean STLport resize supplies the algorithm; explicit extra count keeps
// native evaluation/register ordering as in the matched28B-record sibling.
#include "unicode_string.h"
struct Rva005DE7D1Record {UnicodeString text;unsigned word;};
class Rva005DE7D1Vector {public:
 unsigned size()const{return finish-start;} Rva005DE7D1Record*begin(){return start;} Rva005DE7D1Record*end(){return finish;}
 void resize(unsigned,Rva005DE7D1Record);
private:
 Rva005DE7D1Record*start;Rva005DE7D1Record*finish;Rva005DE7D1Record*limit;
 Rva005DE7D1Record*erase(Rva005DE7D1Record*,Rva005DE7D1Record*);
 void fill(Rva005DE7D1Record*,unsigned,const Rva005DE7D1Record&);
};
void Rva005DE7D1Vector::resize(unsigned count,Rva005DE7D1Record value) {
 if(count<size())erase(begin()+count,end());
 else {unsigned extra=count-size();fill(end(),extra,value);}
}


#pragma comment(linker, "/alternatename:?erase@Rva005DE7D1Vector@@AAEPAURva005DE7D1Record@@PAU2@0@Z=?erase@?$vector@UBfmeStringRecord005DDD40@@V?$allocator@UBfmeStringRecord005DDD40@@@_STL@@@_STL@@QAEPAUBfmeStringRecord005DDD40@@PAU3@0@Z")

#pragma comment(linker, "/alternatename:?fill@Rva005DE7D1Vector@@AAEXPAURva005DE7D1Record@@IABU2@@Z=?_M_fill_insert@?$vector@UBfmeStringRecord005DDD40@@V?$allocator@UBfmeStringRecord005DDD40@@@_STL@@@_STL@@QAEXPAUBfmeStringRecord005DDD40@@IABU3@@Z")

// 0x000C4733: the rowed one-argument wrapper 0x000C4D34 names this
// BfmeStringRecord instantiation. Native RET12 proves an eight-byte by-value
// argument; its destructor is the rowed two-AsciiString teardown 0x000B6CF1.
// The library providers use different established record views with the same
// consumed eight-byte ABI; their application-level identities remain open.
#include "ascii_string.h"
struct BfmeStringRecord000B94D2 {
 AsciiString first, second;
 ~BfmeStringRecord000B94D2();
};
struct Rva00B6CF1;
struct Rva000C225DElement;
namespace _STL {
template <class T> class allocator {};
template <class T, class A> class vector {
public:
 unsigned size() const {return finish-start;}
 T *begin() {return start;} T *end() {return finish;}
 void resize(unsigned, T);
 T *erase(T *, T *);
 void _M_fill_insert(T *, unsigned, const T &);
private:
 T *start; T *finish; T *limit;
};
template <> void vector<BfmeStringRecord000B94D2, allocator<BfmeStringRecord000B94D2> >::resize(unsigned count, BfmeStringRecord000B94D2 value) {
 if(count<size())
  reinterpret_cast<vector<Rva00B6CF1, allocator<Rva00B6CF1> > *>(this)->erase(reinterpret_cast<Rva00B6CF1 *>(begin()+count), reinterpret_cast<Rva00B6CF1 *>(end()));
 else {
  unsigned extra=count-size();
  reinterpret_cast<vector<Rva000C225DElement, allocator<Rva000C225DElement> > *>(this)->_M_fill_insert(reinterpret_cast<Rva000C225DElement *>(end()),extra,reinterpret_cast<const Rva000C225DElement &>(value));
 }
}
}
