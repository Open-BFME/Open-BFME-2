// cl: /MD
// ?rva003AFB2A@Rva003AFB2A@@QAEXPAUCoord3D@@MMII@Z @0x003AFB2A 151B
// Evidence: unlock lane; virtual slot 0x1c fills local Coord3D then SSE scales via TheWritableGlobalData+0x9ec g_Va00BBB8D8 g_Va007C26F0; ret 0x14; caller 0x1F5586.
struct Coord3D
{
	float x;
	float y;
	float z;
};

class GlobalData
{
public:
	char m_pad[0x9EC];
	volatile float m_09EC;
};

extern GlobalData *TheWritableGlobalData;
extern float g_Va00BBB8D8;
extern float g_Va007C26F0;

class Rva003AFB2A
{
public:
	virtual void vf00();
	virtual void vf01();
	virtual void vf02();
	virtual void vf03();
	virtual void vf04();
	virtual void vf05();
	virtual void vf06();
	virtual void vf07(Coord3D *out, float a, float b, unsigned int c, unsigned int d);
	void rva003AFB2A(Coord3D *out, float a, float b, unsigned int c, unsigned int d);
};

void Rva003AFB2A::rva003AFB2A(Coord3D *out, float a, float b, unsigned int c, unsigned int d)
{
	Coord3D tmp;
	vf07(&tmp, a, b, c, d);
	tmp.x = (TheWritableGlobalData->m_09EC + g_Va00BBB8D8) * g_Va007C26F0 * tmp.x;
	tmp.y = (TheWritableGlobalData->m_09EC + g_Va00BBB8D8) * g_Va007C26F0 * tmp.y;
	tmp.z = (TheWritableGlobalData->m_09EC + g_Va00BBB8D8) * g_Va007C26F0 * tmp.z;
	out->x = tmp.x;
	out->y = tmp.y;
	out->z = tmp.z;
}
