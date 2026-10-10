// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva0006692C@BaseHeightMapRenderObjClass@@QAEXXZ, retail 0x0006692C..0x00066962
// (54 bytes, ends in a tail jump). The terrain's device-resource teardown
// helper: releases the water reflection resources held by the global at VA
// 0x00DE2000 (rowed 0x0007E12F), frees the shrub (+0x3854) and tree
// (+0x3850) buffer batches through the rowed 0x000E6B99, and tail-jumps
// into W3DShaderManager::shutdown. WorldBuilder's twin (0x00752340) shows
// the same three steps with the water texture release named. Original
// method name unknown.

extern void *W3DGCData00DE2000;

class Rva0007E12F { public: void rva0007E12F(); };
class Rva000EC9C6 { public: void rva000E6B99(); };
class W3DShaderManager { public: static void shutdown(); };

class BaseHeightMapRenderObjClass
{
public:
	void rva0006692C();

private:
	char m_pad00[0x3850];
	Rva000EC9C6 *m_treeBuffer;	// +0x3850
	Rva000EC9C6 *m_shrubBuffer;	// +0x3854
};

void BaseHeightMapRenderObjClass::rva0006692C()
{
	if (W3DGCData00DE2000)
		((Rva0007E12F *)W3DGCData00DE2000)->rva0007E12F();
	if (m_shrubBuffer)
		m_shrubBuffer->rva000E6B99();
	if (m_treeBuffer)
		m_treeBuffer->rva000E6B99();
	W3DShaderManager::shutdown();
}
