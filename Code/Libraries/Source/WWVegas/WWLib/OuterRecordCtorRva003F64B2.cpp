// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target Ghidra [3F64B2,3F652E),124B; constructor returns this; RET4.
// Caller196B3F6D35 constructs a temporary28B outer record then pushes it
// into a stride28 vector. Target reads input34 into field0; constructs
// vectors at4/10; reserves six48B elements and appends one constructed
// from the input address bits. Destructor60B3F60C8 independently confirms
// those two vector members. Original application/input identities remain
// unproved; the input word and remaining element48B layout stay opaque.
// C++ vector construction/reserve/push follow STLport4.5.3. Native calls
// use full29B emptybase211E58;116Breserve3F5F15;113Belementctor3F55D6;
// 55Bpush3F6401;60Belementdtor3F535B. All providers are separately verified.
// Address-derived ABI aliases below bind these consumed operations without
// asserting original application type names or unobserved field semantics.
#include <vector>
struct Rva003F64B2Input {char pad[0x34];int key;};
struct Rva003F64B2Element {
 char consumed[48];
 Rva003F64B2Element(int); Rva003F64B2Element(int,const void*);
 ~Rva003F64B2Element();
};
namespace _STL {
template<> void vector<Rva003F64B2Element>::reserve(unsigned);
template<> void vector<Rva003F64B2Element>::push_back(const Rva003F64B2Element&);
}
struct Rva003F64B2Outer {
 int key;
 _STL::vector<Rva003F64B2Element> elements;
 _STL::vector<int> words;
 Rva003F64B2Outer(Rva003F64B2Input*); Rva003F64B2Outer(Rva003F64B2Input*,const void*);
};
Rva003F64B2Outer::Rva003F64B2Outer(Rva003F64B2Input *p)
 :key(p->key),elements(_STL::allocator<Rva003F64B2Element>()),words(_STL::allocator<int>()) {
 elements.reserve(6);
 elements.push_back(Rva003F64B2Element(reinterpret_cast<int>(p)));
}


#pragma comment(linker, "/alternatename:??0Rva003F64B2Element@@QAE@H@Z=??0Rva003F610FElement@@QAE@H@Z")

#pragma comment(linker, "/alternatename:??1Rva003F64B2Element@@QAE@XZ=??1Rva003F610FElement@@QAE@XZ")

#pragma comment(linker, "/alternatename:?push_back@?$vector@URva003F64B2Element@@V?$allocator@URva003F64B2Element@@@_STL@@@_STL@@QAEXABURva003F64B2Element@@@Z=?push_back@?$vector@UBfmePod48@@V?$allocator@UBfmePod48@@@_STL@@@_STL@@QAEXABUBfmePod48@@@Z")

#pragma comment(linker, "/alternatename:?reserve@?$vector@URva003F64B2Element@@V?$allocator@URva003F64B2Element@@@_STL@@@_STL@@QAEXI@Z=?reserve@?$vector@URva003F610FElement@@V?$allocator@URva003F610FElement@@@_STL@@@_STL@@QAEXI@Z")

// Target Ghidra [3F652E,3F65AD),127B; RET8. Same target outer28B
// construction as3F64B2 but forwards the second argument unchanged to
// full142B inner constructor3F5970. That provider is separately verified;
// its ModuleData spelling is a linker identity rather than an assertion
// about the original application payload type at this caller.
Rva003F64B2Outer::Rva003F64B2Outer(Rva003F64B2Input *p,const void *payload)
 :key(p->key),elements(_STL::allocator<Rva003F64B2Element>()),words(_STL::allocator<int>()) {
 elements.reserve(6);
 elements.push_back(Rva003F64B2Element(reinterpret_cast<int>(p),payload));
}

#pragma comment(linker, "/alternatename:??0Rva003F64B2Element@@QAE@HPBX@Z=??0Rva003F5970@@QAE@HPBVModuleData@@@Z")
