// cl: /O1 /Oy- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Record layout is carried from the existing rowed assignment C24EA and
// copy workers C376C/C4795: word0 plus basic_string<char> at4 plus a triple
// at10 and word1C. Native erases C4DBC/C4D52 independently prove stride20.
// Original record and vector class names remain unknown; these RVA names
// retain the existing record view. Default string destruction emits all15B
// at796BC including its free30830 call. The existing pair spelling at that
// folded address does not establish a Locomotor payload for this record.
#include <vector>
#include <string>
struct DwordTriple {int a,b,c;};
class Rva000C24EA {
public:
 Rva000C24EA &operator=(const Rva000C24EA&);
 ~Rva000C24EA();
private:
 int m_00; _STL::basic_string<char> m_04; DwordTriple m_10;int m_1C;
};


// The fourth copy argument is an unused pointer in the native cdecl ABI.
// C4795 reads only the three record pointers and forwards its own tag to
// C376C. Preserve the native address of the final byte of the first stack
// argument without asserting an object lifetime or reading that byte.
Rva000C24EA *Rva000C4795Copy4(const Rva000C24EA*,const Rva000C24EA*,Rva000C24EA*,const void*);
void Rva000BDCEFDestroy32(Rva000C24EA*,Rva000C24EA*);
#pragma comment(linker, "/alternatename:?Rva000C4795Copy4@@YAPAVRva000C24EA@@PBV1@0PAV1@PBX@Z=??$copy@PBVRva000C24EA@@PAV1@@_STL@@YAPAVRva000C24EA@@PBV1@0PAV1@@Z")
#pragma comment(linker, "/alternatename:?Rva000BDCEFDestroy32@@YAXPAVRva000C24EA@@0@Z=?Rva000BDCEFDestroy@@YAXPAURvaPair000BDCEF@@0@Z")
// Native receiver has the vector start/finish/end prefix. C4DBC copies
// [last,finish) to first then destroys the removed tail and updates finish.
class Rva000C24EAVector {
public: Rva000C24EA *eraseRange(Rva000C24EA *first,Rva000C24EA *last);
 Rva000C24EA *eraseOne(Rva000C24EA *position);
private: Rva000C24EA *_M_start,*_M_finish,*_M_end;
};
Rva000C24EA *Rva000C24EAVector::eraseRange(Rva000C24EA *first,Rva000C24EA *last) {
 Rva000C24EA *i=Rva000C4795Copy4(last,_M_finish,first,reinterpret_cast<const unsigned char*>(&first)+3);
 Rva000BDCEFDestroy32(i,_M_finish);_M_finish=i;return first;
}

// C4D52 shifts the suffix unless position is last then destroys the final
// record using the byte-verified folded string cleanup at796BC.
#pragma comment(linker, "/alternatename:??1Rva000C24EA@@QAE@XZ=??1?$pair@$$CBW4LocomotorSetType@@V?$vector@PBVLocomotorTemplate@@V?$allocator@PBVLocomotorTemplate@@@_STL@@@_STL@@@_STL@@QAE@XZ")
Rva000C24EA *Rva000C24EAVector::eraseOne(Rva000C24EA *position) {
 _STL::__false_type tag;
 Rva000C24EA *finish=_M_finish;
 if(position+1!=finish)Rva000C4795Copy4(position+1,finish,position,&tag);
 --_M_finish;_M_finish->Rva000C24EA::~Rva000C24EA();return position;
}
