// ?isCellOnSide@Bridge@@QAE_NPBURegion2D@@@Z
// partial score=0.94 date=2026-10-05
// cl: /O1 /Ireference/shims/meshgeom /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?isCellOnSide@Bridge@@QAE_NPBURegion2D@@@Z @0x0027C95B 548B
// Evidence: ZH donor GeneralsMD TerrainLogic.cpp Bridge::isCellOnSide verbatim; retail 4x LineInRegion calls plus caller 0x00366FB0 passing Region2D with ecx=[ebx+0x34] Bridge; corners at +0x28/+0x34/+0x40/+0x4c match BridgeIsPointOnBridge layout.

#define PATHFIND_CELL_SIZE 10

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
	void normalize();
};

struct Coord2D
{
	float x, y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Region2D
{
	float loX;
	float loY;
	float hiX;
	float hiY;
};

bool LineInRegion(const Coord2D *p1, const Coord2D *p2, const Region2D *clipRegion);

class PolygonTrigger;

class Bridge
{
public:
	bool isCellOnSide(const Region2D *cell);

private:
	char m_pad00[0x28];
	Coord3D m_fromLeft;
	Coord3D m_fromRight;
	Coord3D m_toLeft;
	Coord3D m_toRight;
	char m_pad58[0xB4 - 0x58];
	Region2D m_bounds;
	int m_layer;
	PolygonTrigger *m_extra;
};

// ?isCellOnSide@Bridge@@QAE_NPBURegion2D@@@Z present-unmatched
bool Bridge::isCellOnSide(const Region2D *cell)
{
	Coord3D endVector;
	endVector.x = m_fromRight.x - m_fromLeft.x;
	endVector.y = m_fromRight.y - m_fromLeft.y;
	endVector.z = m_fromRight.z - m_fromLeft.z;
	endVector.normalize();
	// Offset by 1 pathfind cell.
	endVector.y *= PATHFIND_CELL_SIZE*0.51f;
	endVector.x *= PATHFIND_CELL_SIZE*0.51f;

	Coord3D fromLeft, fromRight, toLeft, toRight;
	fromLeft.x = m_fromLeft.x - endVector.x;
	fromLeft.y = m_fromLeft.y - endVector.y;
	fromRight.x = m_fromRight.x + endVector.x;
	fromRight.y = m_fromRight.y + endVector.y;
	toLeft.x = m_toLeft.x - endVector.x;
	toLeft.y = m_toLeft.y - endVector.y;
	toRight.x = m_toRight.x + endVector.x;
	toRight.y = m_toRight.y + endVector.y;

	Coord2D line1, line2;
	line1.x = fromLeft.x;
	line1.y = fromLeft.y;
	line2.x = toLeft.x;
	line2.y = toLeft.y;
	if (LineInRegion(&line1, &line2, cell)) {
		return true;
	}
	line1.x = fromRight.x;
	line1.y = fromRight.y;
	line2.x = toRight.x;
	line2.y = toRight.y;
	if (LineInRegion(&line1, &line2, cell)) {
		return true;
	}
	fromLeft.x -= endVector.x;
	fromLeft.y -= endVector.y;

	fromRight.x += endVector.x;
	fromRight.y += endVector.y;

	toLeft.x -= endVector.x;
	toLeft.y -= endVector.y;

	toRight.x += endVector.x;
	toRight.y += endVector.y;

	line1.x = fromLeft.x;
	line1.y = fromLeft.y;
	line2.x = toLeft.x;
	line2.y = toLeft.y;
	if (LineInRegion(&line1, &line2, cell)) {
		return true;
	}
	line1.x = fromRight.x;
	line1.y = fromRight.y;
	line2.x = toRight.x;
	line2.y = toRight.y;
	if (LineInRegion(&line1, &line2, cell)) {
		return true;
	}
	return(false);
}
