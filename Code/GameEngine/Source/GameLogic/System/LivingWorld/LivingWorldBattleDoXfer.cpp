// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /ICode/Libraries/Include/Lib
// ?DoXfer@LivingWorldBattle@@UAEXAAVXfer@@@Z @0x003F7023 268B (ret 4).
// Snapshot slot 3 of the LivingWorldBattle primary vtable 0x00C3709C
// (slot 0 the deleting dtor 0x003F6CDD; slot 2 the name getter 0x003F6A8B).
// WorldBuilder twin 0x0104D1A0 (mislabelled from its inlined
// "LivingWorldBattle::ResolutionType" XferEnum literal) gives the flow:
// Version(1 1) then the Coord2D at +0x28 (Xfer slot 0x50) the int at +0x30
// the battle ID at +0x34 (rowed 0x003F40BB) the int at +0x38 and the
// resolution type at +0x3C (rowed 0x003F3FB6). The region pointer at +0x24
// travels as its +0x12C region ID (-1 when null) through the rowed int
// helper 0x003EFE82; on load it is looked up again through
// TheLivingWorldLogic +0xB0 and the rowed region-by-id accessor 0x0020EAF6.
// Last the 28-byte BattleSide vector at +0x18: its count is transferred and
// on load the vector is cleared (rowed range erase 0x003F6975) and resized
// (rowed 0x003F7000) before each element runs the rowed BattleSide transfer
// 0x003F6672.
#include "Coord2D.h"

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

class Xfer
{
public:
    class Version
    {
    public:
        Version() {}
        Version(unsigned char a, unsigned char b) { data[0] = a; data[1] = b; }
        unsigned char data[2];
    };

    virtual ~Xfer();

    virtual bool IsLoading() const;
    virtual bool IsStoring() const;
    virtual bool IsCRC() const;
    virtual bool IsLightCRC() const;

    virtual void v5() = 0;
    virtual void v6() = 0;
    virtual void v7() = 0;

    virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
    virtual Xfer &XferRawBytes(void *data, unsigned int size);
    virtual Xfer &operator==(bool &value);
    virtual Xfer &operator==(char &value);
    virtual Xfer &operator==(unsigned char &value);
    virtual Xfer &operator==(short &value);
    virtual Xfer &operator==(unsigned short &value);
    virtual Xfer &operator==(int &value);
    virtual Xfer &operator==(unsigned int &value);
    virtual Xfer &operator==(__int64 &value);
    virtual Xfer &operator==(float &value);
    virtual Xfer &operator==(AsciiString &value);
    virtual Xfer &operator==(UnicodeString &value);
    virtual Xfer &operator==(PooledString &value);
    virtual Xfer &operator==(Coord3DBase &value);
    virtual Xfer &operator==(ICoord3D &value);
    virtual Xfer &operator==(Region3D &value);
    virtual Xfer &operator==(IRegion3D &value);
    virtual Xfer &operator==(Coord2D &value);
    virtual Xfer &operator==(ICoord2D &value);
    virtual Xfer &operator==(Region2D &value);
    virtual Xfer &operator==(IRegion2D &value);
    virtual Xfer &operator==(RealRange &value);
    virtual Xfer &operator==(RGBColor &value);
    virtual Xfer &operator==(RGBAColorReal &value);
    virtual Xfer &operator==(RGBAColorInt &value);
    virtual Xfer &operator==(Snapshot &value);
    virtual Xfer &operator==(XferUnknown11 &value) = 0;
    virtual Xfer &operator==(Version &value);

    virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);
};

struct Rva003EFE82Obj;
int __cdecl Rva003EFE82Get(Rva003EFE82Obj *xfer, void *value);
void __cdecl XferLivingWorldBattleID(Xfer *xfer, void *value);
void __cdecl XferLivingWorldBattleResolutionType(Xfer *xfer, void *value);

// Region: +0x12C is its region ID.
class Rva0020E89C
{
public:
    char m_pad000[0x12C];
    int m_id;
};

class Rva0020EAF6View
{
public:
    Rva0020E89C *rva0020EAF6(int id);
};

class LivingWorldLogic
{
public:
    char m_pad000[0xB0];
    Rva0020EAF6View *m_regionManager;
};
extern LivingWorldLogic *TheLivingWorldLogic;

// 28-byte BattleSide element; rowed transfer 0x003F6672.
class Rva003F6672
{
public:
    void rva003F6672(Xfer *xfer);
    char m_bytes[0x1C];
};

struct Rva003F6975Record;
class Rva003F6975Vector
{
public:
    Rva003F6975Record *erase(Rva003F6975Record *first, Rva003F6975Record *last);
};

class Rva00427130Vector
{
public:
    void resize(unsigned int count);
};

struct BattleSideVector
{
    Rva003F6672 *m_first;
    Rva003F6672 *m_last;
    Rva003F6672 *m_end;
};

class LivingWorldBattle
{
public:
    virtual void DoXfer(Xfer &xfer);

    char m_pad04[0x14];
    BattleSideVector m_sides;     // +0x18
    Rva0020E89C *m_region;        // +0x24
    Coord2D m_coord28;            // +0x28
    int m_int30;                  // +0x30
    int m_battleID;               // +0x34
    int m_winningSide;            // +0x38
    int m_resolutionType;         // +0x3C
};

void LivingWorldBattle::DoXfer(Xfer &xfer)
{
    Xfer::Version v(1, 1);
    xfer == v;
    xfer == m_coord28;
    xfer == m_int30;
    XferLivingWorldBattleID(&xfer, &m_battleID);
    xfer == m_winningSide;
    XferLivingWorldBattleResolutionType(&xfer, &m_resolutionType);

    if (xfer.IsLoading())
    {
        int regionID;
        Rva003EFE82Get((Rva003EFE82Obj *)&xfer, &regionID);
        m_region = TheLivingWorldLogic->m_regionManager->rva0020EAF6(regionID);
    }
    else
    {
        int id = m_region ? m_region->m_id : -1;
        int regionID = id;
        Rva003EFE82Get((Rva003EFE82Obj *)&xfer, &regionID);
    }

    BattleSideVector &sides = m_sides;
    int count = sides.m_last - sides.m_first;
    xfer == count;
    if (xfer.IsLoading())
    {
        ((Rva003F6975Vector *)&sides)->erase((Rva003F6975Record *)sides.m_first, (Rva003F6975Record *)sides.m_last);
        ((Rva00427130Vector *)&sides)->resize(count);
    }
    for (int i = 0; i < count; ++i)
        sides.m_first[i].rva003F6672(&xfer);
}
