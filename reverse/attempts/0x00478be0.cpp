// ?healObjects@GarrisonContain@@IAEXXZ
// partial score=0.8 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// stlport
#include <list>
namespace _STL {
template<class T,class L,class R>
static inline bool operator!=(const _List_iterator<T,L>& a,const _List_iterator<T,R>& b) { return a._M_node != b._M_node; }
}
class Object;
typedef _STL::list<Object*> Rva00478BE0List;
struct Rva0046247DPair { void* present; Rva00478BE0List* list; };
class Rva0046247D { public: void rva0046247D(Rva0046247DPair&); };
struct Rva00478BE0Data {
    char m_lead[0x98];
    bool m_doIHealObjects;
    float m_framesForFullHeal;
};
class GarrisonContain {
public:
protected:
    void healObjects();
    void healSingleObject(Object*,float);
private:
    char m_lead[4];
    const Rva00478BE0Data* m_data;
};
void GarrisonContain::healObjects() {
    const Rva00478BE0Data* data=m_data;
    if(!data->m_doIHealObjects) return;
    Rva0046247DPair pair;
    ((Rva0046247D*)this)->rva0046247D(pair);
    const Rva00478BE0List& list=*pair.list;
    for(Rva00478BE0List::const_iterator it=list.begin();it!=list.end();++it)
        healSingleObject(*it,data->m_framesForFullHeal);
}
