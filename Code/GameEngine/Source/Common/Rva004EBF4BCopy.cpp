// cl: /MD
// ?rva004EBF4B@Rva004EBF4B@@QAEXPAUCoord3D@@@Z @0x004EBF4B 72B: wrapper over
// rowed ?rva00506B74@Rva00506B74@@QAE_NPAUCoord3D@@@Z; zeroes temp Coord3D via
// xorps plus three movss then forwards ecx+4 plus temp and block-copies temp
// to *out via three movss. Callers include 0x004E9264 0x00572F50 0x005732B2.
// Prev Disp no flags next stlport list; SSE2 for movss. Honest address name;
// Rva00506B74 at +4 carries the +0x28 member so ecx+4 lands at +0x2C.
struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase
{
};

struct Rva00506B74
{
	char m_pad[0x28];
	Coord3D m_28;
	bool rva00506B74(Coord3D *out);
};

class Rva004EBF4B
{
public:
	void rva004EBF4B(Coord3D *out);
private:
	char m_00[4];
	Rva00506B74 m_04;
};

void Rva004EBF4B::rva004EBF4B(Coord3D *out)
{
	Coord3D tmp;
	tmp.x = 0.0f;
	tmp.y = 0.0f;
	tmp.z = 0.0f;
	m_04.rva00506B74(&tmp);
	out->x = tmp.x;
	out->y = tmp.y;
	out->z = tmp.z;
}
