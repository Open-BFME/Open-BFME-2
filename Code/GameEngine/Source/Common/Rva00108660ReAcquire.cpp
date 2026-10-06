// cl: /DNDEBUG /MD /EHsc
// ?ReAcquireResources@Rva00108660ResourceManager@@QAE_NXZ @0x00108660 140B leaf
// Re-acquires index and vertex buffers: new DX8IndexBuffer(0x10000,1) at +0x258,
// new BfmeDynamicNativeVB(0x242,0x8000,1,0) at +0x254. Returns false if first
// null, else second non-null. Caller W3DShadowManager::ReAcquireResources.
// Callees new at 0x0002FDA0, DX8IB at 0x00138980, BfmeVB at 0x0013AC00 rowed.
// Neighbour BfmeConv928 shares /O1 /EHsc flags; no floats.
class DX8IndexBufferClass
{
public:
	enum UsageType
	{
		USAGE_1 = 1
	};
	DX8IndexBufferClass(unsigned indexCount, UsageType usage);
private:
	unsigned char m_pad[0x18];
};
class BfmeDynamicNativeVB
{
public:
	BfmeDynamicNativeVB(unsigned fvf, unsigned short count, unsigned usage, unsigned fvfSize);
private:
	unsigned char m_pad[0x20];
};
class Rva00108660ResourceManager
{
public:
	bool ReAcquireResources();
private:
	unsigned char m_pad00[0x254];
	BfmeDynamicNativeVB *m_vb;
	DX8IndexBufferClass *m_ib;
};

bool Rva00108660ResourceManager::ReAcquireResources()
{
	DX8IndexBufferClass *ib = new DX8IndexBufferClass(0x10000, (DX8IndexBufferClass::UsageType)1);
	m_ib = ib;
	if (!ib)
		return false;
	BfmeDynamicNativeVB *vb = new BfmeDynamicNativeVB(0x242, 0x8000, 1, 0);
	m_vb = vb;
	return vb;
}
