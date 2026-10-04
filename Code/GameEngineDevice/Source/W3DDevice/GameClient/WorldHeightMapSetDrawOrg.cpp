// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// WorldHeightMap::setDrawOrg, retail 0x000AC40D (185 bytes): Zero Hour's body
// verbatim over BFME 2's layout. Target facts: width/height at +0x08/+0x0C,
// draw origin and draw size at +0x120E0..+0x120EC, TheGlobalData's
// stretch-terrain and draw-entire-terrain flags at +0x4C/+0x4E, and the
// stretch size 0x41. The ZH-header port in WorldHeightMap.cpp places these
// fields elsewhere, so the body lives here. Retail clamps with cmovg, which
// MSVC 7.1 emits only under /arch:SSE.
typedef int Int;
typedef bool Bool;
enum
{
	STRETCH_DRAW_WIDTH = 65,
	STRETCH_DRAW_HEIGHT = 65
};
class GlobalData
{
public:
	unsigned char m_pad00[0x4C];
	Bool m_stretchTerrain;		// +0x4C
	unsigned char m_pad4D;
	Bool m_drawEntireTerrain;	// +0x4E
};
extern GlobalData *TheGlobalData;
class WorldHeightMap
{
public:
	Bool setDrawOrg(Int xOrg, Int yOrg);
private:
	unsigned char m_pad00[0x08];
	Int m_width;			// +0x08
	Int m_height;			// +0x0C
	unsigned char m_pad10[0x120E0 - 0x10];
	Int m_drawOriginX;		// +0x120E0
	Int m_drawOriginY;		// +0x120E4
	Int m_drawWidthX;		// +0x120E8
	Int m_drawHeightY;		// +0x120EC
};
Bool WorldHeightMap::setDrawOrg(Int xOrg, Int yOrg)
{
	Int newX, newY;
	Int newWidth, newHeight;
	newX = xOrg;
	newY = yOrg;
	newWidth = m_drawWidthX;
	newHeight = m_drawHeightY;
	if (TheGlobalData && TheGlobalData->m_stretchTerrain) {
		newWidth=STRETCH_DRAW_WIDTH;
		newHeight=STRETCH_DRAW_HEIGHT;
	}
	if (TheGlobalData && TheGlobalData->m_drawEntireTerrain) {
		newWidth=m_width;
		newHeight=m_height;
	}
	if (newWidth > m_width) newWidth = m_width;
	if (newHeight > m_height) newHeight = m_height;
	if (newX > m_width - newWidth) newX = m_width-newWidth;
	if (newX<0) newX=0;
	if (newY > m_height - newHeight) newY = m_height - newHeight;
	if (newY<0) newY=0;
	Bool anythingDifferent = (m_drawOriginX!=newX) ||
										 (m_drawOriginY!=newY) ||
										 (m_drawWidthX!=newWidth) ||
										 (m_drawHeightY!=newHeight) ;

	if (anythingDifferent) {
		m_drawOriginX=newX;
		m_drawOriginY=newY;
		m_drawWidthX=newWidth;
		m_drawHeightY=newHeight;
		return(true);
	}
	return(false);
}
