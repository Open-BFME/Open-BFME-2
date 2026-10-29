// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7
// Native 001E4015..001E4073 RET8; WB AE7CA0; caller Path::rva00365E98.
// The entry's mode74==1 and flagD8 permit a destination-versus-heading test.
// WB copies the destination into a coordinate, subtracts Object's position,
// then takes the XY dot product. Keeping that coordinate operation order
// reproduces retail's SSE allocation. No original method name is asserted.
#include "Lib/Coord3D.h"

typedef bool Bool;
class Object;
#include "../../Common/Thing/thing.h"
struct Direction4015Template {
    char pad00[0x74];
    int mode74;
    char pad78[0xD8 - 0x78];
    int flagD8;
};
struct Direction4015Entry {
    void *word0;
    Direction4015Template *settings;
};
struct Direction4015Object {
    char pad00[0x38];
    Coord3D pos;
};
struct DirectionMath : Coord3D {
    DirectionMath() {}
    DirectionMath(const Coord3D &v) { x = v.x; y = v.y; z = v.z; }
    void sub(const Coord3D *v) { x -= v->x; y -= v->y; z -= v->z; }
};
class Rva001E46E1 {
public:
    Bool rva001E4015(Object *, const Coord3D *);
};

Bool Rva001E46E1::rva001E4015(Object *obj, const Coord3D *dest)
{
    Direction4015Entry *entry = (Direction4015Entry *)this;
    if (entry->settings->mode74 == 1) {
        if (entry->settings->flagD8) {
            DirectionMath direction;
            ((const Thing *)obj)->getUnitDirectionVector2D(direction);
            const Coord3D *pos = &((const Direction4015Object *)obj)->pos;
            DirectionMath delta(*dest);
            delta.sub(pos);
            float dot = direction.x * delta.x + direction.y * delta.y;
            if (dot < 0.0f)
                return true;
        }
    }
    return false;
}
