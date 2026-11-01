// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ??6@YAAAVDebug@@AAV0@ABVPath@@@Z retail 0x002E7CCB (93B): the debug-stream
// dump of a path: "[path:", then one "\n  " line per node (from the +0x04
// head along each node's +0x00 link) with "(opt)" before the nodes of the
// optimized chain (followed through each one's +0x08 link), each node's
// +0x0C position through the rowed Coord3D operator<< (0x000050BA), and a
// closing "]\n". Every string goes through Debug's const char * slot (+0x38).
// The Debug view repeats coord3d.cpp's slot layout; Path and PathNode keep
// only the members read here (structural inference from Zero Hour's
// PathNode, whose optimized link this mirrors).

#include "../../Common/debug.h"

class Coord3D;
Debug &operator<<(Debug &debug, const Coord3D &coord);

struct Coord3DView
{
    float x;
    float y;
    float z;
};

class PathNode
{
public:
    PathNode *m_next; // +0x00
    PathNode *m_prev; // +0x04
    PathNode *m_nextOptimized; // +0x08
    Coord3DView m_pos; // +0x0C
};

#include "../../../Include/GameLogic/PathfindPath.h"

Debug &operator<<(Debug &debug, const Path &path)
{
    debug << "[path:";
    PathNode *optimized = path.m_path;
    for (PathNode *node = path.m_path; node; node = node->m_next)
    {
        debug << "\n  ";
        if (node == optimized)
        {
            debug << "(opt)";
            optimized = optimized->m_nextOptimized;
        }
        debug << *(const Coord3D *)&node->m_pos;
    }
    debug << "]\n";
    return debug;
}
