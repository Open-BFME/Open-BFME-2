// cl: /O1 /DNDEBUG /MD /arch:SSE
// stlport
// ?rva004BBA3D@GeometryInfo@@QAEXM@Z @0x004BBA3D 40B
// Evidence: unlock lane GeometryInfo vector size idiv 0x24 first-shape +0xC float store then rowed calcBoundingStuff 0x006BE700; caller 0x004BBCD7; same 0x24 stride as GeometryInfoCalcBoundingStuff.
#include <vector>

struct GeometryShape
{
	char _pad[0xc];
	float m_minorRadius;
	char _pad2[0x24 - 0x10];
};

class GeometryInfo
{
private:
	void calcBoundingStuff();
	char _pad[0x2c];
	std::vector<GeometryShape> m_shapes;
public:
	void rva004BBA3D(float f);
};

void GeometryInfo::rva004BBA3D(float f)
{
	if (m_shapes.size() > 0)
		m_shapes[0].m_minorRadius = f;
	calcBoundingStuff();
}
