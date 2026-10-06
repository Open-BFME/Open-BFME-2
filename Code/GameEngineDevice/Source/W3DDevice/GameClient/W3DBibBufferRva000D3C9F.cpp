// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
//
// ?allocateBibBuffers@W3DBibBuffer@@IAEXXZ, retail 0x000d3c9f, 150 bytes. Banked partial (score 0.96) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// frees existing buffers when either slot is set, then global-new BfmeDynamicNativeVB
// (0x20B rowed ??0BfmeDynamicNativeVB@@QAE@IGII@Z, FVF 0x142, word-sized vertex
// count at +4) and DX8IndexBufferClass (0x18B rowed ??0DX8IndexBufferClass@@QAE@IW4UsageType@0@@Z,
// dword index count at +0xC) and zeroes the used counts. Evidence: retail pushes
// 0x20/0x18 to rowed ??2@YAPAXI@Z, calls rowed freeBibBuffers at 0x000D3C74,
// neighbours freeBibBuffers/clearAllBibs in W3DBibBuffer.cpp, callers at
// 0x000669F6 and 0x000D431B. TU-local views: ZH headers declare the old DX8-only
// shapes, so the BFME2 dynamic-buffer types live here.
class BfmeDynamicNativeVB
{
public:
	BfmeDynamicNativeVB(unsigned, unsigned short, unsigned, unsigned);
private:
	char m_pad[0x20];
};
class DX8IndexBufferClass
{
public:
	enum UsageType
	{
		USAGE_DYNAMIC = 1
	};
	DX8IndexBufferClass(unsigned, UsageType);
private:
	char m_pad[0x18];
};
class W3DBibBuffer
{
protected:
	void allocateBibBuffers();
	void freeBibBuffers();
private:
	BfmeDynamicNativeVB *m_vertexBib;
	unsigned short m_vertexBibSize;
	DX8IndexBufferClass *m_indexBib;
	int m_indexBibSize;
	char m_pad10[8];
	int m_curNumBibVertices;
	int m_curNumBibIndices;
};
void W3DBibBuffer::allocateBibBuffers()
{
	if (m_vertexBib || m_indexBib)
		freeBibBuffers();
	m_vertexBib = new BfmeDynamicNativeVB(0x142, m_vertexBibSize + 4, 1, 0);
	m_indexBib = new DX8IndexBufferClass((unsigned)m_indexBibSize + 4, DX8IndexBufferClass::USAGE_DYNAMIC);
	m_curNumBibVertices = 0;
	m_curNumBibIndices = 0;
}
