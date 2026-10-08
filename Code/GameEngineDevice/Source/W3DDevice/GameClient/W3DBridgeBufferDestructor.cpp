// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// W3DBridgeBuffer::~W3DBridgeBuffer, Zero Hour's body: free the vertex and
// index buffers (the ledger's Rva0074011F, called as freeBridgeBuffers by the
// rowed allocateBridgeBuffers), then destroy the 200 0x114-byte bridges at
// +0x10.

class Rva0074011F
{
public:
	void rva0074011F();
};

class W3DBridge
{
public:
	~W3DBridge();
private:
	char m_pad[0x114];
};

enum { MAX_BRIDGES = 200 };

class W3DBridgeBuffer
{
public:
	~W3DBridgeBuffer();
private:
	void *m_vertexBridge; // +0x00
	void *m_indexBridge; // +0x04
	int m_curNumBridgeVertices; // +0x08
	int m_curNumBridgeIndices; // +0x0C
	W3DBridge m_bridges[MAX_BRIDGES]; // +0x10
	int m_numBridges; // +0xD7B0
	bool m_initialized; // +0xD7B4
};

// ??1W3DBridgeBuffer@@QAE@XZ @0x000DE4EB
W3DBridgeBuffer::~W3DBridgeBuffer()
{
	((Rva0074011F *)this)->rva0074011F();
}
