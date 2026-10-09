// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// ?doDrawModule@W3DLightDraw@@UAEXPBVMatrix3D@@@Z, retail 0x000CFC0C..0x000CFDDF
// (467B), thiscall ret 4.
//
// Donor: Open-BFME-1 game/GameEngineDevice/Source/W3DDevice/GameClient/
// Drawable/Draw/W3DLightDrawDoDrawModule.cpp (BFME 1 W3DLightDraw::doDrawModule):
// advance the flicker phase, move the dynamic light to the drawable's position
// keeping its rotation, step the height drift toward a random target and add
// the sine flicker, then store the result in the light. BFME 2 differences
// read from retail: the phase step is 1 / the int global g_Va00DBA4E4 (5 at
// load, BFME 1's 0.2f) and the drift period is that int over data +0x38
// (BFME 1's 5.0f); the light's value is at +0xD0 (BFME 1 +0xD4). Layout as
// the rowed W3DLightDraw xfer/ctor: module data +0x04, drawable +0x08, light
// +0x0C, phase +0x10, radius +0x14, angle +0x18, height +0x1C. Callees:
// light slots 20 (Validate_Transform) / 21 (Set_Transform), the pinned
// drawable position getter 0x00276470 and WWMath::Random_Float 0x00711B90.

typedef float Real;
typedef bool Bool;

#include "Coord3D.h"

struct Vector3
{
	Vector3(Real x, Real y, Real z) : X(x), Y(y), Z(z) {}
	Real X, Y, Z;
};

class Matrix3D
{
public:
	Matrix3D() {}
	void Set_Translation(const Vector3 &t)
	{
		Row[0][3] = t.X;
		Row[1][3] = t.Y;
		Row[2][3] = t.Z;
	}
	Real Row[3][4];
};

class WWMath
{
public:
	static Real Random_Float();
	static __forceinline Real Sin(Real val)
	{
		Real retval;
		__asm {
			fld [val]
			fsin
			fstp [retval]
		}
		return retval;
	}
};

extern int g_Va00DBA4E4;

class Rva00276470Drawable
{
public:
	const Coord3D *rva00276470() const;
};
class Drawable;

class RenderObjClass
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19();
	virtual void Validate_Transform() const;
	virtual void Set_Transform(const Matrix3D &transform);

	const Matrix3D &Get_Transform_No_Validity_Check() const { return m_transform; }

	unsigned char m_pad04[0x14];
	Matrix3D m_transform;			// +0x18
};

class W3DDynamicLight : public RenderObjClass
{
};

class W3DLightDrawModuleData
{
public:
	unsigned char m_pad[0x30];
	Real m_30;
	Real m_34;
	Real m_38;
	Real m_3c;
	Real m_40;
	Real m_44;
};

class DrawModule
{
public:
	virtual void doDrawModule(const Matrix3D *transform) = 0;

protected:
	W3DLightDrawModuleData *m_moduleData;	// +0x04
	Drawable *m_drawable;			// +0x08
};

class W3DLightDraw : public DrawModule
{
public:
	virtual void doDrawModule(const Matrix3D *transform);

private:
	W3DDynamicLight *m_light;		// +0x0C
	Real m_phase;				// +0x10
	Real m_radius;				// +0x14
	Real m_angle;				// +0x18
	Real m_height;				// +0x1C
};

void W3DLightDraw::doDrawModule(const Matrix3D *)
{
	Real phase = m_phase;
	W3DDynamicLight *light = m_light;
	phase += 1.0f / (Real)g_Va00DBA4E4;
	m_phase = phase;
	if (light == 0)
		return;

	const W3DLightDrawModuleData *data = m_moduleData;
	if (data == 0)
		return;
	Real height = data->m_30;
	Drawable *drawable = m_drawable;
	if (drawable != 0)
	{
		light->Validate_Transform();
		Matrix3D transform;
		volatile float *destination = (volatile float *)&transform;
		volatile const float *source = (volatile const float *)&light->Get_Transform_No_Validity_Check();
		destination[0] = source[0];
		destination[1] = source[1];
		destination[2] = source[2];
		destination[3] = source[3];
		destination[4] = source[4];
		destination[5] = source[5];
		destination[6] = source[6];
		destination[7] = source[7];
		destination[8] = source[8];
		destination[9] = source[9];
		destination[10] = source[10];
		destination[11] = source[11];
		const Coord3D *position = ((const Rva00276470Drawable *)drawable)->rva00276470();
		Vector3 positionVector(position->x, position->y, position->z);
		transform.Set_Translation(positionVector);
		m_light->Set_Transform(transform);
	}

	if (data->m_34 > 0.0f)
	{
		if (m_radius <= 0.0f)
		{
			m_radius = (Real)g_Va00DBA4E4 / data->m_38;
			Real minimum = -data->m_34;
			Real maximum = data->m_34;
			m_angle = ((WWMath::Random_Float() * (maximum - minimum) + minimum) + height - m_height) / m_radius;
		}
		m_radius -= 1.0f;
		height = m_angle + m_height;
		m_height = height;
	}
	if (data->m_3c > 0.0f)
		height = WWMath::Sin(m_phase * data->m_40 * 6.2831855f) * data->m_3c + height;
	*(Real *)((char *)m_light + 0xd0) = height;
}
