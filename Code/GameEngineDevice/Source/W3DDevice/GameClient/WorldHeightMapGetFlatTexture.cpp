// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native AE989..AEAA6 RET28, 285B: BFME 2's WorldHeightMap flat-texture
// builder, the Zero Hour getFlatTexture twin.
//
// Target evidence: W3DTerrainBackground::updateTexture (0x001125BE) and
// doTesselatedUpdate (0x001149EB) call it at the points where Zero Hour's
// W3DTerrainBackground calls m_map->getFlatTexture(m_xOrigin, m_yOrigin,
// m_width, pixelsPerCell). The body scales pixelsPerCell by the texture
// reduction getter 0x00117C00 (WW3D::Get_Texture_Reduction), rounds the texture width up to a power of two,
// builds the one-word holder 0x000EF902 and fills it through updateFlat
// (0x000EF2C1, format 0x19) or updateFlatDXT1 (0x000EF4A3, 'DXT1'), else
// reports "Unsupported format for terrain texture". The sixth argument is
// pushed as a whole word into both fill calls' tile-kind slot, so it is an
// int here (callers pass 0 or 1).
// Donor: BFME 1 WorldHeightMapRva0074C4F0.cpp (open-bfme-1 cee35b7d8),
// adapted to BFME 2's reduction getter, the forwarded tile kind and the
// RefCountPtr return, whose inline copy adds the WORD reference at +4.
class TextureClass
{
public:
	void Add_Ref() { ++m_numRefs; }
	void Release_Ref();
	char m_pad00[0x4];
private:
	unsigned short m_numRefs; // +0x04
};

template<class T> class RefCountPtr
{
public:
	RefCountPtr(const RefCountPtr &rhs) : m_ptr(rhs.m_ptr) { if (m_ptr) m_ptr->Add_Ref(); }
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }
private:
	T *m_ptr;
};

class Rva000EF902 : public RefCountPtr<TextureClass>
{
public:
	Rva000EF902(int width, int height, int format);
};

class WorldHeightMap;

class TileData;
class TerrainTextureClass
{
public:
	int updateFlat(WorldHeightMap *htMap, int xCell, int yCell, int cellWidth, int pixelsPerCell, int tileKind);
	int updateFlatDXT1(WorldHeightMap *htMap, int xCell, int yCell, int cellWidth, int pixelsPerCell, int tileKind);
	int updateCliff(TileData**,int,int,int,int);
};

class WW3D
{
public:
	static int Get_Texture_Reduction(void);
};

class BfmeAwakenLog
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void slot4C(int report);
};
class Debug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second, int third);
};
extern Debug *theDebug;
extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(int kind);

#define DEBUG_CRASH_REPORT(MESSAGE) \
	do { \
		if (_bfme_debugReportingEnabled()) { \
			_bfme_debugRecordCallsite(1); \
			theDebug->slot60(); \
			theDebug->slot6C(0, 0, 0)->slot38(MESSAGE)->slot4C(2); \
		} \
	} while (0)

class WorldHeightMap
{
public:
	RefCountPtr<TextureClass> getFlatTexture(int xCell, int yCell, int cellWidth,
		int pixelsPerCell, int format, int tileKind);
};

RefCountPtr<TextureClass> WorldHeightMap::getFlatTexture(int xCell, int yCell,
	int cellWidth, int pixelsPerCell, int format, int tileKind)
{
	if (WW3D::Get_Texture_Reduction() > 0) {
		if (WW3D::Get_Texture_Reduction() > 1)
			pixelsPerCell /= 4;
		else
			pixelsPerCell /= 2;
	}

	int width = 1;
	while (width < cellWidth * pixelsPerCell)
		width *= 2;

	Rva000EF902 texture(width, width, format);
	if (format == 0x19)
		((TerrainTextureClass *)&texture)->updateFlat(this, xCell, yCell,
			cellWidth, pixelsPerCell, tileKind);
	else if (format == 0x31545844)
		((TerrainTextureClass *)&texture)->updateFlatDXT1(this, xCell, yCell,
			cellWidth, pixelsPerCell, tileKind);
	else
		DEBUG_CRASH_REPORT("Unsupported format for terrain texture");
	return texture;
}
