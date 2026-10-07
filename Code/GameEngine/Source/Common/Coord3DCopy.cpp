// cl: /MD
// ?Rva0060173ACopy@@YAXPAVCoord3D@@ABUCoord3DBase@@@Z @0x0060173A 18B: null-checked Coord3D assign helper.
// Callee rowed ?4Coord3D@@QAEAAV0@ABUCoord3DBase@@@Z @0x004216D3 in coord3d.cpp; callers 0x0060174C 0x00601772 0x0060197D 0x00601A3A copy 0x0C-stride Coord3D ranges.
struct Coord3DBase
{
    float x;
    float y;
    float z;
};
class Coord3D : public Coord3DBase
{
public:
    Coord3D &operator=(const Coord3DBase &that);
    Coord3D &rva006016AC(const Coord3D &that);
};
void __cdecl Rva0060173ACopy(Coord3D *dst, const Coord3DBase &src)
{
    if (dst)
        *dst = src;
}
Coord3D *__cdecl Rva00601772Fill(Coord3D *first, unsigned int count, const Coord3DBase &value)
{
    Coord3D *dst = first;
    unsigned int n = count;
    for (; n > 0; --n, ++dst)
        Rva0060173ACopy(dst, value);
    return dst;
}
Coord3D *__cdecl Rva0060174CCopy(const Coord3D *first, const Coord3D *last, Coord3D *result)
{
    Coord3D *dst = result;
    const Coord3D *src = first;
    for (; src != last; ++src, ++dst)
        Rva0060173ACopy(dst, *(const Coord3DBase *)src);
    return dst;
}
// ?rva006016AC@Coord3D@@QAEAAV1@ABV1@@Z @0x006016AC 29B: 12B self-checked copy, caller 0x00601797 loops 0x0C stride.
Coord3D &Coord3D::rva006016AC(const Coord3D &that)
{
    if (&that != this)
    {
        x = that.x;
        y = that.y;
        z = that.z;
    }
    return *this;
}
// ?Rva00601797Copy@@YAPAVCoord3D@@PBV1@0PAV1@@Z @0x00601797 50B: counted Coord3D range copy via 0x006016AC, caller 0x0060186F.
Coord3D *__cdecl Rva00601797Copy(const Coord3D *first, const Coord3D *last, Coord3D *result)
{
    int n = ((const char *)last - (const char *)first) / 12;
    if (n > 0)
    {
        int count = n;
        do
        {
            result->rva006016AC(*first);
            ++first;
            ++result;
            --count;
        } while (count != 0);
    }
    return result;
}

// Native 0x0020E47C..0x0020E493: eight-byte floating-pair return from +0x80.
// Its caller 0x0020EA58 supplies a hidden result slot and copies both words
// to a float-pair output when the receiver's +0x89 flag is set. The explicit
// memberwise copy constructor reproduces retail's x87 first-component copy
// and integer second-component copy. Application identity remains unknown;
// this is a partial address-derived receiver view, not a complete class.
struct Rva0020E47CVal
{
    float x, y;
    Rva0020E47CVal(const Rva0020E47CVal &other) : x(other.x), y(other.y) {}
};
class Rva0020E47C
{
public:
    Rva0020E47CVal rva0020E47C();
private:
    char prefix[0x80];
    Rva0020E47CVal value;
};
Rva0020E47CVal Rva0020E47C::rva0020E47C()
{
    return value;
}
