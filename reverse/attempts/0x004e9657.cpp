// ??1Rva004E9657@@QAE@XZ
// partial score=0.9352165934493688 date=2026-10-10
// cl: /O1 /G7 /MD /EHs /EHc- /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /D_CRTIMP=
// stlport
#include <map>
#include <vector>

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
 reinterpret_cast<RvaVector*>(&vector18)->erase(vector18.begin(),vector18.end());
}
