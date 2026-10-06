// cl: /DNDEBUG /MD /EHsc
// ?setFrameFade@W3DDynamicLight@@QAEXII@Z @0x0006DF81 105B
// BFME2 W3DDynamicLight::setFrameFade. Donor: reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDynamicLight.cpp
// Target facts: called from 0x0004430D (W3DDisplay::createLightPulse) and 0x000CF9FF (W3DLightDraw ctor) as (0,0)/(increase,decay); store order and offsets match upstream (decay to +0x150/+0x148, increase to +0x14c/+0x154, Ambient +0xD4 to +0x15C, Diffuse +0xE0 to +0x168, FarEnd +0x104 to +0x158).

typedef unsigned int UnsignedInt;

struct Vector3
{
	float x;
	float y;
	float z;
	Vector3 &operator=(const Vector3 &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
};

class W3DDynamicLight
{
public:
	void setFrameFade(UnsignedInt frameIncreaseTime, UnsignedInt decayFrameTime);

private:
	char _pad0[0xD4];
	Vector3 Ambient; // +0xD4
	Vector3 Diffuse; // +0xE0
	char _pad1[0x14];
	float FarAttenStart; // +0x100
	float FarAttenEnd; // +0x104
	char _pad2[0x40];
	UnsignedInt m_curDecayFrameCount; // +0x148
	UnsignedInt m_curIncreaseFrameCount; // +0x14C
	UnsignedInt m_decayFrameCount; // +0x150
	UnsignedInt m_increaseFrameCount; // +0x154
	float m_targetRange; // +0x158
	Vector3 m_targetAmbient; // +0x15C
	Vector3 m_targetDiffuse; // +0x168
};

void W3DDynamicLight::setFrameFade(UnsignedInt frameIncreaseTime, UnsignedInt decayFrameTime)
{
	m_decayFrameCount = decayFrameTime;
	m_curDecayFrameCount = decayFrameTime;
	m_curIncreaseFrameCount = frameIncreaseTime;
	m_increaseFrameCount = frameIncreaseTime;
	m_targetAmbient = Ambient;
	m_targetDiffuse = Diffuse;
	m_targetRange = FarAttenEnd;
}
