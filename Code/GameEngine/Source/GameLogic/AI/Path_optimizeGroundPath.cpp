// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// BF1 clean donor0bef PathOptimizeGround.cpp is semantic guide.
// Target363FA4..3641AE RET4; caller2EF908 passes pathDiameter.
// Target layer classification calls rowed2E6E6C; AI.pathfinder target+10.
// Name address-derived: donor purpose and ABI supported; original spelling unresolved.
// BFME's ground-path optimizer takes only the path diameter. It accepts both
// ground and bridge layers in its transition scan, then shortcuts passable
// segments and removes very short optimized middle nodes.

typedef int Int;
typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1,
	LAYER_FIRST_BRIDGE = 16
};

#include "Lib/Coord3D.h"
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathNode
{
public:
	// Both getters inline in the native optimizer. Suppress their surplus
	// standalone copies without changing the member accesses or call ABI.
	__declspec(dllimport) __forceinline PathNode *getNext(void) const { return m_next; }
	PathNode *getPrevious(void) const { return m_previous; }
	PathNode *getNextOptimized(void) const { return m_nextOptimized; }
	const Coord3D *getPosition(void) const { return &m_position; }
	__declspec(dllimport) __forceinline PathfindLayerEnum getLayer(void) const { return m_layer; }

private:
	friend class Path;
	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	PathfindLayerEnum m_layer;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
#include "../../../Include/GameLogic/AIPathfind.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
#include "../../../Include/GameLogic/AI.h"

// 0x00DFF0F8 is retail's TheAI singleton: `extern AI *TheAI`. The AI class
// above is that same name, so the reference below carries retail's spelling
// and mangles to ?TheAI@@3PAVAI@@A.
extern AI *TheAI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
#include "../../../Include/GameLogic/PathfindPath.h"

Int isGroundOrBridgeLayer(Int);
// ?optimizeGroundPath@Path@@QAEXH@Z
void Path::optimizeGroundPath(Int pathDiameter)
{
	PathNode *node, *anchor;

	anchor = m_path;

	while (anchor != m_pathTail)
	{
		Bool optimizedSegment = false;
		PathfindLayerEnum layer = anchor->getLayer();
		PathfindLayerEnum curLayer = anchor->getLayer();
		Int count = 0;
		const Int ALLOWED_STEPS = 3;
		PathNode *next;
		// The same-valued conditional keeps 'node = next' a distinct value, so the
		// next load goes through the copy (MOV EBX,[ESI]) as in retail instead of
		// being propagated to the original (MOV EBX,[EBX]).
		for (node = anchor->getNext(), next = node->getNext(); next; node = (next ? next : next), next = node->getNext())
		{
			count++;
			if (static_cast<unsigned char>(isGroundOrBridgeLayer(curLayer)))
			{
				if (node->getLayer() != curLayer)
				{
					layer = node->getLayer();
					curLayer = layer;
					if (count > ALLOWED_STEPS)
						break;
				}
			}
			else if (next->getLayer() != curLayer)
			{
				if (count > ALLOWED_STEPS)
					break;
			}
			curLayer = node->getLayer();
		}

		for (; node != anchor; node = node->getPrevious())
		{
			Bool isPassable = false;
			if (TheAI->pathfinder()->IsGroundPathPassable(
				anchor->getPosition(), layer, node->getPosition(), pathDiameter))
			{
				isPassable = true;
			}

			if (!isPassable)
			{
				Int dx = node->getPosition()->x - anchor->getPosition()->x;
				Int dy = node->getPosition()->y - anchor->getPosition()->y;
				Bool mightBePassable = false;
				PathNode *pathNode;
				if (dx == 0)
				{
					mightBePassable = true;
					for (pathNode = node->getPrevious(); pathNode && pathNode != anchor;
						pathNode = pathNode->getPrevious())
					{
						dx = pathNode->getNext()->getPosition()->x - pathNode->getPosition()->x;
						if (dx != 0)
							mightBePassable = false;
					}
				}
				if (dy == 0)
				{
					mightBePassable = true;
					for (pathNode = node->getPrevious(); pathNode && pathNode != anchor;
						pathNode = pathNode->getPrevious())
					{
						dy = pathNode->getNext()->getPosition()->y - pathNode->getPosition()->y;
						if (dy != 0)
							mightBePassable = false;
					}
				}
				if (dx == dy)
				{
					mightBePassable = true;
					for (pathNode = node->getPrevious(); pathNode && pathNode != anchor;
						pathNode = pathNode->getPrevious())
					{
						dx = pathNode->getNext()->getPosition()->x - pathNode->getPosition()->x;
						dy = pathNode->getNext()->getPosition()->y - pathNode->getPosition()->y;
						if (dy != dx)
							mightBePassable = false;
					}
				}
				if (dx == -dy)
				{
					mightBePassable = true;
					for (pathNode = node->getPrevious(); pathNode && pathNode != anchor;
						pathNode = pathNode->getPrevious())
					{
						dx = pathNode->getNext()->getPosition()->x - pathNode->getPosition()->x;
						dy = pathNode->getNext()->getPosition()->y - pathNode->getPosition()->y;
						if (dy != -dx)
							mightBePassable = false;
					}
				}
				if (mightBePassable)
					isPassable = true;
			}

			if (isPassable)
			{
				anchor->m_nextOptimized = node;
				anchor = node;
				optimizedSegment = true;
				break;
			}
		}

		if (optimizedSegment == false)
		{
			anchor->m_nextOptimized = anchor->getNext();
			anchor = anchor->getNext();
		}
	}

	for (anchor = m_path; anchor != 0; anchor = anchor->getNextOptimized())
	{
		node = anchor->getNextOptimized();
		if (node && node->getNextOptimized())
		{
			Real dx = node->getPosition()->x - anchor->getPosition()->x;
			Real dy = node->getPosition()->y - anchor->getPosition()->y;
			if (dx * dx + dy * dy < 390.0f)
				anchor->m_nextOptimized = node->getNextOptimized();
		}
	}

	m_isOptimized = true;
}
