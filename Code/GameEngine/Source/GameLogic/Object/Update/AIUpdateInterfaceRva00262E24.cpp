// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include
// Native 0x00262E24..0x00262EFF, 219B; WB 0x00E502F0 proves a Coord3D
// returned by value. Partial non-owning views below retain only measured fields.
// This TU keeps the unowned Path::rva003642DF dependency separate from the
// independently linking predicate unit. No vtable or owning object is emitted.
#include "Lib/Coord3DCtorView.h"

struct Rva003642DFNode;
struct Rva003642DFResult { Rva003642DFNode *m_node; Coord3D m_pos; };
class Path { public: Rva003642DFResult rva003642DF(float dist); };
#include "../../../Common/Thing/thing.h"
class Object {
public:
    unsigned char m_prefix[0x38];
    Coord3D m_position;
};
class AIUpdateInterface {
    unsigned char m_prefix[8];
    Object *m_obj;
    unsigned char m_pad0C[0x140 - 0x0C];
    Path *m_path140;
    unsigned char m_pad144[0x1FC - 0x144];
    int m_field1FC;
    Coord3D m_coord200;
public:
    Coord3D rva00262E24();
};

Coord3D AIUpdateInterface::rva00262E24()
{
    Object *obj = m_obj;
    int mode = m_field1FC;
    if (mode != 2 && mode != 4) {
        if (mode == 1) {
            Path *path = m_path140;
            if (path != 0) {
                Rva003642DFResult tmp = path->rva003642DF(40.0f);
                return tmp.m_pos;
            }
        }
        const Coord3D *dir = ((Thing *)obj)->getUnitDirectionVector2D();
        Coord3D d(*dir);
        d.x *= 40.0f;
        d.y *= 40.0f;
        d.z *= 40.0f;
        d.x += obj->m_position.x;
        d.y += obj->m_position.y;
        d.z += obj->m_position.z;
        return d;
    }
    return m_coord200;
}
