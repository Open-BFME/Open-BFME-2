// cl: /D_OPERATOR_NEW_DEFINED_ /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Include /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ?rva0006692C@BaseHeightMapRenderObjClass@@UAEXXZ, retail 0x0006692C..0x00066962
// (54 bytes, ends in a tail jump). The terrain's device-resource teardown
// helper: releases the water reflection resources held by the global at VA
// 0x00DE2000 (rowed 0x0007E12F), frees the shrub (+0x3854) and tree
// (+0x3850) buffer batches through the rowed 0x000E6B99, and tail-jumps
// into W3DShaderManager::shutdown. WorldBuilder's twin (0x00752340) shows
// the same three steps with the water texture release named. Original
// method name unknown.

extern void *W3DGCData00DE2000;

class Rva0007E12F { public: void rva0007E12F(); };
#include "../../../../GameEngine/Include/Common/Rva000EC9C6.h"
#include "../../../Include/W3DDevice/GameClient/W3DShaderManagerClass.h"

#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

void BaseHeightMapRenderObjClass::rva0006692C()
{
	if (W3DGCData00DE2000)
		((Rva0007E12F *)W3DGCData00DE2000)->rva0007E12F();
	if (m_shrubBuffer)
		((Rva000EC9C6 *)m_shrubBuffer)->rva000E6B99();
	if (m_treeBuffer)
		((Rva000EC9C6 *)m_treeBuffer)->rva000E6B99();
	W3DShaderManager::shutdown();
}
