/* Target facts (code addresses are RVAs; tables are VAs): FireLogicSystem is polymorphic. Constructor 0x00286EC8 calls SubsystemInterface 0x001B4E63 at 0x00286EDA, stores Snapshot's table 0x00BBB554 at +0x0C at 0x00286EE4, then installs its own primary 0x00BFB7BC and secondary 0x00BFB7AC at 0x00286F01/0x00286F07. Destructor 0x00286F8F restores that same pair at 0x00286FA0/0x00286FA6, restores Snapshot at 0x00286FF7 and calls SubsystemInterface's destructor 0x001B4E74 at 0x00286FFE. The parent installs 0x00BD77A0 and owns byte +4 and AsciiString +8; its lifetime tables are not competing FireLogicSystem tables. Allocation 0x0022F86F requests 0xA0 bytes through 0x0002FDA0 and calls this constructor at 0x0022F887. The final constructor write at +0x9C proves the same extent. Bases are SubsystemInterface at +0 and Snapshot at +0x0C; sizeof is 0xA0.
Primary table 0x00BFB7BC has fourteen slots before the class-name string at 0x00BFB7F4: 0 deleting destructor 0x00287C05; 1 init 0x0028576D; 2 loadIniFilesFromLegend 0x001B5384; 3/8/12 ret 0x000B3FD0; 4/11 false-ret-4 0x005CB9FF; 5 false 0x0047A699; 6 zero 0x000D43D0; 7/13 ret-4 0x0047A69C; 9 reset 0x00287010; 10 update 0x00287FAD. Slots 2-8/11-13 equal the parent's fourteen-slot table. Secondary table 0x00BFB7AC has four slots ending at the primary table: deleting-destructor thunk 0x00286F87 subtracts 0x0C and jumps to 0x00287C05; loadPostProcess is ret 0x000B3FD0; GetSnapshotName 0x00286F81 returns the string at 0x00BFB7F4; xfer is 0x00287C51. Constructor 0x00286EEB..0x00286F0E constructs four 0x18-byte material records at +0x10 using 0x00286297; their destructor 0x0029D7C2 releases AsciiString at record +4. Tree construction/destruction at 0x00286F13/0x00286FCC select +0x84; the following dword starts at +0x90. Constructor stores prove dwords +0x70/+0x74/+0x78/+0x7C/+0x80/+0x90/+0x94/+0x98/+0x9C; 0x00285DC5 reads the cell-row pointer at +0x70, signed row/column bounds at +0x78/+0x7C and uses 0x14-byte cells. Cell word +4 is read at 0x00285EA3 and saturated at 0x00285EAC..0x00285EC3; unsigned word +6 is tested at 0x00285E98; packed dword +8 is read and masked at 0x00285EC7..0x00285F24; dword +0 is cleared at 0x00285F27. The cell tail +0x0C..0x13 remains opaque. NewMap stores the allocated 0x14-byte-stride cell block at +0x74 at 0x0028708E and its row table at +0x70 at 0x002870A4; 0x002870B1..0x002870C6 populates each row pointer from that block. init stores callback address 0x006D7B50 at +0x9C. Material and tree representations remain opaque here.
Out-of-line declarations follow ledger signatures: RegisterObject 0x00287C21, UnregisterObject 0x00287C39, rva00287552 0x00287552, ChangeFuelInArea 0x002864E6, rva00285DC5 0x00285DC5, ChangeBurnRate 0x00286926/0x00286AB4, ChangeBurnRateInArea 0x002871A4/0x002873DF, ChangeCellToObjectFlammability 0x00285F43, ResetCellToOriginalFlammability 0x00285778, rva00286373 0x00286373, rva0028641F 0x0028641F, rva00286D4E 0x00286D4E, rva00286772 0x00286772, rva00286CC4 0x00286CC4, rva002872BA 0x002872BA and NewMap 0x00287015. Constructor, virtual destructor and all rowed methods are declared without bodies. No Zero Hour class or field-name evidence is used. */
#pragma once
#ifndef BFME2_FIRELOGICSYSTEM_H
#define BFME2_FIRELOGICSYSTEM_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;

struct Coord3D;
struct Rva00287C21Other;
class PolygonTrigger;
class ThingTemplate;
enum ObjectID;

class FireLogicSystem : public SubsystemInterface, public Snapshot
{
public:
    FireLogicSystem();
    virtual ~FireLogicSystem();
    virtual void init();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual int vslot06();
    virtual void vslot07(int);
    virtual void vslot08();
#endif
    virtual void reset();
    virtual void update();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool vslot11(int);
    virtual void vslot12();
    virtual void vslot13(int);
#endif

    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);

    void RegisterObject(Rva00287C21Other *object);
    void UnregisterObject(Rva00287C21Other *object);
    void rva00287552(Rva00287C21Other *object, int add);
    void ChangeFuelInArea(float *position, float radius, int add, int field18, int field00, int field10, bool onlyBurning);
    void rva00285DC5(int startRow, int endRow, int column, int add, int field18, int field00, int field10, bool onlyBurning);
    void ChangeBurnRate(int startRow, int endRow, int column, int delta, bool onlyBurning);
    void ChangeBurnRate(const Coord3D *origin, const Coord3D *direction, float threshold, int startRow, int endRow, int column, int delta, bool onlyBurning);
    void ChangeBurnRateInArea(const Coord3D *position, float radius, int delta, bool onlyBurning);
    void ChangeBurnRateInArea(const Coord3D *position, float radius, const Coord3D *direction, float threshold, int delta, bool onlyBurning);
    void ChangeCellToObjectFlammability(int row, int column, const ThingTemplate *thingTemplate);
    void ResetCellToOriginalFlammability(int row, int column);
    void rva00286373(int id, const Coord3D *position, const ThingTemplate *thingTemplate);
    void rva0028641F(unsigned int id, const Coord3D *position);
    void *rva00286D4E(ObjectID id, int row, int column, bool add);
    bool rva00286772(const PolygonTrigger *area, int minimum);
    void rva00286CC4();
    void rva002872BA(const PolygonTrigger *area, int delta, bool onlyBurning);
    void NewMap();

    struct Cell
    {
        int field00;
        unsigned short field04;
        unsigned short field06;
        unsigned int field08;
        unsigned char field0C[8];
    };
    unsigned char field10[0x60];
    Cell **field70;
    Cell *field74;
    int field78;
    int field7C;
    int field80;
    unsigned char field84[0x0C];
    int field90;
    int field94;
    int field98;
    unsigned int field9C;
};

#endif
