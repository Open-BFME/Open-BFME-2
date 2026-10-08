// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// W3DBridgeBuffer::loadBridgesInVertexAndIndexBuffers, Zero Hour's refill of
// the bridge vertex and index buffers. BFME 2 holds its DX8 device lock across
// the refill, discards both buffers (D3DLOCK_DISCARD) and also skips the work
// when no bridges are loaded. Its locks are 12 bytes, each carrying a device
// lock; bridges are 0x114 bytes from +0x10 with the count at +0xD7B0.

extern void BFME_DX8_Thread_Lock(void);
extern void BFME_DX8_Thread_Assert(void);

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class IndexBufferClass
{
public:
	class WriteLockClass
	{
		BFMEDX8DeviceLock device_lock;
		unsigned short *indices;
		IndexBufferClass *index_buffer;
	public:
		WriteLockClass(IndexBufferClass *index_buffer, int flags = 0);
		~WriteLockClass();
		unsigned short *Get_Index_Array() { return indices; }
	};
};

class VertexBufferClass
{
public:
	class WriteLockClass
	{
		BFMEDX8DeviceLock device_lock;
		void *Vertices;
		VertexBufferClass *VertexBuffer;
	public:
		WriteLockClass(VertexBufferClass *vertex_buffer, int flags = 0);
		~WriteLockClass();
		void *Get_Vertex_Array() { return Vertices; }
	};
};

struct VertexFormatXYZNDUV1;
class RenderObjClass;
template <class T> class RefMultiListIterator;
typedef RefMultiListIterator<RenderObjClass> RefRenderObjListIterator;

class W3DBridge
{
public:
	void getIndicesNVertices(unsigned short *destination_ib, VertexFormatXYZNDUV1 *destination_vb, int *curIndexP, int *curVertexP, RefRenderObjListIterator *pLightsIterator);
private:
	char m_pad[0x114];
};

enum { MAX_BRIDGES = 200 };

class W3DBridgeBuffer
{
public:
	void loadBridgesInVertexAndIndexBuffers(RefRenderObjListIterator *pLightsIterator);
private:
	VertexBufferClass *m_vertexBridge; // +0x00
	IndexBufferClass *m_indexBridge; // +0x04
	int m_curNumBridgeVertices; // +0x08
	int m_curNumBridgeIndices; // +0x0C
	W3DBridge m_bridges[MAX_BRIDGES]; // +0x10
	int m_numBridges; // +0xD7B0
	bool m_initialized; // +0xD7B4
};

// ?loadBridgesInVertexAndIndexBuffers@W3DBridgeBuffer@@QAEXPAV?$RefMultiListIterator@VRenderObjClass@@@@@Z @0x000DF52C
void W3DBridgeBuffer::loadBridgesInVertexAndIndexBuffers(RefRenderObjListIterator *pLightsIterator)
{
	if (!m_indexBridge || !m_vertexBridge || !m_initialized || !m_numBridges)
		return;

	m_curNumBridgeVertices = 0;
	m_curNumBridgeIndices = 0;
	BFMEDX8DeviceLock lock;
	IndexBufferClass::WriteLockClass lockIdxBuffer(m_indexBridge, 0x2000);
	VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexBridge, 0x2000);
	VertexFormatXYZNDUV1 *vb = (VertexFormatXYZNDUV1 *)lockVtxBuffer.Get_Vertex_Array();
	unsigned short *ib = lockIdxBuffer.Get_Index_Array();
	for (int curBridge = 0; curBridge < m_numBridges; curBridge++)
		m_bridges[curBridge].getIndicesNVertices(ib, vb, &m_curNumBridgeIndices, &m_curNumBridgeVertices, pLightsIterator);
}
