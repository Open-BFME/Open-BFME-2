// cl: /ICode/Libraries/Include /O1 /arch:SSE /DNDEBUG /MD /EHsc
// CastleBehavior::createOwnedObject: target 0x0039947A-0x003994C5, 75B.
// Source lead: Open-BFME-1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorCreateOwnedObject.cpp.
// Target facts: owner +8, position +0x38, orientation +0x44 (fld/fstp),
// factory receiver +0x20 and slot +0x10, rowed controlling-player getter.
// Donor carries the wrapper/registration names; target registration body
// 0x003986EF independently looks up the literal CastleMemberBehavior and
// assigns the owner's ID to the created object's member. CastleBehavior's
// adjacent deleting wrapper/destructor establish the subsystem's owner.
// Factory class spelling and definition's type remain address-derived/opaque.
// The BFME 1 donor's void* view of +0x44 is replaced by the target float ABI.
class Player;
class Object { public: Player* getControllingPlayer() const; };
#include "Lib/Coord3D.h"
struct Rva0039947AObjectView {
    char m_lead[0x38];
    Coord3D m_position;
    float m_orientation;
};
class Rva0039947AFactory {
public:
    virtual void unused0();
    virtual void unused1();
    virtual void unused2();
    virtual void unused3();
    virtual Object* create(Object*, void*, Coord3D*, float, Player*, int);
};
class CastleBehavior {
public:
    Object* createOwnedObject(void* definition);
    void registerOwnedObject(Object*);
private:
    char m_lead[8];
    Object* m_object;
    char m_gap[0x14];
    Rva0039947AFactory m_ownedObjectFactory;
};
Object* CastleBehavior::createOwnedObject(void* definition) {
    Object* owner=m_object;
    float orientation=((Rva0039947AObjectView*)owner)->m_orientation;
    Object* created=m_ownedObjectFactory.create(owner, definition,
        &((Rva0039947AObjectView*)owner)->m_position,
        orientation, owner->getControllingPlayer(), 0);
    if(created) registerOwnedObject(created);
    return created;
}
