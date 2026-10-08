// cl: /DNDEBUG /MD /EHsc
// ?rva002C9C37@PartitionManager@@QAEMPBVObject@@0PAX@Z @0x002C9C37 75B
// PartitionManager relative-angle helper with orientation offsets at +0xBC.
// Evidence: this passed through to rowed getRelativeAngle2D 0x2C9BE4 and to
// rowed rva002C9BC3 0x2C9BC3 and rva002C9B80 0x2C9B80; callers in 0x2FAD13 and
// 0x2FC9B1; neighbours Weapon getAttackRange and isWithinTargetPitch give
// Object layout with float at +0xBC; both callees return float (st0), which
// is returned here so the float tail shares the epilogue.
class Object {
public:
    unsigned char _00[0xBC];
    float m_orientBC;
};
class PartitionManager {
public:
    float getRelativeAngle2D(const Object *a, const Object *b);
    float rva002C9C37(const Object *a, const Object *b, void *c);
};
class Rva002C9BC3Owner {
public:
    float rva002C9BC3(void *a, void *b);
};
class Rva002C9B80Owner {
public:
    float rva002C9B80(void *a, float b);
};
float PartitionManager::rva002C9C37(const Object *a, const Object *b, void *c)
{
    if (b) {
        float ang = getRelativeAngle2D(a, b);
        ang += a->m_orientBC;
        ang += b->m_orientBC;
        return ang;
    } else if (c) {
        return ((Rva002C9BC3Owner *)this)->rva002C9BC3((void *)a, c);
    } else {
        return ((Rva002C9B80Owner *)this)->rva002C9B80((void *)a, 0.0f);
    }
}
