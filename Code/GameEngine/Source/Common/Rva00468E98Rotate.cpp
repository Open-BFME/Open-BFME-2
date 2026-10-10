// ?rotate@Rva00468E98@@QAE?AVRva00468E98Point@@V2@@Z
// Native468E98..468F0F RET12 proves the eight-byte value argument and
// hidden return pointer; this+8 holds the angle owner, whose angle is +44.
// WB10CA070 (labelled Coord2D::Rotate, MathCoord2D.h) supplies the rotation
// semantic lead; the original owner and value type are still unproven.
// The address-derived value view preserves the target constructor/return ABI.
// The same-valued raw-X predicate retains MSVC's native SSE expression form.
// Only FSINCOS uses asm: VC7.1 otherwise emits x87 libcall arithmetic, while
// retail explicitly does both sin/cos calls then the hardware pair. This
// bounded x87 codegen blocker was isolated before reconstructing the C++ math.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
class Rva00468E98Point
{
public:
    float x, y;
    __forceinline Rva00468E98Point(const Rva00468E98Point &, float);
};
struct Rva00468E98Owner
{
    char pad[0x44];
    float angle;
};
class Rva00468E98
{
public:
    Rva00468E98Point rotate(Rva00468E98Point);
private:
    char pad[8];
    Rva00468E98Owner *owner;
};

__forceinline Rva00468E98Point::Rva00468E98Point(const Rva00468E98Point &point,float angle)
{
    struct Trig
    {
        float cosine;
        float sine;
    } trig;

    trig.sine = (float)sin(angle);
    trig.cosine = (float)cos(angle);

    __asm
    {
        fld angle
        fsincos
        fstp trig.cosine
        fstp trig.sine
    }

    float &sine = trig.sine;
    float &cosine = trig.cosine;
    x = (*(unsigned *)&point.x ? point.x * cosine : point.x * cosine) - point.y * sine;
    y = point.y * cosine + point.x * sine;
}

Rva00468E98Point Rva00468E98::rotate(Rva00468E98Point point)
{
    float angle = owner->angle;
    return Rva00468E98Point(point, angle);
}
