// ?rva00472620@Rva00468E98@@QAE?AURva00472620Position@@PAURva00472620Object@@PAM@Z
// partial score=0.9 date=2026-10-07
// cl: /O1 /arch:SSE /MD /EHsc /Oy- /DNDEBUG
// stlport
// Native Ghidra 00472620..004726DD, 189B, RET12. The first stack
// argument is a hidden three-float result; the explicit arguments supply
// an object-like record with a key at +74 and an auxiliary float output.
// Receiver +8 supplies the base position at +38; map<int,int> at +17C
// selects a 28-byte record in the vector at +188. Same-ECX call 00468E98
// consumes an output reference and a nontrivially copied Vector2 by value,
// and returns that output address. Hidden versus explicit result is unknown.
// Original class/method/field identities remain unknown. Vector2's copy
// operations follow BFME1 ba7ddda7e8 vector2.h; the layouts below are
// measured from the BFME2 accesses, rather than inferred donor layouts.
#include <map>
#include <vector>

class Vector2
{
public:
    float X, Y;
    Vector2() {}
    Vector2(const Vector2 &other) { X = other.X; Y = other.Y; }
    Vector2(float x, float y) { X = x; Y = y; }
    Vector2 &operator=(const Vector2 &other)
    { X = other.X; Y = other.Y; return *this; }
};
struct Rva00472620Position
{
    float x, y, z;
    Rva00472620Position() {}
    Rva00472620Position(const Rva00472620Position &other)
    { x = other.x; y = other.y; z = other.z; }
};
struct Rva00472620Object
{
    char unknown00[0x74];
    int key;
    int getKey() const { return key; }
};
struct Rva00472620Owner
{
    char unknown00[0x38];
    Rva00472620Position position;
};
struct Rva00472620Offset
{
    int unknown00;
    Vector2 offset;
    char unknown0C[8];
    float auxiliary;
    int unknown18;
};
class Rva00468E98
{
public:
    Vector2 &rva00468E98(Vector2 &output, Vector2 offset);
    Rva00472620Position rva00472620(Rva00472620Object *object, float *auxiliary);
private:
    char unknown00[8];
    Rva00472620Owner *owner;
    char unknown0C[0x17C - 0x0C];
    std::map<int, int> indexByKey;
    std::vector<Rva00472620Offset> offsets;
};

// ?rva00472620@Rva00468E98@@QAE?AURva00472620Position@@PAURva00472620Object@@PAM@Z present-unmatched
Rva00472620Position Rva00468E98::rva00472620(Rva00472620Object *object, float *auxiliary)
{
    int index = indexByKey[object->getKey()];
    const Rva00472620Position *base = &owner->position;
    Rva00472620Position result = *base;
    if (index >= 0 && static_cast<unsigned int>(index) < offsets.size())
    {
        Vector2 storage;
        const Vector2 &rotated = rva00468E98(storage, offsets[index].offset);
        result.x = base->x + rotated.X;
        result.y = base->y + rotated.Y;
        result.z = base->z;
        *auxiliary = offsets[index].auxiliary;
    }
    return result;
}
