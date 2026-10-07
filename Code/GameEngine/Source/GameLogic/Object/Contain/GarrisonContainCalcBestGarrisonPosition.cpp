// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG
// ZH GeneralsMD GarrisonContain.cpp::calcBestGarrisonPosition, reviewed
// through BFME1 reference revision 1399ad37d42ea52a63829e417c46a1ba9ed2cd20.
// Target 0x00478547..0x004785A2: ret 8, incoming Contain interface at
// +0x20, findConditionIndex 0x00477E50 and closest-free query 0x00478445.
// The coordinate array is at full-object +0x424 with 40 points per condition.
// Source supplies the purpose/name; native calls, copy and offsets establish
// this target's ABI and layout. The base views follow the verified condition
// query's TU; only the interface method used here is declared in B3.

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class B0 { public: virtual void b0(); int pad4; void *object; };
class B1 { public: virtual void b1(); };
class B2 { public: virtual void b2(); private: unsigned char pad[12]; };
class B3 { public: virtual bool calcBestGarrisonPosition(Coord3D *, const Coord3D *); };
class B4 { public: virtual void b4(); };
class B5 { public: virtual void b5(); };
class B6 { public: virtual void b6(); };
class B7 { public: virtual void b7(); };
class B8 { public: virtual void b8(); private: unsigned char pad[0xC8 - 4]; };

class OpenContain : public B0, public B1, public B2, public B3, public B4,
    public B5, public B6, public B7, public B8
{
public:
    virtual ~OpenContain();
};

class GarrisonContain : public OpenContain
{
public:
    virtual bool calcBestGarrisonPosition(Coord3D *sourcePos, const Coord3D *targetPos);
protected:
    int findConditionIndex();
    int findClosestFreeGarrisonPointIndex(int conditionIndex, const Coord3D *targetPos);
private:
    unsigned char pad[0x424 - sizeof(OpenContain)];
    Coord3D garrisonPoint[3][40];
};

bool GarrisonContain::calcBestGarrisonPosition(Coord3D *sourcePos, const Coord3D *targetPos)
{
    if (!sourcePos || !targetPos)
        return false;
    int conditionIndex = findConditionIndex();
    int placeIndex = findClosestFreeGarrisonPointIndex(conditionIndex, targetPos);
    if (placeIndex == -1)
        return false;
    // The target copies the three words without floating-point arithmetic.
    // Keep the sequential word stores, including their possible overlap.
    const unsigned *point = (const unsigned *)&garrisonPoint[conditionIndex][placeIndex];
    unsigned *out = (unsigned *)sourcePos;
    out[0] = point[0];
    out[1] = point[1];
    out[2] = point[2];
    return true;
}
