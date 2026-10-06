// cl: /DNDEBUG /MD /EHsc
// ?allocateBridgeBuffers@W3DBridgeBuffer@@QAEXXZ 0x000DD8B8 144B W3DBridgeBuffer::allocateBridgeBuffers from BFME1 donor W3DBridgeBufferAllocateBridgeBuffers.cpp; evidence: free call 0x0074011F when VB or IB present VB new 0x20 ctor 0x0013AC00 args 0x152 0x1F44 1 0 IB new 0x18 ctor 0x00138980 args 0x3E84 1 counts +8 +12 zeroed callers 0x00066A14 0x000DE581
class Rva0074011F
{
public:
	void rva0074011F();
};

class BfmeDynamicNativeVB
{
public:
	BfmeDynamicNativeVB(unsigned int fvf, unsigned short count, unsigned int usage, unsigned int size);
private:
	unsigned char m_pad[0x20];
};

class DX8IndexBufferClass
{
public:
	enum UsageType
	{
		USAGE_DEFAULT = 0,
		USAGE_DYNAMIC = 1
	};
	DX8IndexBufferClass(unsigned int count, UsageType usage);
private:
	unsigned char m_pad[0x18];
};

class W3DBridgeBuffer
{
public:
	void allocateBridgeBuffers();
private:
	BfmeDynamicNativeVB *m_vertexBridge;
	DX8IndexBufferClass *m_indexBridge;
	int m_08;
	int m_0C;
};

void W3DBridgeBuffer::allocateBridgeBuffers()
{
	if (m_vertexBridge || m_indexBridge)
		((Rva0074011F *)this)->rva0074011F();
	m_vertexBridge = new BfmeDynamicNativeVB(0x152, 0x1F44, 1, 0);
	m_indexBridge = new DX8IndexBufferClass(0x3E84, DX8IndexBufferClass::USAGE_DYNAMIC);
	m_08 = 0;
	m_0C = 0;
}
