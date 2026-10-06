// cl: /DNDEBUG /MD /EHsc
// ??0W3DBridgeBuffer@@QAE@XZ 0x000DE52E 110B W3DBridgeBuffer ctor with 200-bridge array via ??_L plus clearAllBridges and allocateBridgeBuffers
// evidence: ??_L pushes 0xC8 0x114 with dtor 0x000DDA6E and ctor 0x000DD97F for bridges at +0x10; nulls +0x0 +0x4 +0x8 +0xC +0xD7B0 and flag +0xD7B4 0 then 1; calls clearAllBridges 0x000DD948 and allocateBridgeBuffers 0x000DD8B8; chain from 0x000DD8B8; caller 0x0006CC2F in 0x0006C9CF
class W3DBridge
{
public:
	W3DBridge();
	~W3DBridge();
private:
	unsigned char m_pad[0x114];
};

class W3DBridgeBuffer
{
public:
	W3DBridgeBuffer();
	void clearAllBridges();
	void allocateBridgeBuffers();
private:
	void *m_vertexBridge;
	void *m_indexBridge;
	int m_08;
	int m_curNumBridgeIndices;
	W3DBridge m_bridges[200];
	int m_numBridges;
	unsigned char m_flagD7B4;
	unsigned char m_flagD7B5;
	unsigned char m_flagD7B6;
	unsigned char m_padTail[0xD7C0 - 0xD7B7];
};

W3DBridgeBuffer::W3DBridgeBuffer()
{
	m_flagD7B4 = 0;
	m_vertexBridge = 0;
	m_indexBridge = 0;
	m_08 = 0;
	m_curNumBridgeIndices = 0;
	m_numBridges = 0;
	clearAllBridges();
	allocateBridgeBuffers();
	m_flagD7B4 = 1;
}
