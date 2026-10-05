// ?rva002CB2D1@Rva002C9B80Owner@@QAE_NPAVObject@@PBUCoord3D@@PBX1@Z
// partial score=0.93 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /DNDEBUG /MD /EHs-c-
struct Coord3D { float x; float y; float z; };
class Object {
public:
    float rva002636F6(const Coord3D *a, const void *other, const Coord3D *b) const;
    float rva002C97E8(const Coord3D *a, const Coord3D *b) const;
};
class WeaponTemplate {
public:
    float getMinimumAttackRange() const;
};
class Rva002C9B80Owner {
public:
    void rva002C9B80(void *a, float b);
    void *m_00;
    WeaponTemplate *m_04;
    bool rva002CB2D1(Object *o, const Coord3D *a, const void *other, const Coord3D *b2);
};
// ?rva002CB2D1@Rva002C9B80Owner@@QAE_NPAVObject@@PBUCoord3D@@PBX0@Z present-unmatched
bool Rva002C9B80Owner::rva002CB2D1(Object *o, const Coord3D *a, const void *other, const Coord3D *b2)
{
    float d1;
    const Coord3D *b;
    if (other) {
        b = (const Coord3D *)((const char *)other + 0x38);
        d1 = o->rva002636F6(a, other, b);
    } else {
        if (!b2)
            return false;
        b = b2;
        d1 = o->rva002C97E8(a, b);
    }
    float dz = b->z - a->z;
    rva002C9B80(o, dz);
    float f2 = d1;
    float minR = m_04->getMinimumAttackRange();
    float minSq = minR * minR;
    if (minSq > d1)
        return false;
    float dzSq = f2;
    dzSq = dz * dz;
    if (dzSq < d1)
        return false;
    return true;
}
