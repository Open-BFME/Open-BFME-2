/* Target facts (addresses are RVAs): PathfindCell has no virtual functions or base subobjects. Constructor 0x0052DFF2 clears the data pointer at +0 and calls reset 0x0052DED3; destructor 0x0052DD64 reads that pointer and calls 0x0052DD41 to release it into the pool at VA 0x00E049D0. Neither stores a vtable. PathfindLayer::allocateCells passes these two callbacks and stride 0x10 at 0x00366A65..0x00366A78; vector deleting destructor 0x002E70E8 passes the same destructor and stride at 0x002E70F6..0x002E7103. Thus sizeof is 0x10 and there is no constructor/destructor table disagreement. Reset stores a dword at +4, word 0xFFFF at +8 and a packed dword at +0x0C (0x0052DED6/0x0052DEDA/0x0052DEE7). allocateCells copies its zone word to cell+8 at 0x00366ABE. SetType_Dirty 0x0052DA1C uses the low four packed bits; IsObstaclePresent 0x002E6C23 tests type 4; classifyMapCell 0x0052E11A stores clear 0, water 1 and obstacle 4. DoXfer extracts layer bits 4..9 at 0x0052D97B..0x0052D981, and setPinched 0x0052E0FC updates bit 16. The rowed IS_IMPASSABLE predicate 0x002E7569 tests types 5, 4 and 6; its CellType names for 5 and 6 are carried from Zero Hour. CalcCostSoFar tests byte +0x0E bit 0 at 0x0052DCDC, an overlapping view of packed bit 16, not another byte of storage.
The declarations reproduce ledger rows at 0x0052DFF2, 0x0052DD64, 0x0052DED3, 0x0052DE5B, 0x0052DE9B, 0x0052DAC4, 0x0052DA1C, 0x0052DA95, 0x0052DFB1, 0x0052DAE9, 0x0052DC29, 0x0052DAFF, 0x0052DEEF, 0x0052DC3F, 0x0052DC97, 0x0052D84C, 0x002E6C23, 0x0052E0FC and 0x0052DD75. Zero Hour AIPathfind.h supplies the names m_info, m_zone, CellType, getType, getLayer, getPinched, getZone and setZone, not BFME2's layout. The +0x0A word has no proved name; +4 and the packed dword likewise retain offset placeholders. All rowed methods, including the constructor and nonvirtual destructor, are declared out of line.
*/

#pragma once
#ifndef BFME2_PATHFINDCELL_H
#define BFME2_PATHFINDCELL_H

class MixFileInfoBuffer;
class PathfindCellInfo;
class Rva002E6C79;
class Xfer;
struct In002E6BA1;
struct Rva0052DEEFArg;
struct Rva0052DFB1Arg;
enum ObjectID;
enum PathfindLayerEnum;

class PathfindCell
{
public:
    enum CellType
    {
        CELL_CLEAR = 0,
        CELL_WATER = 1,
        CELL_OBSTACLE = 4,
        CELL_BRIDGE_IMPASSABLE = 5,
        CELL_IMPASSABLE = 6
    };

    PathfindCell();
    ~PathfindCell();
    void rva0052DED3();
    void ReleaseInfo();
    static int ReleaseClosedList(MixFileInfoBuffer *);
    void SetParentCell(int *);
    bool SetType_Dirty(int);
    bool StartPathfind(int);
    bool rva0052DFB1(const Rva0052DFB1Arg *);
    void SetOpen(bool);
    void PutOnClosedList(MixFileInfoBuffer **);
    void RemoveFromClosedList();
    bool rva0052DEEF(const Rva0052DEEFArg *, bool, In002E6BA1 *);
    int CalcCostToHierGoal(PathfindCell *);
    int CalcCostSoFar(const Rva002E6C79 *);
    void DoXfer(Xfer *);
    bool IsObstaclePresent(ObjectID) const;
    void setPinched(bool);
    float rva0052DD75(float, int, float);

    CellType getType() const { return (CellType)(m_0C & 0xF); }
    PathfindLayerEnum getLayer() const { return (PathfindLayerEnum)((m_0C >> 4) & 0x3F); }
    bool getPinched() const { return ((m_0C >> 16) & 1) != 0; }
    unsigned short getZone() const { return m_zone; }
    void setZone(unsigned short zone) { m_zone = zone; }

    PathfindCellInfo *m_info;
    unsigned int field04;
    unsigned short m_zone;
    unsigned short field0A;
    unsigned int m_0C;
};

#endif
