// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// Dump range 1 twins (0x00068073 64B, 0x000680D6 67B): guarded pairs through
// +0x3854/+0x3858. The first guard calls, the second restores esi before its
// branch. 0x68073 is (int,float,int) then (int,float); 0x680D6 is
// (Coord3D*,GeometryInfo&,float) twice, the second into the rowed
// W3DPropBuffer::removePropsForConstruction 0x000EF154. Pins for the three
// unrowed siblings. Coord3D is struct, GeometryInfo is class to match the
// rowed mangling. Honest address-derived pin names.

struct Coord3D;
class GeometryInfo;

class W3DPropBuffer
{
public:
	void rva000E912A(int a, float b, int c);
	void rva000EE04A(int a, float b);
	void rva000E9D18(const Coord3D *a, const GeometryInfo &b, float c);
	void removePropsForConstruction(const Coord3D *a, const GeometryInfo &b, float c);
};

class Rva00068073Host
{
public:
	void rva00068073(int a, float b, int c);
	void rva000680D6(const Coord3D *a, const GeometryInfo &b, float c);

	char m_pad[0x3854];
	W3DPropBuffer *m_3854; // +0x3854
	W3DPropBuffer *m_3858; // +0x3858
};

void Rva00068073Host::rva00068073(int a, float b, int c)
{
	if (m_3854)
		m_3854->rva000E912A(a, b, c);
	if (m_3858)
		m_3858->rva000EE04A(a, b);
}

void Rva00068073Host::rva000680D6(const Coord3D *a, const GeometryInfo &b, float c)
{
	if (m_3854)
		m_3854->rva000E9D18(a, b, c);
	if (m_3858)
		m_3858->removePropsForConstruction(a, b, c);
}
