// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ??0Rva00541021@@QAE@ABU0@@Z @0x00541021 29B: copy ctor of 28-byte element (int at +0 plus Region3D at +4). Evidence: calls rowed Region3D copy 0x0009AC04; callers are vector helpers 0x0054105B 0x0054107F 0x0054112D 0x00541D10; element stride 0x1C proven by idiv in callers.
struct Region3D
{
    Region3D(const Region3D &that);
    float x_min;
    float y_min;
    float z_min;
    float x_max;
    float y_max;
    float z_max;
};
struct Rva00541021
{
    int m_field0;
    Region3D m_region;
    Rva00541021(const Rva00541021 &other);
};
Rva00541021::Rva00541021(const Rva00541021 &other)
    : m_field0(other.m_field0), m_region(other.m_region)
{
}
