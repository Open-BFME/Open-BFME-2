/* Target facts (addresses are RVAs):
PathNode has no virtual functions or vtable. Constructor 0x0026212A copies ECX to EAX at 0x0026212A, clears the three link words at +0/+4/+8 at 0x00262132/0x00262134/0x00262137, and makes no base call or vptr store. The nonvirtual scalar deleting destructor 0x003642C8 only tests its delete flag, calls FreePooledNode at 0x00265488 and returns this; its object destructor is empty. MemoryPoolObject's registered virtual destructor does not describe this target class, so PathNode has no declared base.
The same constructor copies the input Coord3D into +0x0C/+0x10/+0x14 at 0x0026213D/0x00262143/0x00262149, writes the PathfindLayerEnum argument to +0x18 at 0x00262150, clears byte +0x1C at 0x00262153 and sets dword +0x20 to 0x7FFFFFFF at 0x00262156. The pool allocator 0x002635C2 allocates 0x1204 bytes at 0x002635EC, links elements at stride 0x24 at 0x0026360B/0x00263614 and stops at 0x1200 bytes: sizeof(PathNode) is 0x24.
Path::appendNode 0x002655E3 links the old tail's +0 to the new node and the new node's +4 to the old tail at 0x00265641/0x00265643; it separately sets the optimized +8 link at 0x00265653. Path::prependNode calls the constructor at 0x002655B2 and the link helper 0x00262161 at 0x002655C9; that helper writes both +0 and +8 and the successor's +4. Path::GetNextPortalID 0x00363AA8 follows +8 at 0x00363AC5 and reads +0x20 at 0x00363AD0. Path::SetLastNodePortal 0x00363B24 writes +0x20 at 0x00363B2F, proving the portal ID field's purpose and sentinel.
The constructor is declared out of line under its ledger spelling. The deleting destructor's call at 0x003642D3 proves pooled deletion through FreePooledNode. Getter bodies expose the proven links, position and layer; no extra optimized-distance or direction fields are present in the 0x24-byte pool element.
Donor facts: Zero Hour GeneralsMD GameLogic/AIPathfind.h names m_next, m_prev, m_nextOpti, m_pos, m_layer, m_canOptimize and the corresponding accessors. Its MemoryPoolObject base, default constructor, leading m_id and cached optimized distance/direction describe a different layout. Only the names of target-supported members are reused; no donor or scoped pathfinding shim is included.
*/

#pragma once
#ifndef BFME2_PATHNODE_H
#define BFME2_PATHNODE_H

#include "../../../Libraries/Include/Lib/Coord3D.h"

enum PathfindLayerEnum;
void __cdecl FreePooledNode(void *node);

class PathNode
{
public:
    PathNode(const Coord3D *position, PathfindLayerEnum layer) throw();
    ~PathNode() {}
    static void operator delete(void *node) { FreePooledNode(node); }

    const Coord3D *getPosition() const { return &m_pos; }
    void setPosition(const Coord3D *position) { m_pos = *position; }
    PathNode *getNext() { return m_next; }
    PathNode *getNext() const { return m_next; }
    PathNode *getPrevious() const { return m_prev; }
    PathNode *getNextOptimized() const { return m_nextOpti; }
    PathfindLayerEnum getLayer() const { return m_layer; }
    void setCanOptimize(bool canOptimize) { m_canOptimize = canOptimize; }
    bool getCanOptimize() const { return m_canOptimize; }

    PathNode *m_next;
    PathNode *m_prev;
    PathNode *m_nextOpti;
    Coord3D m_pos;
    PathfindLayerEnum m_layer;
    bool m_canOptimize;
    int m_portalID;
};

#endif // BFME2_PATHNODE_H
