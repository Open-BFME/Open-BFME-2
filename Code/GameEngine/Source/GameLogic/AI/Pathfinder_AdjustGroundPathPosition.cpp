// cl: /DNDEBUG /MD /EHsc
// ?AdjustGroundPathPosition@Pathfinder@@QAEHPBUCoord3D@@PAU2@@Z @0x002EDFBD 60B Pathfinder helper: builds Rva002E7B02 info from this+4+*a then calls rowed rva002EB3D7 and copies back 12B on success. Evidence: rowed callees 0x002E7B02 0x002EB3D7, callers 0x002EFA95 0x00371721, neighbours share flags.
typedef int Int;
typedef float Real;
#include "../../../../Libraries/Include/Lib/Coord3D.h"
enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_ONE = 1
};
struct _Rva002E7B02Cell
{
	Real x;
	Real y;
	Real z;
};
class Rva002E7B02
{
public:
	Rva002E7B02(int lhs, int rhs, const _Rva002E7B02Cell &cell);
public:
	int m_00;
	int m_04;
	Real m_08;
	Real m_0C;
	Real m_10;
};
struct Rva002E7B29Info
{
	int m_00;
	int m_04;
	Real m_08;
	Real m_0C;
	Real m_10;
};
#include "../../../Include/GameLogic/AIPathfind.h"
int Pathfinder::AdjustGroundPathPosition(const Coord3D *lhs, Coord3D *rhs)
{
	Rva002E7B02 info((int)this, 4, *(const _Rva002E7B02Cell *)lhs);
	int ret = rva002EB3D7(lhs, rhs, LAYER_ONE, (Rva002E7B29Info *)&info);
	if (ret != 0)
	{
		*rhs = *(const Coord3D *)&info.m_08;
	}
	return ret;
}
