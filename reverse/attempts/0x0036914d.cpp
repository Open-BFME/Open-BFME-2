// ?update@Rva0036914D@@QAEHXZ
// partial score=1.0 date=2026-10-08
// cl: /ICode/Libraries/Include /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
#include "Lib/Coord3D.h"
class Thing {public: void setPosition(const Coord3D *);};
class BfmeVec3EJ;
class Gen_000E5A50 {public: float bfmeDistanceSquared(const BfmeVec3EJ *) const;};
class Rva00368C7A {
public:
    void rva00368C7A(float,const Coord3D *,int);
    char unknown00[0x4EC]; bool active;
    char unknown4ED[0x534-0x4ED]; unsigned char gate;
    char unknown535[3]; float radius; char unknown53C[4]; float amount; Coord3D destination;
};
struct Rva0036914DObject {
    char unknown00[0x258]; Rva00368C7A *movement;
    char unknown25C[0x438-0x25C]; unsigned int flags;
};
struct Rva0036914DBinding {char unknown00[0x14];Rva0036914DObject *object;};
class Rva0036914D {
public:
    char unknown00[0x18]; Rva0036914DBinding *binding;
    int update();
};
int Rva0036914D::update()
{
    Rva0036914DObject *object=binding->object;
    if (object->flags&1) return -2;
    Rva00368C7A *movement=object->movement;
    if (!movement) return -2;
    movement->rva00368C7A(movement->amount,0,1);
    if (!movement->active) return -2;
    float radius=movement->radius;
    Coord3D destination;
    const Coord3D *point=&movement->destination;
    destination.x=point->x;
    destination.y=point->y;
    destination.z=point->z;
    bool close=reinterpret_cast<Gen_000E5A50 *>(object)->bfmeDistanceSquared(reinterpret_cast<const BfmeVec3EJ *>(&destination))<radius*radius;
    if (float(movement->gate)==0.0f && !close) return 0;
    reinterpret_cast<Thing *>(object)->setPosition(&destination);
    return -1;
}
