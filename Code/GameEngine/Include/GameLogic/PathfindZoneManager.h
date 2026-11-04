// Target facts: ctor RVA 0x00532361 (190 bytes) and dtor 0x00533B74 (120 bytes) store no vptr; PathfindZoneManager has no retail virtual functions; its only base is the Rva00531E14 id table at +0. The named ledger rows are GetCollapseIndex 0x0053123A, MarkDirty 0x00531342/0x00531431, IsPassable 0x00531512, GetPortal 0x0053161A, CouldBeInEquivSet 0x00531757, InEquivSet 0x005317D7, CreateEquivalencySet 0x00532708, Update 0x00533BEC and DoXfer 0x005342CB.
// RVA 0x00531D08, called at 0x0053237A with 24000, initializes ushort fields +0/+2/+4/+6 and a pointer +8; 0x00533BD6 frees +8. RVA 0x00531720 indexes four-byte cells at +0xC; 0x00532383 initializes 4001 bucket words and one trailing word at +0x1770C.
// Ctor 0x00532399..0x005323E2 and dtor 0x00533B91..0x00533BD1 prove 56 twenty-byte records at +0x1B594, one at +0x1B9F4, and two twenty-byte bitmaps at +0x1BA08/+0x1BA1C. The helper types below are the verified views of PathfindZoneManagerXfer.cpp, whose ctor/dtor rows byte-match with them: the +0..+0xB prefix is the Rva00531E14 id table (0x00531D08 initializes it as a base before state 0), the 24000 four-byte CellType cells fill +0xC..+0x1770C (0x00531720 reads them; Xfer 0x005342CB transfers them), 0x00532383 builds the Rva00531E74 bucket table at +0x1770C, the eh vector ctor at 0x005323B2 builds the 8x7 Rva00531FCF union-find records with callbacks 0x00531FBE/0x00531FCF, 0x005323C2 builds the last one, and 0x00530F47 builds both BooleanBitmapSet subobjects. Ctor 0x005323E9..0x0053240B and transfer 0x005342CB prove flag bytes +0x1BA30/+0x1BA31, pointers +0x1BA34/+0x1BA38, two grid dimensions +0x1BA3C/+0x1BA40 and a sixteen-byte bounds value +0x1BA44 (accessed extent 0x1BA54). All methods below have ledger rows at their named RVAs; real method names follow those rows, and unproved field names remain neutral. Allocation at 0x005328E2 copies four dwords from the row-named Rva005312BERect argument to +0x1BA44..+0x1BA50.

#ifndef BFME2_PATHFINDZONEMANAGER_H
#define BFME2_PATHFINDZONEMANAGER_H

#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/IRegion2D.h"

class PathfindCell;
class PathfindLayer;
class Rva005312BEItem;
class Xfer;
struct PathfindZoneParams;
struct Rva005312BERect;

class Rva00531E14
{
public:
    Rva00531E14(unsigned short n) { rva00531D08(n); }
    Rva00531E14 &rva00531D08(unsigned short);
    ~Rva00531E14() { delete [] table; }
    unsigned char IsUsed_SlowMethod(unsigned short);
    unsigned char ReleaseUse(unsigned short);
    unsigned short GetAndUseNew();
    unsigned short rva00531DE1();
    unsigned short capacity, first, second, end;
    unsigned short *table;
};

class Rva00531A44
{
public:
    Rva00531A44 &rva00531A44(unsigned short);
    void rva00531BA7(Xfer *);
    __declspec(nothrow) void rva00531A93();
    void MakeSet(unsigned short);
    unsigned short capacity, first;
    unsigned short *parents;
    unsigned char *ranks;
    unsigned short *next, *last;
    unsigned short FindSet(unsigned short);
    unsigned short rva00531B20(unsigned short);
    void rva00531B3A(unsigned short);
    unsigned short GetNextSetMember(unsigned short n) { return next[n]; }
};

