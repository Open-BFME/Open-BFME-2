// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv624.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoCME@BfmeThingCME@@QAEHPAX@Z 0x0027F0D3 (53B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
#include "Coord3D.h"

struct ICoord2D
{
	int x;
	int y;
};
struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};
class PolygonTrigger
{
public:
	void getCenterPoint(Coord3D *center) const;
	void getBounds(IRegion2D *bounds);
};
class Rva0027D30D
{
public:
	int count;
	PolygonTrigger *trigger;
};
class Rva0027E248
{
public:
	void rva0027E248(Coord3D *center, float radius, Rva0027D30D *result, bool flag, int mode);
};

inline const int &largerDimension(const int &width, const int &height)
{
	return width > height ? width : height;
}

struct BfmeTempCME
{
	BfmeTempCME();
	unsigned char m_bfmeHead[0x14];
	int m_bfmeResult;
};

class BfmeThingCME
{
public:
	void bfmeCallCME(void *what, float value, BfmeTempCME *out, int one, int two);
	int bfmeGoCME(void *what);
	int rva0027F108(void *what, float value, int one, int two);
	int rva0027F171(PolygonTrigger *trigger);
};

int BfmeThingCME::bfmeGoCME(void *what)
{
	BfmeTempCME tmp;
	bfmeCallCME(what, 10.0f, &tmp, 0, 0);
	return tmp.m_bfmeResult;
}

int BfmeThingCME::rva0027F108(void *what, float value, int one, int two)
{
	BfmeTempCME tmp;
	bfmeCallCME(what, value, &tmp, one, two);
	return tmp.m_bfmeResult;
}

// Native 0x0027F171..0x0027F1DD, RET 4. The measured grid-query helper
// 0x0027E248 takes center/radius/result/flag/mode and calls 0x0027D30D,
// whose own body tests result.trigger (+4) and increments result.count (+0).
// The verified PolygonTrigger APIs provide the center and integer bounds.
// BfmeThingCME and the helper names are established opaque ABI views;
// original owner/method identity remains unresolved.
int BfmeThingCME::rva0027F171(PolygonTrigger *trigger)
{
	Rva0027D30D result = { 0, trigger };
	Coord3D center;
	trigger->getCenterPoint(&center);
	IRegion2D bounds;
	trigger->getBounds(&bounds);
	int height = bounds.hi.y - bounds.lo.y;
	int width = bounds.hi.x - bounds.lo.x;
	float radius = static_cast<float>(largerDimension(width, height));
	reinterpret_cast<Rva0027E248 *>(this)->rva0027E248(&center, radius, &result, false, 0);
	return result.count;
}
