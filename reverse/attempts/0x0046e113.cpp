// ?rva0046E113@HordeContain@@UAE_NPAUCoord3D@@@Z
// partial score=0.95 date=2026-10-05
// ?rva0046E113@HordeContain@@UAE_NPAUCoord3D@@@Z
// Compact source snippet from the home-TU trial. Target evidence: +0x11C
// slot 140; the 320B extent ends at ret 4 before the next body at 0x46E253.
// The +0x170 key collection is the target-proven set<int>.
#include <list>
#include <set>
namespace _STL { using std::list; using std::set; }
struct Coord3D {
    float x, y, z;
    void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
    void scale(float s) { x *= s; y *= s; z *= s; }
};
typedef unsigned int ObjectID;
class Object {
public:
    const Coord3D *getPosition() const;
};
class GameLogic {
public:
    Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
class HordeContain {
public:
    const _STL::list<Object *> *containedItems();
    _STL::set<int> m_170;
    bool rva0046E113(Coord3D *center);
};
bool HordeContain::rva0046E113(Coord3D *center)
{
    float count = 0.0f;
    center->zero();
    const _STL::list<Object *> *items = containedItems();
    for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it) {
        Object *obj = *it;
        if (obj) {
            const Coord3D *pos = obj->getPosition();
            center->x = center->x + pos->x;
            center->y = pos->y + center->y;
            center->z = pos->z + center->z;
            count += 1.0f;
        }
    }
    for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k) {
        Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
        if (obj) {
            const Coord3D *pos = obj->getPosition();
            center->x = pos->x + center->x;
            center->y = pos->y + center->y;
            center->z = pos->z + center->z;
            count += 1.0f;
        }
    }
    if (count == 0.0f)
        return false;
    float inv = 1.0f / count;
    center->scale(inv);
    return true;
}
