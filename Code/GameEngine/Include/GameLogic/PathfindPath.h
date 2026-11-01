/* Target facts (addresses are RVAs):
Path has no virtual functions or polymorphic base in retail. Its complete constructor at 0x00363DC8 writes zero to +0/+4/+8/+0x10, bytes +0x0C/+0x0D, and floats +0x14/+0x18/+0x1C/+0x20; it writes -1 to +0x24 and makes no calls or vtable stores. The complete destructor at 0x00364A89 only walks the head at +4 and calls 0x00265488 to release nodes. The nonvirtual scalar deleting destructor at 0x00262895 calls that destructor directly. There is no Path constructor or destructor table to declare; Zero Hour's Snapshot inheritance does not describe this target.
Allocation sites 0x0026580B and 0x002EDEEC push 0x28, call operator new at 0x0026580D/0x002EDEEE, and call the constructor at 0x00265820/0x002EDF01: sizeof(Path) is 0x28. appendNode at 0x002655E3 reads the head at +4, tail at +8 and optimized byte at +0x0C. GetNextPortalID at 0x00363AA8 and DoAdvanceAlongPath at 0x00363930 use the selected node at +0x10; the latter stores its segment fraction at +0x14. DoXfer at 0x003661FC transfers the flags at +0x0C/+0x0D, twelve position bytes at +0x18, the float at +0x14 and the integer at +0; its load branch resets +0x24 to -1. Unknown members keep offset names.
The declared out-of-line bodies are the ledger rows at 0x00363DC8, 0x00364A89, 0x00265596, 0x002655E3, 0x003649B1, 0x003641F2, 0x00363B24, 0x00363DF9, 0x00363AA8, 0x0036617B, 0x00364521, 0x003661FC, 0x00363EC0, 0x00363930, 0x00363FA4, 0x00365DF0, 0x001E3549, 0x00365B8A, 0x003641AE, 0x00365E98, 0x003642DF, 0x00364551, 0x00365309 and 0x00364AA2. No rowed body is defined inline. The append caller at 0x00265832 supplies the 0x7FFFFFFF default portal ID.
Donor names: Zero Hour GeneralsMD AIPathfind.h declares m_path, m_pathTail, m_isOptimized, m_blockedByAlly, getFirstNode, getLastNode, markOptimized, setBlockedByAlly and getBlockedByAlly. Their target offsets and accesses are established above; Zero Hour's remaining cache fields and virtual slots are not used.
*/

#pragma once
#ifndef BFME2_PATHFINDPATH_H
#define BFME2_PATHFINDPATH_H

struct Coord3D;
struct DirectionOptions;
class Object;
class PathNode;
enum PathfindLayerEnum;
class Rva0008BB38FloatField;
class Rva00263404Product;
struct Rva003642DFResult;
enum ScienceType;
class Xfer;

namespace _STL
{
template <class T> class allocator;
template <class T, class Allocator> class vector;
}

class Path
{
public:
    Path();
    ~Path();

    void prependNode(const Coord3D *, PathfindLayerEnum, int);
    void appendNode(const Coord3D *, PathfindLayerEnum, int = 0x7FFFFFFF);
    void rva003649B1(const PathNode *);
    Coord3D rva003641F2() const;
    void SetLastNodePortal(int);
    Coord3D *PeekPastClimbPortal(Coord3D *);
    int GetNextPortalID();
    void AdvancePastPortal(ScienceType, _STL::vector<ScienceType, _STL::allocator<ScienceType> > *);
    Rva003642DFResult rva00364521(const Rva0008BB38FloatField *);
    void DoXfer(Xfer *);
    float computeFlightDistToGoal(const Coord3D *, Coord3D &);
    bool DoAdvanceAlongPath(const Coord3D *, bool);
    void optimizeGroundPath(int);
    void SpliceAndPrepend(Rva00263404Product *);
    bool rva001E3549(const Coord3D *);
    void rva00365B8A(Object *, PathNode *, PathNode *, const Coord3D *, float);
    int rva003641AE(float, float);
    void rva00365E98(Object *, const Coord3D *, int, bool);
    Rva003642DFResult rva003642DF(float);
    void rva00364551(Object *, int, bool, const float *);
    bool rva00365309(Object *, PathNode *, const Coord3D *, DirectionOptions *, int, float, bool);
    void rva00364AA2(PathNode *, PathNode *, PathNode *, float);

    PathNode *getFirstNode() { return m_path; }
    PathNode *getFirstNode() const { return m_path; }
    PathNode *getLastNode() { return m_pathTail; }
    PathNode *getLastNode() const { return m_pathTail; }
    void markOptimized() { m_isOptimized = true; }
    void setBlockedByAlly(bool blocked) { m_blockedByAlly = blocked; }
    bool getBlockedByAlly() { return m_blockedByAlly; }

    int field_00;
    PathNode *m_path;
    PathNode *m_pathTail;
    bool m_isOptimized;
    bool m_blockedByAlly;
    PathNode *field_10;
    float field_14;
    float field_18;
    float field_1C;
    float field_20;
    int field_24;
};

#endif
