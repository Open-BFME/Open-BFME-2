// ?rva00460CBA@DynamicPortalBehaviour@@QAEXPAUCoord3D@@@Z
// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /ICode/Libraries/Include/Lib /I.
// Native460CBA..460DD8 full288 RET4; WB10ACDD0 and rowed portal data ctor
// corroborate transform-point purpose and TopAttackPos at data144. Literal
// 1/0 and double length temporary reproduce native SSE/x87 scheduling;
// no donor callable name is asserted; observed out-Coord3D ABI is retained.
#include <math.h>

#include "Coord3D.h"


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

class DynamicPortalBehaviourModuleData
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
	const DynamicPortalBehaviourModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

void DynamicPortalBehaviour::rva00460CBA(Coord3D *out)
{
	Coord3D tmp1;
	Coord3D tmp2;
	Coord3D tmp3;
	tmp2.x = 1.0f;
	tmp2.y = 0.0f;
	tmp2.z = 0.0f;
	const DynamicPortalBehaviourModuleData *data = m_moduleData;
	((Thing *)m_object)->transformPoint(&tmp2, &tmp1);
	Coord3D *pPos = &m_object->m_pos;
	tmp1.x -= pPos->x;
	tmp1.y -= pPos->y;
	tmp1.z -= pPos->z;
	float fdy = (float)fabs(tmp1.y);
	float fdx = (float)fabs(tmp1.x);
	const float *pick = fdx > fdy ? &fdx : &fdy;
	float scale = 1.0f / *pick;
	tmp1.x = scale * tmp1.x;
	tmp1.y = scale * tmp1.y;
	tmp1.z = scale * 0.0f;
	double len = tmp1.length();
	tmp2 = data->m_144;
	tmp2.x *= len;
	tmp2.y *= len;
	((Thing *)m_object)->transformPoint(&tmp2, &tmp3);
	out->x = tmp3.x;
	out->y = tmp3.y;
	out->z = tmp3.z;
}
