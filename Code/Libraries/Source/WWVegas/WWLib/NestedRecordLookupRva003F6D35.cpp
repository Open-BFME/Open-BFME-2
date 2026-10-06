// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target Ghidra [3F6D35,3F6DF9),196B; thiscall RET4 returning an inner.
// Target finds an outer by input using full70B3F4752; missing (-1) creates
// a temporary28B record with full124B3F64B2 and pushes it at owner18.
// It then finds an inner via full19B3F4FAA; missing creates and appends a
// temporary48B element. Native reserve constants are2 and6. Return is
// the selected inner address; target arithmetic proves strides28/48.
// The record28/48 fields and owner18 vector are structural target facts;
// original application/input identities and unused fields remain unproved.
// Clean STLport vector accessors preserve the target base-load ordering;
// a flat pointer emitter folded that load and was194B. All full providers
// below are independently rowed and verified; aliases only bind consumed
// ABIs and do not claim original names. Input address bits are preserved
// by the inner provider's established four-byte constructor argument.
#include <vector>
struct Rva003F6D35Inner {
 char consumed[48];Rva003F6D35Inner(int);~Rva003F6D35Inner();
};
struct Rva003F6D35Outer {
 int key;_STL::vector<Rva003F6D35Inner> inners;void*words[3];
 Rva003F6D35Outer(void*);~Rva003F6D35Outer();
};
namespace _STL {
template<> void vector<Rva003F6D35Inner>::reserve(unsigned);
template<> void vector<Rva003F6D35Inner>::push_back(const Rva003F6D35Inner&);
template<> void vector<Rva003F6D35Outer>::reserve(unsigned);
template<> void vector<Rva003F6D35Outer>::push_back(const Rva003F6D35Outer&);
}
class Rva003F6D35Owner {public:
 Rva003F6D35Inner *findOrCreateRva003F6D35(void*);
 int findOuter(void*);int findInner(int,void*);
private:char pad[0x18];_STL::vector<Rva003F6D35Outer> outers;
};
Rva003F6D35Inner *Rva003F6D35Owner::findOrCreateRva003F6D35(void *p){
 int o=findOuter(p);
 if(o==-1){
  outers.reserve(2);
  outers.push_back(Rva003F6D35Outer(p));
  o=outers.size()-1;
 }
 Rva003F6D35Outer &outer=outers[o];
 int i=findInner(o,p);
 if(i==-1){
  outer.inners.reserve(6);
  outer.inners.push_back(Rva003F6D35Inner(reinterpret_cast<int>(p)));
  i=outer.inners.size()-1;
 }
 return &outer.inners[i];
}

#pragma comment(linker, "/alternatename:??0Rva003F6D35Inner@@QAE@H@Z=??0Rva003F610FElement@@QAE@H@Z")

#pragma comment(linker, "/alternatename:??0Rva003F6D35Outer@@QAE@PAX@Z=??0Rva003F64B2Outer@@QAE@PAURva003F64B2Input@@@Z")

#pragma comment(linker, "/alternatename:??1Rva003F6D35Inner@@QAE@XZ=??1Rva003F610FElement@@QAE@XZ")

#pragma comment(linker, "/alternatename:??1Rva003F6D35Outer@@QAE@XZ=??1BfmeStringRecord00111ACF@@QAE@XZ")

#pragma comment(linker, "/alternatename:?findInner@Rva003F6D35Owner@@QAEHHPAX@Z=?rva003F4FAA@LivingWorldBattle@@QAEHHPAX@Z")

#pragma comment(linker, "/alternatename:?findOuter@Rva003F6D35Owner@@QAEHPAX@Z=?rva003F4752@LivingWorldBattle@@QAEHPAX@Z")

#pragma comment(linker, "/alternatename:?push_back@?$vector@URva003F6D35Inner@@V?$allocator@URva003F6D35Inner@@@_STL@@@_STL@@QAEXABURva003F6D35Inner@@@Z=?push_back@?$vector@UBfmePod48@@V?$allocator@UBfmePod48@@@_STL@@@_STL@@QAEXABUBfmePod48@@@Z")

#pragma comment(linker, "/alternatename:?push_back@?$vector@URva003F6D35Outer@@V?$allocator@URva003F6D35Outer@@@_STL@@@_STL@@QAEXABURva003F6D35Outer@@@Z=?push_back@?$vector@UBfmeStringRecord00111ACF@@V?$allocator@UBfmeStringRecord00111ACF@@@_STL@@@_STL@@QAEXABUBfmeStringRecord00111ACF@@@Z")

#pragma comment(linker, "/alternatename:?reserve@?$vector@URva003F6D35Inner@@V?$allocator@URva003F6D35Inner@@@_STL@@@_STL@@QAEXI@Z=?reserve@?$vector@URva003F610FElement@@V?$allocator@URva003F610FElement@@@_STL@@@_STL@@QAEXI@Z")

#pragma comment(linker, "/alternatename:?reserve@?$vector@URva003F6D35Outer@@V?$allocator@URva003F6D35Outer@@@_STL@@@_STL@@QAEXI@Z=?reserve@?$vector@UBfmeStringRecord00111ACF@@V?$allocator@UBfmeStringRecord00111ACF@@@_STL@@@_STL@@QAEXI@Z")
