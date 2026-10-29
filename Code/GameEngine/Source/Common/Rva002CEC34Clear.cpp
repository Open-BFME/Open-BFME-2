// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva002CEC34@Rva002CEC0A@@QAEXXZ @0x002CEC34 14B
// Clears the vector<AsciiString> at +4 via the rowed erase at 0x0002CCFC.
// Same class and member as Rva002CEC0ADtor (dtor at 0x002CEC0A tail-calls
// the vector dtor; this method erases begin/end). Callers at 0x002297EB
// 0x002458F2 0x002CED4F prove a thiscall void method; honest address name.
class AsciiString;

#include <vector>

namespace _STL
{
// Bind the range erase to the rowed 0x0002CCFC worker.
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString *first, AsciiString *last);
}

class Rva002CEC0A
{
public:
	void rva002CEC34();
	void rva002CED26(class Xfer *xfer);

private:
	int m_00;
	_STL::vector<AsciiString> m_04;
};

void Rva002CEC0A::rva002CEC34()
{
	_STL::vector<AsciiString> *v = &m_04;
	v->erase(v->begin(), v->end());
}

class Snapshot;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
#include "../../Include/Common/BfmeXfer.h"

Xfer *xferAsciiStringVector(Xfer *xfer, _STL::vector<AsciiString> *vec);

void Rva002CEC0A::rva002CED26(Xfer *xfer)
{
	xfer->BeginBlock("CRCParameterCheck");
	xferAsciiStringVector(xfer, &m_04);
	xfer->EndBlock();
	rva002CEC34();
}
