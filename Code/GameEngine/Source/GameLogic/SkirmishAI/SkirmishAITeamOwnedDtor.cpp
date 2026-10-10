extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ??1Rva004E9657@@QAE@XZ
// cl: /O1 /G7 /MD /EHs /EHc- /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /D_CRTIMP=
// stlport
// Native4E9657..4E9710,185B. Reset2A9072 deletes this owner; ctor4E962A
// independently proves map00 and vectors0C/18 plus flag24. Element identities
// remain opaque. Native second loop never advances its iterator. Global delete
// intentionally invokes virtual destruction with flag0 then operator delete.
// A scheduling barrier before erase requires fresh range loads; the local
// vector pointer preserves native ESI+4 end addressing. No donor identity claimed.
#include <map>
#include <vector>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}

void Rva00030830GameFree(void*);
namespace _STL {template<> inline void allocator<void*>::deallocate(void**p,size_t)const{if(p)Rva00030830GameFree(p);}}
class Rva004E9419 {public:~Rva004E9419();void rva004E94A1();};
struct TeamMapStorage {unsigned words[3];__forceinline ~TeamMapStorage(){reinterpret_cast<Rva004E9419*>(this)->~Rva004E9419();}};
class Rva002C6E4E {public:~Rva002C6E4E() throw();};
class TeamOwnedPoly {public:virtual ~TeamOwnedPoly() throw();};
class RvaVector {public:void**erase(void**,void**) throw();};
class Rva004E9657 {
public:~Rva004E9657();
 TeamMapStorage map00;
 _STL::vector<void*> vector0c;
 _STL::vector<void*> vector18;
 bool flag24;
};
Rva004E9657::~Rva004E9657(){
 typedef _STL::map<int,Rva002C6E4E*> Map;
 Map&map=*reinterpret_cast<Map*>(&map00);
 Map::iterator end=map.end();
 for(Map::iterator i=map.begin();i!=end;++i)delete i->second;
 reinterpret_cast<Rva004E9419*>(&map00)->rva004E94A1();
 void**i=vector18.begin();void**end18=vector18.end();
 for(;i!=end18;)::delete reinterpret_cast<TeamOwnedPoly*>(*i);
 _ReadWriteBarrier();_STL::vector<void*>*vec=&vector18;reinterpret_cast<RvaVector*>(vec)->erase(vec->begin(),vec->end());
}