// Target array callback 0x00531FCF is a 5-byte destructor forwarding to the
// rowed union-find release at 0x00531A93; the wrapper name stays
// address-qualified. Cleanup helpers 0x00530FAE/0x00531A93/0x005320C1 only
// deallocate: explicit nothrow contracts reproduce retail EH state stores.
class Rva00531FCF : public Rva00531A44
{
public:
    Rva00531FCF() { rva00531A44(24000); }
    ~Rva00531FCF() throw() { rva00531A93(); }
};

class BooleanBitmapSet
{
public:
    BooleanBitmapSet(int);
    ~BooleanBitmapSet() throw() { rva00530FAE(); }
    __declspec(nothrow) void rva00530FAE();
    void SetBit(int);
    void rva00530FC5();
    void ResetEnum() { bit = 0; cursor = 0; }
    bool DoEnum(int *);
    unsigned numBitsDiv32;
    int *bits;
    unsigned *summary;
    unsigned cursor, bit;
};

// The first 20-byte bitmap subobject uses a size-preserving derived
// construction view to reproduce native LEA-before-PUSH ordering at
// 0x005323C7. This is compiler shape evidence; no claim about an original
// derived type is made.
class PathfindInitialBitmapView : public BooleanBitmapSet
{
public:
    __forceinline PathfindInitialBitmapView(int n) : BooleanBitmapSet(n) {}
};

class Rva00531E74
{
public:
    Rva00531E74() : count(0) { for (int i = 0; i < 4001; ++i) words[i] = 0; }
    __declspec(nothrow) void rva005320C1();
    void rva00531E74();
    ~Rva00531E74() throw() { rva005320C1(); }
private:
    unsigned words[4001];
    unsigned count;
};

class PathfindZoneManager : public Rva00531E14
{
public:
    class CellType
    {
    public:
        void DoXfer(Xfer *);
        union { unsigned value; struct { unsigned type:3, id:6, secondary:6, unknown15:4, bridge:1, unknown20:12; }; };
    };
    class Block;

    PathfindZoneManager();
    ~PathfindZoneManager();
    static int GetCollapseIndex(const PathfindZoneParams &);
    void rva005312BE();
    void rva00531300();
    void MarkDirty(Rva005312BERect *);
    void MarkDirty(int, int);
    void rva00531481();
    void rva005314C6(int, int, unsigned char);
    unsigned char IsPassable(int, int);
    void rva0053155E(int, int, bool, int);
    bool rva005315C8(int, int);
    int GetPortal(int, int, int);
    unsigned char rva005316E0(unsigned short, unsigned short);
    unsigned char rva00531720(unsigned int, unsigned int);
    bool CouldBeInEquivSet(unsigned int, unsigned int);
    bool InEquivSet(unsigned int, unsigned int, unsigned int);
    bool rva00532069(int, int);
    void rva005324D8(unsigned char, unsigned short, unsigned short);
    void CreateEquivalencySet(unsigned int, unsigned int);
    void rva005328E2(Rva005312BERect *);
    void rva005329C8(PathfindCell **, const IRegion2D &);
    void rva00532FEA(Block *, PathfindCell **, const IRegion2D &);
    void rva005335D3();
    void rva00533664(Block *, PathfindCell **, PathfindLayer *, const IRegion2D &, bool);
    void Update(PathfindCell **, PathfindLayer *, const IRegion2D &);
    void DoXfer(Xfer *);

    CellType field0C[24000];
    Rva00531E74 field1770C;
    Rva00531FCF field1B594[8][7];
    Rva00531FCF field1B9F4;
    PathfindInitialBitmapView field1BA08;
    BooleanBitmapSet field1BA1C;
    unsigned char field1BA30;
    unsigned char field1BA31;
    char unknown1BA32[2];
    Rva005312BEItem *field1BA34;
    Rva005312BEItem **field1BA38;
    int field1BA3C;
    int field1BA40;
    IRegion2D field1BA44;
};

typedef char PathfindZoneManagerUnionSize[(sizeof(Rva00531FCF) == 20 && sizeof(BooleanBitmapSet) == 20) ? 1 : -1];
typedef char PathfindZoneManagerAccessedSize[(sizeof(PathfindZoneManager) == 0x1BA54) ? 1 : -1];

#endif
