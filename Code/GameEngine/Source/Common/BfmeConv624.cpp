// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv624.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoCME@BfmeThingCME@@QAEHPAX@Z 0x0027F0D3 (53B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
#include "Coord3D.h"

#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/IRegion2D.h"
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

class Rva0027D35F
{
public:
	unsigned char value;
	// The caller's context occupies an aligned argument word. Only its low
	// byte is initialized or read; the remaining bytes have no asserted data.
	unsigned char m_unwritten[3];
};
class Rva0027E79E
{
public:
	void rva0027E79E(Coord3D *center, float radius, Rva0027D35F *result, bool flag, int mode);
};

inline const int &largerDimension(const int &width, const int &height)
{
	return width > height ? width : height;
}

struct BfmeTempCME
{
	unsigned char m_bfmeHead[0x14];
	int m_bfmeResult;
};

// LINK: the temp's initializer and the grid query are rowed under their retail
// names (0x0027D1C6, 0x0027DCF2); the views keep the call shapes.
class Rva0027D1C6
{
public:
	Rva0027D1C6 *rva0027D1C6();
};
class Rva0027D244;
class Rva0027DCF2
{
public:
	void rva0027DCF2(Coord3D *center, float radius, Rva0027D244 *result, bool flag, int mode);
};
typedef void (Rva0027DCF2::*Rva0027DCF2Shape)(void *, float, void *, int, int);

class BfmeThingCME
{
public:
	int bfmeGoCME(void *what);
	int rva0027F108(void *what, float value, int one, int two);
	int rva0027F171(PolygonTrigger *trigger);
	void rva0027F2B2(Coord3D *center, float radius, unsigned char value);
};

int BfmeThingCME::bfmeGoCME(void *what)
{
	BfmeTempCME queryResult;
	((Rva0027D1C6 *)&queryResult)->rva0027D1C6();
	(((Rva0027DCF2 *)this)->*reinterpret_cast<Rva0027DCF2Shape>(&Rva0027DCF2::rva0027DCF2))(what, 10.0f, &queryResult, 0, 0);
	return queryResult.m_bfmeResult;
}

int BfmeThingCME::rva0027F108(void *what, float value, int one, int two)
{
	BfmeTempCME queryResult;
	((Rva0027D1C6 *)&queryResult)->rva0027D1C6();
	(((Rva0027DCF2 *)this)->*reinterpret_cast<Rva0027DCF2Shape>(&Rva0027DCF2::rva0027DCF2))(what, value, &queryResult, one, two);
	return queryResult.m_bfmeResult;
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

// Native 0x0027F2B2..0x0027F2D6, RET 12. The third argument initializes
// the one-byte context consumed by the rowed 0x0027D35F callback, reached
// through the 683-byte grid query at 0x0027E79E. The two filter args are zero.
void BfmeThingCME::rva0027F2B2(Coord3D *center, float radius, unsigned char value)
{
	Rva0027D35F result;
	result.value = value;
	reinterpret_cast<Rva0027E79E *>(this)->rva0027E79E(center, radius, &result, false, 0);
}
