// cl: /DNDEBUG /MD /Oi-
#include <math.h>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
// ?rva0026417F@AIUpdateInterface@@QAEH_N@Z
// ABI repair: native CalcCollisionFreeExtraCosts 0x002EC0A2 stores the
// ENEMIES comparison as one byte and pushes that bool without zero-extending
// at all six priority calls; WB 0x00D32F30 also pushes the byte-valued flag.
// This helper ignores the argument in both native and WB 0x00E41FF0. Its
// name remains address-qualified; callers establish a boolean parameter.
// 0x0026417F 59B: AIUpdateInterface score helper between slot139 0x0026412B and free 0x00264237. Reads owner at this+8 and template byte +0x109 bits 0x40 and 0x02 plus 10x Object::rva0028CE7B. Evidence: this+8 is m_object as in AIUpdateInterfacePrivateCommands slot bodies and Rva00263910Goal +8 model. Callee rowed-or-pinned 0x0028CE7B. Callers in 0x0026CF11 0x002EBE54 0x002EC0A2.
class ThingTemplate
{
public:
	unsigned char m_pad[0x109];
	unsigned char m_b109; // +0x109
};

class Object
{
public:
	signed char rva0028CE7B() const;
	float GetRelativeAngle(const struct Coord3D *coord) const;
	unsigned char m_pad[4];
	ThingTemplate *m_template; // +4
};

struct Rva003642DFResult
{
	float m_distance;
	Coord3D m_point;
};

class FloatData
{
public:
	unsigned char m_pad[0xF0];
	float m_value;
};

class Rva0008BB38FloatField
{
public:
	unsigned char m_pad[4];
	FloatData *m_data;
};

class Path
{
public:
	Rva003642DFResult rva00364521(const Rva0008BB38FloatField *field);
};

class AIUpdateInterface
{
public:
	int rva0026417F(bool arg);
	unsigned char m_pad[8];
	Object *m_object; // +8
	unsigned char m_pad140[0x140 - 12];
	Path *m_path; // +0x140
	unsigned char m_pad1F0[0x1F0 - 0x144];
	Rva0008BB38FloatField *m_field; // +0x1F0
	unsigned char m_pad3B1[0x3B1 - 0x1F4];
	unsigned char m_flag3B1; // +0x3B1
	unsigned char rva002641BA();
};

int AIUpdateInterface::rva0026417F(bool arg)
{
	(void)arg;
	Object *obj = m_object;
	int v = 0;
	if ((obj->m_template->m_b109 & 0x40) != 0)
		v = 100;
	v += 10 * obj->rva0028CE7B();
	if ((obj->m_template->m_b109 & 2) != 0)
		v += 5;
	return v;
}

extern float g_00BF967C;

unsigned char AIUpdateInterface::rva002641BA()
{
	if (m_flag3B1 != 0)
		return 1;
	if (m_field != 0 && m_field->m_data->m_value > 0.0f)
		return 0;
	float angle = 0.0f;
	if (m_path != 0)
	{
		Rva003642DFResult result = m_path->rva00364521(m_field);
		angle = m_object->GetRelativeAngle(&result.m_point);
	}
	return fabs(angle) > g_00BF967C;
}
