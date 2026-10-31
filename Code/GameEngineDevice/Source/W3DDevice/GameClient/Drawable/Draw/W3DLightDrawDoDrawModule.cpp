// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib /Ireference/shims/bfme2renderobj /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
//
// ?doDrawModule@W3DLightDraw@@UAEXPBVMatrix3D@@@Z, retail 0x000CFC0C..0x000CFDDF
// (467B), thiscall ret 4.
//
// Donor: Open-BFME-1 game/GameEngineDevice/Source/W3DDevice/GameClient/
// Drawable/Draw/W3DLightDrawDoDrawModule.cpp (BFME 1 W3DLightDraw::doDrawModule):
// advance the flicker phase, move the dynamic light to the drawable's position
// keeping its rotation, step the height drift toward a random target and add
// the sine flicker, then store the result in the light. BFME 2 differences
// read from retail: the phase step is 1 / the int global BfmeLogicFramesPerSecond (5 at
// load, BFME 1's 0.2f) and the drift period is that int over data +0x38
// (BFME 1's 5.0f); the light's value is at +0xD0 (BFME 1 +0xD4). Layout as
// the rowed W3DLightDraw xfer/ctor: module data +0x04, drawable +0x08, light
// +0x0C, phase +0x10, radius +0x14, angle +0x18, height +0x1C. Callees:
// light slots 20 (Validate_Transform) / 21 (Set_Transform), the pinned
// drawable position getter 0x00276470 and WWMath::Random_Float 0x00711B90.

typedef float Real;
typedef bool Bool;

#include "Coord3D.h"

#include "../../../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"




extern int BfmeLogicFramesPerSecond;

class Rva00276470Drawable
{
public:
	const Coord3D *rva00276470() const;
};
class Drawable;


class W3DDynamicLight : public RenderObjClass
{
};

class W3DLightDrawModuleData
{
public:
	unsigned char m_pad[0x30];
	Real m_intensity;
	Real m_flickerAmplitude;
	Real m_flickerFrequency;
	Real m_pulseAmplitude;
	Real m_pulseFrequency;
	Real m_attachToBoneInAnotherModule;
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
	phase += 1.0f / (Real)BfmeLogicFramesPerSecond;
	m_phase = phase;
	if (light == 0)
		return;

	const W3DLightDrawModuleData *data = m_moduleData;
	if (data == 0)
		return;
	Real height = data->m_intensity;
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

	if (data->m_flickerAmplitude > 0.0f)
	{
		if (m_radius <= 0.0f)
		{
			m_radius = (Real)BfmeLogicFramesPerSecond / data->m_flickerFrequency;
			Real minimum = -data->m_flickerAmplitude;
			Real maximum = data->m_flickerAmplitude;
			m_angle = ((WWMath::Random_Float() * (maximum - minimum) + minimum) + height - m_height) / m_radius;
		}
		m_radius -= 1.0f;
		height = m_angle + m_height;
		m_height = height;
	}
	if (data->m_pulseAmplitude > 0.0f)
		height = WWMath::Sin(m_phase * data->m_pulseFrequency * 6.2831855f) * *(volatile const Real *)&data->m_pulseAmplitude + height;
	*(Real *)((char *)m_light + 0xd0) = height;
}
