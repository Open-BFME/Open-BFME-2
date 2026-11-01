// cl: /DNDEBUG /MD
//
// ?friend_setPath@AIUpdateInterface@@QAEXPAVPath@@@Z, retail 0x00262AF9, 22 bytes.
// ZH donor AIUpdate.cpp friend_setPath verbatim: destroyPath then m_path at
// +0x140 from the Path pointer arg. Layout follows the landed destroyPath
// 0x00262A8A row via GameLogicDestroyObject with m_path at +0x140. Single
// rowed callee destroyPath; six callers including path helpers.

class Path;

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::friend_setPath(Path *newPath)
{
	destroyPath();
	m_path = newPath;
}
