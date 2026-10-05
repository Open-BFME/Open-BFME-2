// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Retail [5B04D3,5B0505),50B computes signed count at stride20 and copies
// five DWORDs per iteration; [5B09D8,5B09F5),29B is its const-tag wrapper.
// Erase5B129F supplies last/finish/first and the empty false_type reference.
// STLport4.5.3 __copy and __copy_ptrs are the reference algorithms. This local
// wrapper restores the retail const-reference tag ABI changed by the shim.
// Record is only the target's raw20 copy view; application identity unknown.
// The pre-existing50B alias row is rehomed here from a unit the link census
// refuses; this is an existing-body linkage repair, not added byte coverage.
#include <stl/_algobase.h>
struct Rva005B09D8Record { int words[5]; };
template Rva005B09D8Record* _STL::__copy<Rva005B09D8Record*,Rva005B09D8Record*,int>(Rva005B09D8Record*,Rva005B09D8Record*,Rva005B09D8Record*,const _STL::random_access_iterator_tag&,int*);
Rva005B09D8Record* copyPointersRva005B09D8(Rva005B09D8Record*first,Rva005B09D8Record*last,Rva005B09D8Record*result,const _STL::__false_type&) {
return _STL::__copy(first,last,result,_STL::random_access_iterator_tag(),(int*)0);
}

// Native erase [5B129F,5B12C5),38B RET8, called by resize5B1A07.
// Retail copies [last,finish) onto first with the full29B wrapper above,
// stores its result at receiver+4 and returns first. No element destructor
// is called on this path. The three-pointer view follows STLport vector;
// application owner and element identity remain unknown.
class Rva005B129FVector {
public:
 Rva005B09D8Record* erase(Rva005B09D8Record*,Rva005B09D8Record*);
 void resize(unsigned int,Rva005B09D8Record);
private: Rva005B09D8Record*start,*finish,*endStorage;
};
Rva005B09D8Record* Rva005B129FVector::erase(Rva005B09D8Record*first,Rva005B09D8Record*last) {
finish=copyPointersRva005B09D8(last,finish,first,_STL::__false_type());
return first;
}

// Native [5B1A07,5B1A50),73B RET24: count plus a by-value20B record,
// unlike the reference's const-reference resize signature. Shrink calls
// full38B erase5B129F; growth calls full232B fill-insert5B1748. The target
// independently supplies the three-pointer offsets, stride20 and value ABI.
// BfmePod20 is the existing fill provider's size-only view. Declaration-only
// specialization binds that full provider without emitting another copy.
struct BfmePod20 { int a[5]; };
#include <vector>
namespace _STL {
template<> void vector<BfmePod20>::_M_fill_insert(BfmePod20*,unsigned int,const BfmePod20&);
}
void Rva005B129FVector::resize(unsigned int count,Rva005B09D8Record value) {
if(count < static_cast<unsigned int>(finish-start)) erase(start+count,finish);
else reinterpret_cast<_STL::vector<BfmePod20>*>(this)->_M_fill_insert(reinterpret_cast<BfmePod20*>(finish),count-static_cast<unsigned int>(finish-start),reinterpret_cast<const BfmePod20&>(value));
}
