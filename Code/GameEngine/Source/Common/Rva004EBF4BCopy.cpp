// cl: /MD /arch:SSE /Oy- /Os
// ?rva004EBF4B@Rva004EBF4B@@QAE?AUCoord3D@@XZ @0x004EBF4B 72B: wrapper over
// rowed ?rva00506B74@AIBaseBuilder@@QAE_NPAUCoord3D@@@Z; zeroes temp Coord3D via
// xorps plus three movss then forwards ecx+4 plus temp and block-copies temp
// to *out via three movss. Callers include 0x004E9264 0x00572F50 0x005732B2.
// Native callers consume EAX as the hidden output pointer; WB also returns arg0.
// Explicit scalar return construction preserves the native local-copy phase.
// Honest address name;
// AIBaseBuilder at +4 carries the +0x28 member so ecx+4 lands at +0x2C.
struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Coord3D : public Coord3DBase
{
	Coord3D(){}
	Coord3D(float X,float Y,float Z){x=X;y=Y;z=Z;}
};

class AIBaseBuilder
{
public:
	char m_pad[0x28];
	Coord3D m_28;
	bool rva00506B74(Coord3D *out);
};

class Rva004EBF4B
{
public:
	Coord3D rva004EBF4B();
private:
	char m_00[4];
	AIBaseBuilder m_04;
};

Coord3D Rva004EBF4B::rva004EBF4B()
{
	Coord3D tmp;
	tmp.x = 0.0f;
	tmp.y = 0.0f;
	tmp.z = 0.0f;
	m_04.rva00506B74(&tmp);
	return Coord3D(tmp.x,tmp.y,tmp.z);
}
