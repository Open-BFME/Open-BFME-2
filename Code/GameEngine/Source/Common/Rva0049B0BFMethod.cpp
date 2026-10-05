// cl: /O1 /MD /EHsc /arch:SSE
//
// ?rva0049B0BF@Rva0049B0BF@@QAEXPAURva0049B0BFData@@H@Z @ 0x0049B0BF 268B
// Leaf sharing +0x08/+0x3CA/+0x3E8/+0x3EC layout with Rva0049AE5ECheck;
// sets flag, copies ID at +0x74 to +0x3E8/+0x3EC, normalizes the delta
// between m_obj8 position and arg position, copies both GeometryInfos,
// then calls rowed Rva0026228F with computed point and int arg.
// Evidence: offsets match Rva0049AE5ECheck; callees all rowed.
class Coord3D
{
public:
	void normalize();
	float x;
	float y;
	float z;
};

class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &other);
	virtual ~GeometryInfo();
	char m_pad04[0x0C];
	float m_field10;
	char m_pad14[0x5C - 0x14];
};

struct Rva0049B0BFData
{
	char m_pad00[0x38];
	float m_x38;
	float m_y3C;
	float m_z40;
	char m_pad44[0x74 - 0x44];
	int m_id74;
	char m_pad78[0xA8 - 0x78];
	GeometryInfo m_geoA8;
};

class Rva0026228F
{
public:
	void rva0026228F(int a, int b);
};

class Rva0049B0BF
{
public:
	void rva0049B0BF(Rva0049B0BFData *arg, int arg2);
private:
	char m_pad00[8];
	Rva0049B0BFData *m_obj8;
	char m_pad0C[0x3CA - 0x0C];
	unsigned char m_flag3CA;
	char m_pad3CB[0x3E8 - 0x3CB];
	int m_id3E8;
	int m_id3EC;
	int m_id3F0;
};

void Rva0049B0BF::rva0049B0BF(Rva0049B0BFData *arg, int arg2)
{
	m_flag3CA = 1;
	Rva0049B0BFData *obj = m_obj8;
	m_id3E8 = arg->m_id74;
	m_id3EC = arg->m_id74;
	Coord3D diff;
	float ox = obj->m_x38;
	float oy = obj->m_y3C;
	float oz = obj->m_z40;
	diff.x = ox - arg->m_x38;
	diff.y = oy - arg->m_y3C;
	diff.z = oz - arg->m_z40;
	diff.normalize();
	GeometryInfo g1(arg->m_geoA8);
	GeometryInfo g2(obj->m_geoA8);
	float sum = g1.m_field10 + g2.m_field10;
	float sx = sum * diff.x;
	float sy = sum * diff.y;
	float ax = arg->m_x38;
	float ay = arg->m_y3C;
	float az = arg->m_z40;
	Coord3D pt;
	pt.z = az;
	pt.x = ax + sx;
	pt.y = ay + sy;
	((Rva0026228F *)this)->rva0026228F((int)&pt, arg2);
}
