// cl: /O1 /arch:SSE /G7 /Oy- /DNDEBUG /MD /ICode/Libraries/Include/Lib
// Native 0x0046AFDE..0x0046B05B, 125B, RET4. BFME1 semantic guide:
// ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f game/GameEngine/Source/GameLogic/
// Object/Contain/HordeContain/Rva0023BE60NearbyObjectsCheck.cpp.
// Target directly reads template flag bytes109/115 without override traversal;
// Object contained-by is274, AI pathfinder10, receiver owner8, and IDs74.
// Receiver/method identity stays address-derived. Query2EC9E1's full286B
// boundary writes at most16 IDs, takes Object/position/output and pops12.
#include "Coord3D.h"
#include "../../../../Common/GameLogicObjectLookupView.h"
struct Rva0046AFDETemplate {
    char pad000[0x109];
    unsigned char flags109;
    char pad10A[0x115 - 0x10A];
    unsigned char flags115;
};
class Object {
public:
    char pad000[4];
    Rva0046AFDETemplate *m_template;
    char pad008[0x38 - 8];
    Coord3D position;
    char pad044[0x74 - 0x44];
    ObjectID id;
    char pad078[0x274 - 0x78];
    Object *containedBy;
};
class Pathfinder {
public:
    int rva002EC9E1(Object *, const Coord3D *, int *);
};
class AI {
public:
    char pad000[0x10];
    Pathfinder *pathfinder;
};
extern AI *TheAI;
extern GameLogic *TheGameLogic;
class Rva0046AFDEReceiver {
public:
    bool rva0046AFDE(Object *target);
    char pad000[8];
    Object *owner;
};
bool Rva0046AFDEReceiver::rva0046AFDE(Object *target)
{
    if (target->m_template->flags109 & 8)
        return true;
    Object *self = owner;
    Pathfinder *pathfinder = TheAI->pathfinder;
    int nearby[16];
    int count = pathfinder->rva002EC9E1(target, &target->position, nearby);
    for (int i = 0; i < count; ++i) {
        ObjectID id = (ObjectID)nearby[i];
        if (id == self->id)
            continue;
        Object *candidate = TheGameLogic->findObjectByID(id);
        if (!candidate)
            return false;
        if (candidate->containedBy == self)
            continue;
        if (candidate->m_template->flags115 & 0x20)
            continue;
        return false;
    }
    return true;
}
