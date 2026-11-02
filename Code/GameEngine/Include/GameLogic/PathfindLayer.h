/* Target facts (addresses are RVAs):
PathfindLayer has no virtual functions or bases. Constructor 0x003666C6 writes zero to +0 at 0x003666CD and initializes the remaining fields without a base call or vtable store. Destructor 0x00367369 jumps directly to 0x00366DEC. Its indirect call at 0x00366E0A uses the object loaded from +0x38 at 0x00366DF8, not the layer's own +0. There is no PathfindLayer constructor or destructor vtable to declare.
Pathfinder's array construction at 0x002F6E41..0x002F6E74 passes destructor VA 0x00767369, constructor VA 0x007666C6, count 16 and stride 0x40 for this+0x60. Its array destruction at 0x002F21C1..0x002F21D2 independently passes the same destructor, count and stride: sizeof(PathfindLayer) is 0x40.
Constructor stores at 0x003666CD..0x003666DB clear the allocation pointers +0/+4, dimensions +8/+0x0C and origin +0x10/+0x14. getCell 0x00366626 reads those column pointers, dimensions and origins and indexes 16-byte PathfindCell objects. The constructor sets the four coordinate words at +0x18/+0x1C/+0x20/+0x24 to -1; AddWallConnectCell 0x00366AE3 compares and copies these two ICoord2D values. It sets +0x28 to zero, dword +0x2C to -1 and byte +0x30 to false at 0x003666EA/0x003666ED/0x003666F0. The setter at 0x0036736E compares and writes byte +0x30; allocation at 0x0036683D consumes the low word of +0x2C as the cell zone.
Constructor stores 0x003666F3/0x003666F6/0x003666F9 set Bridge pointer +0x34 to zero, polygon-list head +0x38 to zero and integer height +0x3C to -1. ClassifyBridgeCells 0x00366E2E calls Bridge methods through +0x34. DoBoundsOverlap 0x003665CB loads +0x38, calls PolygonTrigger::getBounds at 0x002E3978 and follows each trigger's +0x3C link. AddArea 0x003665BB prepends to that list. Cleanup 0x003667D4 clears the allocation pointers and dimensions; 0x00366DEC clears the bridge and trigger list and resets both coordinates, zone and +0x3C.
The initializer at 0x0036659E/0x003665A5 copies the trigger's integer +0x30 into layer +0x3C. ClassifyWall reads layer +0x3C at 0x0052F6C7, converts it with FILD at 0x0052F6CD and subtracts the floating wall height returned through Drawable::rva002725E7. This proves the height field and the inline getHeight accessor used by that rowed caller, rather than an object-ID interpretation.
Out-of-line method declarations follow ledger rows at 0x003666C6, 0x00367369, 0x003665BB, 0x003665CB, 0x00366AE3, 0x0036683D, 0x00366626, 0x00366B77, 0x00366E2E, 0x00366CEA, 0x003666FD, 0x003667D4, 0x00366DEC and 0x000B3FD0. setDestroyed is pinned to 0x0036736E, called from 0x002E722A with the selected 0x40-byte layer as ECX; the rowed body currently belongs to Rva0036666B. All rowed bodies remain out of line.
Donor facts: Zero Hour GeneralsMD GameLogic/AIPathfind.h declares the plain class, its two ICoord2D members and the allocation, dimension, origin, layer, zone, bridge and destroyed member names. The target stores above establish BFME2's offsets and reordered tail independently. No donor header or scoped pathfinding shim is included.
*/

#pragma once
#ifndef BFME2_PATHFINDLAYER_H
#define BFME2_PATHFINDLAYER_H

#include "../../../Libraries/Include/Lib/ICoord2D.h"

class Bridge;
struct IRegion2D;
class LocomotorSet;
class PathfindCell;
class PathfindZoneManager;
class PolygonTrigger;
class Xfer;

class PathfindLayer
{
public:
    PathfindLayer();
    ~PathfindLayer();

    void AddArea(void *area);
    bool DoBoundsOverlap(const IRegion2D *bounds);
    void AddWallConnectCell(const ICoord2D *cell);
    void allocateCells(const IRegion2D *extent);
    PathfindCell *getCell(int x, int y);
    void ClassifyWallCells();
    void ClassifyBridgeCells();
    bool ConnectsZones(PathfindZoneManager *, const LocomotorSet &, int, int);
    bool setDestroyed(bool destroyed);
    void rva003666FD(Xfer *xfer);
    void rva003667D4();
    void rva00366DEC();
    void rva000B3FD0();
    int getHeight() const { return height; }

    PathfindCell *m_blockOfMapCells;
    PathfindCell **m_layerCells;
    int m_width;
    int m_height;
    int m_xOrigin;
    int m_yOrigin;
    ICoord2D m_startCell;
    ICoord2D m_endCell;
    int m_layer;
    int m_zone;
    bool m_destroyed;
    unsigned char m_pad31[3];
    Bridge *m_bridge;
    PolygonTrigger *m_triggers;
    int height;
};

#endif
