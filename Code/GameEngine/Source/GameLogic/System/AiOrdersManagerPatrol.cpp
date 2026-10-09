// cl: /O1 /G7 /arch:SSE /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
#include <list>
#include <vector>
#include "../../../../Libraries/Include/Lib/Coord3D.h"
bool Rva00354EB9(const Coord3D *,const Coord3D *);
enum NameKeyType { NK_NONE=0 };
class ArmorTemplate; // opaque return identity inherited from existing providers
class Rva0035516C { public: const ArmorTemplate *rva0035516C(NameKeyType) const; };
class Rva00355B61 { public: const ArmorTemplate *rva00355155(NameKeyType) const; };
class CreateAHeroData;
typedef _STL::list<CreateAHeroData*> ListHeroPtr;
class Rva00548800 { public:
    bool rva00548800(const ListHeroPtr *);
    bool rva00548753(const Rva00548800 &);
};
class ObjectOrderQueue { public:
    const ArmorTemplate *checkForPatrol(void *,const ListHeroPtr *);
    const ArmorTemplate *checkForPatrol(void *,const Rva00548800 *);
    unsigned unknown0;
    _STL::list<NameKeyType> orders;
};
class GroupOrder { public: virtual void slot0(); _STL::vector<unsigned> objects; int id; };
struct ObjectPatrolView { char pad[0x38]; Coord3D position; char pad44[0x74-0x44]; unsigned id; };
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class AiOrdersManager { public:
    void *rva0035538C(const Coord3D &,int,const ListHeroPtr *);
    void *rva00355472(const Coord3D &,int,GroupOrder *);
};
// Callsites and rowed queue/contains providers establish this target's
// patrol reuse route. Existing ArmorTemplate names are only opaque ABI
// adapters; no armor identity is inferred for the returned order/queue.
void *AiOrdersManager::rva00355472(const Coord3D &destination,int mode,GroupOrder *members) {
    unsigned *end=members->objects.end();
    for(unsigned *i=members->objects.begin();i!=end;++i) {
        unsigned id=*i;
        ObjectPatrolView *obj=(ObjectPatrolView*)TheGameLogic->findObjectByID((ObjectID)id);
        if(obj && Rva00354EB9(&obj->position,&destination)) {
            ObjectOrderQueue *queue=(ObjectOrderQueue*)((Rva0035516C*)this)->rva0035516C((NameKeyType)id);
            if(queue && queue->orders.size()) {
                Rva00548800 *order=(Rva00548800*)((Rva00355B61*)this)->rva00355155(queue->orders.front());
                if(order && order->rva00548753(*(Rva00548800*)members)) return order;
            }
        }
    }
    ObjectOrderQueue *queue=(ObjectOrderQueue*)((Rva0035516C*)this)->rva0035516C((NameKeyType)members->objects.front());
    if(queue) {
        const ArmorTemplate *order=queue->checkForPatrol((void*)&destination,(Rva00548800*)members);
        if(order) return (void*)order;
    }
    return 0;
}
