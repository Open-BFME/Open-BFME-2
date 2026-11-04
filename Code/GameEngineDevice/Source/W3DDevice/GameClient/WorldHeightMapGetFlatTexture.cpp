// cl: /O1 /G7 /arch:SSE /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
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

#include "../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"

#include "../../../../GameEngine/Source/Common/debug.h"
extern Debug *theDebug;
extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(int kind);

#define DEBUG_CRASH_REPORT(MESSAGE) \
	do { \
		if (_bfme_debugReportingEnabled()) { \
			_bfme_debugRecordCallsite(1); \
			theDebug->SkipNext(); \
			(theDebug->CrashBegin(0, 0, 0) << MESSAGE).CrashDone(2); \
		} \
	} while (0)

#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"

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
