// ?rva00460CBA@DynamicPortalBehaviour@@QAEXPAUCoord3D@@@Z
// partial score=0.9 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva00460CBA@DynamicPortalBehaviour@@QAEXPAUCoord3D@@@Z @0x00460CBA 288B: portal offset via transformPoint fabs max scale length and second transform. Evidence: neighbours DynamicPortalBehaviour upgradeRemoval and dtor; callees row transformPoint 0x30A812 fabs 0x629210 length 0x3571; floats g_Va00BBB8D8 1.0 plus BfmeZeroRange; object pos +0x38 moduleData +0x144.
// ?rva00460CBA@DynamicPortalBehaviour@@QAEXPAUCoord3D@@@Z present-unmatched
#include <math.h>

struct Coord3D
{
	float x;
	float y;
	float z;
	float length() const;
};

extern float g_Va00BBB8D8;
extern const float BfmeZeroRange;

class Thing
{
public:
	void transformPoint(const Coord3D *in, Coord3D *out);
};

class Object
{
public:
	char pad[0x38];
	Coord3D m_pos; // +0x38
};

class ModuleData
{
public:
	char pad[0x144];
	Coord3D m_144; // +0x144
};

class DynamicPortalBehaviour
{
public:
	void rva00460CBA(Coord3D *out);
private:
	void *m_vptr; // +0x00
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

void DynamicPortalBehaviour::rva00460CBA(Coord3D *out)
{
	Coord3D tmp1;
	Coord3D tmp2;
	Coord3D tmp3;
	tmp2.x = g_Va00BBB8D8;
	tmp2.y = 0.0f;
	tmp2.z = 0.0f;
	const ModuleData *data = m_moduleData;
	((Thing *)m_object)->transformPoint(&tmp2, &tmp1);
	Coord3D *pPos = &m_object->m_pos;
	tmp1.x -= pPos->x;
	tmp1.y -= pPos->y;
	tmp1.z -= pPos->z;
	float fdy = (float)fabs(tmp1.y);
	float fdx = (float)fabs(tmp1.x);
	float pick = fdx > fdy ? fdx : fdy;
	float scale = g_Va00BBB8D8 / pick;
	tmp1.x = scale * tmp1.x;
	tmp1.y = scale * tmp1.y;
	tmp1.z = scale * BfmeZeroRange;
	float len = tmp1.length();
	tmp2 = data->m_144;
	tmp2.x *= len;
	tmp2.y *= len;
	((Thing *)m_object)->transformPoint(&tmp2, &tmp3);
	out->x = tmp3.x;
	out->y = tmp3.y;
	out->z = tmp3.z;
}
