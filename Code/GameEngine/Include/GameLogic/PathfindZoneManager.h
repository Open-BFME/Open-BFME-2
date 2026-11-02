// Target facts: ctor RVA 0x00532361 (190 bytes) and dtor 0x00533B74 (120 bytes) store no vptr; PathfindZoneManager has no retail virtual functions or identified base. The named ledger rows are GetCollapseIndex 0x0053123A, MarkDirty 0x00531342/0x00531431, IsPassable 0x00531512, GetPortal 0x0053161A, CouldBeInEquivSet 0x00531757, InEquivSet 0x005317D7, CreateEquivalencySet 0x00532708, Update 0x00533BEC and DoXfer 0x005342CB.
// RVA 0x00531D08, called at 0x0053237A with 24000, initializes ushort fields +0/+2/+4/+6 and a pointer +8; 0x00533BD6 frees +8. RVA 0x00531720 indexes four-byte cells at +0xC; 0x00532383 initializes 4001 bucket words and one trailing word at +0x1770C.
// Ctor 0x00532399..0x005323E2 and dtor 0x00533B91..0x00533BD1 prove 56 twenty-byte records at +0x1B594, one at +0x1B9F4, and two twenty-byte bitmaps at +0x1BA08/+0x1BA1C. Ctor 0x005323E9..0x0053240B and transfer 0x005342CB prove flag bytes +0x1BA30/+0x1BA31, pointers +0x1BA34/+0x1BA38, two grid dimensions +0x1BA3C/+0x1BA40 and a sixteen-byte bounds value +0x1BA44 (accessed extent 0x1BA54). All methods below have ledger rows at their named RVAs; real method names follow those rows, and unproved field names remain neutral. Allocation at 0x005328E2 copies four dwords from the row-named Rva005312BERect argument to +0x1BA44..+0x1BA50.

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

class PathfindZoneManager
{
public:
    class CellType;
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

    unsigned short field00;
    unsigned short field02;
    unsigned short field04;
    unsigned short field06;
    unsigned short *field08;
    char unknown0C[0x1BA30 - 0xC];
    unsigned char field1BA30;
    unsigned char field1BA31;
    char unknown1BA32[2];
    Rva005312BEItem *field1BA34;
    Rva005312BEItem **field1BA38;
    int field1BA3C;
    int field1BA40;
    IRegion2D field1BA44;
};

typedef char PathfindZoneManagerAccessedSize[(sizeof(PathfindZoneManager) == 0x1BA54) ? 1 : -1];

#endif
