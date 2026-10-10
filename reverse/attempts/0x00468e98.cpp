// ?rotate@Rva00468E98@@QAE?AVCoord2D@@V2@@Z
// partial score=0.7130226619853177 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
extern "C" double __cdecl sin(double);extern "C" double __cdecl cos(double);
struct Coord2DBase{float x,y;};
class Coord2D:public Coord2DBase {public:Coord2D &Rotate(float);};
struct Rva00468E98Owner{char pad[0x44];float angle;};
class Rva00468E98{public:Coord2D rotate(Coord2D);private:char pad[8];Rva00468E98Owner *owner;};

__forceinline Coord2D &Coord2D::Rotate(float angle)
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
    float rotated = x * cosine - y * sine;
    y = y * cosine + x * sine;
    x = rotated;

    return *this;
}

Coord2D Rva00468E98::rotate(Coord2D point){float angle=owner->angle;point.Rotate(angle);return point;}
