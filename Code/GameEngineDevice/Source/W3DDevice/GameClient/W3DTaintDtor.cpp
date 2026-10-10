// cl: /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// ??1W3DTaint@@QAE@XZ, retail 0x00073BFE (124 bytes, EH). Destructor of the
// class W3DTaint.cpp builds (ctor 0x00074136; this unit keeps a
// destructor-only view of the same members). Target facts: the resource
// release 0x000728E2 first, then the three heap arrays at +0x18 (taint
// colours), +0x38 and +0x3C (cell levels) are delete[]d and cleared, the dirty
// cell set at +0x44 unwinds through its tree destructor (0x000730DE, spelled
// with the owner class the ledger rows it under) and the +0x1C texture handle
// drops its reference (TextureBaseClass::Release_Ref 0x0061ED10).
void __cdecl operator delete[](void *block) throw();
class TextureClass
{
public:
	void Release_Ref();
};

class ShroudTextureHandle
{
public:
	ShroudTextureHandle() : m_p(0) {}
	~ShroudTextureHandle() { if (m_p) m_p->Release_Ref(); }
	TextureClass *m_p;
};

class Rva000728E2
{
public:
	void rva000728E2();
};

class Rva00072FE6
{
public:
	~Rva00072FE6();
	char m_data[12];
};

class W3DTaint
{
public:
	~W3DTaint();
private:
	unsigned int m_numCellsX, m_numCellsY;
	int m_numMaxVisibleCellsX, m_numMaxVisibleCellsY;
	float m_cellWidth, m_cellHeight;
	unsigned int *m_taintData;
	ShroudTextureHandle m_dstTexture;
	int m_dstTextureWidth, m_dstTextureHeight;
	int m_taintFilter;
	float m_drawOriginX, m_drawOriginY;
	unsigned char m_drawTaint, m_clearDstTexture, m_borderTaintLevel, m_pad37;
	unsigned char *m_cellLevels, *m_referenceCellLevels;
	unsigned char m_trackDirtyCells;
	char m_pad41[3];
	Rva00072FE6 m_dirty;
};

W3DTaint::~W3DTaint()
{
	reinterpret_cast<Rva000728E2 *>(this)->rva000728E2();
	if (m_taintData)
		delete [] m_taintData;
	m_taintData = 0;
	if (m_cellLevels)
		delete [] m_cellLevels;
	m_cellLevels = 0;
	if (m_referenceCellLevels)
		delete [] m_referenceCellLevels;
	m_referenceCellLevels = 0;
}
