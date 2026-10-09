// ?addWaypoint@MineshaftPortalNetworkManager@@QAEXPAVWaypoint@@PAVPlayer@@@Z
// partial score=0.95 date=2026-10-09
// cl: /O1 /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
#include <map>
#include <vector>
enum ObjectID { OBJECTID_INVALID=0 };
namespace _STL {
template<> void vector<ObjectID>::push_back(const ObjectID &);
template<class T,class LeftTraits,class RightTraits> static inline bool operator!=(const _Rb_tree_iterator<T,LeftTraits>&a,const _Rb_tree_iterator<T,RightTraits>&b) { return a._M_node!=b._M_node; }
}
class Waypoint { public: void *vtable00; ObjectID id04; };
class Player { public: char unknown00[0x54]; int index54; };
class Rva0037307F {
public:
    Rva0037307F() throw();
    _STL::vector<ObjectID> ids;
    bool dirty0C;
};
typedef _STL::map<int,Rva0037307F *> WaypointLibraries;
class MineshaftPortalNetworkManager {
public:
    void addWaypoint(Waypoint *,Player *);
private:
    char unknown00[16];
    WaypointLibraries libraries10;
};
void MineshaftPortalNetworkManager::addWaypoint(Waypoint *waypoint,Player *player)
{
    int index=player->index54;
    WaypointLibraries::iterator found=libraries10.find(index);
    if(found==libraries10.end()) {
        Rva0037307F *library=new Rva0037307F;
        index=player->index54;
        libraries10[index]=library;
        index=player->index54;
        found=libraries10.find(index);
    }
    index=(int)waypoint->id04;
    found->second->ids.push_back(reinterpret_cast<const ObjectID &>(index));
    found->second->dirty0C=true;
}




