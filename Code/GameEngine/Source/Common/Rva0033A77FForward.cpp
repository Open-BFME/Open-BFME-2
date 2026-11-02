// cl: /O1 /Oy- /DNDEBUG /MD
//
// ?rva0033A77F@Rva0033A77F@@QAEXHHHHH@Z @0x0033A77F 35B.
// Forwarder: passes its five stack arguments plus a trailing 0 to the member
// object at +0xA0 (thiscall, ret 0x14), calling 0x006BEF80, the rowed
// GeometryInfo::getBestContactPoint (GeometryInfoCollidesWith.cpp).
// Retail keeps a frame pointer here (push ebp / mov ebp,esp), hence /Oy-.
// The owner and its own argument types are unknown; dwords are the measured
// ABI view, handed on as the callee's declared types.

struct Coord3D;
#include "../../Include/Common/Geometry.h"

class Rva0033A77F
{
public:
	void rva0033A77F(int pointOut, int from, int trace, int preference, int seed);

private:
	char unknown00[0xA0];
	GeometryInfo m_geometryInfo;
};

void Rva0033A77F::rva0033A77F(int pointOut, int from, int trace, int preference, int seed)
{
	m_geometryInfo.getBestContactPoint((Coord3D *)pointOut, (const Coord3D *)from, (const char *)trace, preference, seed, false);
}
