// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?rva00312DBC@Rva008B77D@@UAEXXZ, retail 0x00312DBC (14 bytes), slot 3 of the seven-slot
// table 0x007C7514 that the Rva008B77D constructors install (0x0008B790, 0x00312CA8):
// empties the object's 184-byte record vector at +0x2C through the rowed erase 0x00312C44.
// The slot's name is not recovered.
#include <vector>

#include "../../../Libraries/Source/WWVegas/WWLib/BfmeStringHeadRecord184.h"

namespace _STL {
template <> BfmeStringHeadRecord184 *vector<BfmeStringHeadRecord184>::erase(BfmeStringHeadRecord184 *first, BfmeStringHeadRecord184 *last);
}

class Rva008B77D
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void rva00312DBC();
private:
	unsigned char m_pad04[0x2C - 4];
	_STL::vector<BfmeStringHeadRecord184> m_records;		// +0x2C
};

void Rva008B77D::rva00312DBC()
{
	m_records.clear();
}
