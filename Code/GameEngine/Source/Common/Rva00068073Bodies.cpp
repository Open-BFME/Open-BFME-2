// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// Dump range 1 twins (0x00068073 64B, 0x000680D6 67B): guarded pairs through
// +0x3854/+0x3858. The first guard calls, the second restores esi before its
// branch. 0x68073 is (int,float,int) then (int,float); 0x680D6 is
// (Coord3D*,GeometryInfo&,float) twice, the second into the rowed
// W3DPropBuffer::removePropsForConstruction 0x000EF154. Pins for the three
// siblings, now called by their row spellings. Coord3D is struct, GeometryInfo is class to match the
// rowed mangling. Honest address-derived pin names.

struct Coord3D;
class GeometryInfo;

// The +0x3854 buffer's two callees are rowed on W3DShrubBuffer (0x000E912A,
// 0x000E9D18); 0x000EE04A takes a const Coord3D * on W3DPropBuffer.
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DShrubBuffer.h"

class AsciiString;
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DPropBufferClass.h"

class Rva00068073Host
{
public:
	void rva00068073(int location, float angle, int id);
	void rva000680D6(const Coord3D *location, const GeometryInfo &b, float angle);

	char m_pad[0x3854];
	W3DShrubBuffer *m_3854; // +0x3854
	W3DPropBuffer *m_3858; // +0x3858
};

void Rva00068073Host::rva00068073(int location, float angle, int id)
{
	if (m_3854)
		m_3854->rva000E912A((const Coord3D *)location, angle, id);
	if (m_3858)
		m_3858->rva000EE04A((const Coord3D *)location, angle);
}

void Rva00068073Host::rva000680D6(const Coord3D *location, const GeometryInfo &geometryInfo, float angle)
{
	if (m_3854)
		m_3854->rva000E9D18(location, geometryInfo, angle);
	if (m_3858)
		m_3858->removePropsForConstruction(location, geometryInfo, angle);
}
