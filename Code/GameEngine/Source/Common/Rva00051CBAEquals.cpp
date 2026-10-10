// cl: /MD
// ?rva00051CBA@Rva00051CBA@@QAEHABV1@@Z @0x00051CBA 38B
// Honest-address equals helper: Coord3D at +0 via rowed equals then byte at +0xC.
// Retail pushes other, calls ?equals@Coord3D@@QBE_NABUCoord3DBase@@@Z, early-false
// on both compares, true returns 1. Unblocks 0x00051CF1. Neighbours use /O1 /MD.
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Libraries/Include/Lib/Coord3DBase.h"

class Rva00051CBA
{
public:
	int rva00051CBA(const Rva00051CBA &other);

private:
	Coord3D m_coord;
	unsigned char m_flag0C;
	char m_pad0D[3];
};

int Rva00051CBA::rva00051CBA(const Rva00051CBA &other)
{
	if (m_coord.equals(asBase(other.m_coord)))
	{
		if (m_flag0C == other.m_flag0C)
			return 1;
	}
	return 0;
}
