// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ?xfer@AI@@UAEXPAVXfer@@@Z, retail 0x002FE799..0x002FE87D (228B, EH):
// a Ghidra-unlisted slot of the AI snapshot table 0x00C073C0. BFME 2 folds
// Zero Hour's AI::crc and AI::xfer into one body: a CRC pass snapshots the
// pathfinder, every TAiData and every AIGroup behind retail's own
// "MARKER:TAiData" / "MARKER:AIGroup" literals (Zero Hour AI.cpp order);
// otherwise it writes version 1, m_nextGroupID and m_nextFormationID's bytes.
// Xfer slots follow the ledger's LivingWorld snapshot view (3 IsCRC,
// 9 user bytes, 12 xferSnapshot, 27 xferAsciiString, 30 unsigned int).
#include "ascii_string.h"
#include "Common/Snapshot.h"
#include <list>

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"

class PathfinderBase
{
public:
	virtual void b0();
};

#include "../../../Include/GameLogic/AIPathfind.h"

#include "../../../Include/GameLogic/TAiData.h"

#include "../../../Include/GameLogic/AIGroup.h"

#include "../../../Include/GameLogic/AI.h"

void AI::xfer(Xfer *xfer)
{
	if (xfer->IsCRC())
	{
		*xfer == static_cast<Snapshot &>(*m_pathfinder);

		AsciiString marker;
		TAiData *aiData = m_aiData;
		while (aiData)
		{
			marker = "MARKER:TAiData";
			*xfer == marker;
			*xfer == static_cast<Snapshot &>(*aiData);
			aiData = aiData->m_next;
		}

		// Compare the public node identities directly, preserving the inlined walk
		// without emitting this TU's non-retail iterator-comparison COMDAT.
		for (_STL::list<AIGroup *>::iterator groupIt = m_groupList.begin(); groupIt._M_node != m_groupList.end()._M_node; ++groupIt)
		{
			if (*groupIt)
			{
				marker = "MARKER:AIGroup";
				*xfer == marker;
				*xfer == static_cast<Snapshot &>(**groupIt);
			}
		}
	}
	else
	{
		xfer->Version1();
		*xfer == m_nextGroupID;
		xfer->XferRawBytes(&m_nextFormationID, 4);
	}
}
