// cl: /DNDEBUG /MD /EHsc
// ?setFrameFade@W3DDynamicLight@@QAEXII@Z @0x0006DF81 105B
// BFME2 W3DDynamicLight::setFrameFade. Donor: reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDynamicLight.cpp
// Target facts: called from 0x0004430D (W3DDisplay::createLightPulse) and 0x000CF9FF (W3DLightDraw ctor) as (0,0)/(increase,decay); store order and offsets match upstream (decay to +0x150/+0x148, increase to +0x14c/+0x154, Ambient +0xD4 to +0x15C, Diffuse +0xE0 to +0x168, FarEnd +0x104 to +0x158).
// ?On_Frame_Update@W3DDynamicLight@@UAEXXZ @0x0006DE3D 324B
// Donor: Open-BFME-1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d,
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDynamicLightOnFrameUpdate.cpp.
// Target evidence: this body reads the same +0x144..+0x170 flags, counters,
// range and color fields as the matched setFrameFade body immediately after it.

typedef unsigned int UnsignedInt;

struct Vector3
{
	float x;
	float y;
	float z;
	Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
	__forceinline friend Vector3 operator*(const Vector3 &v, float scale)
	{
		return Vector3(v.x * scale, v.y * scale, v.z * scale);
	}
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
	virtual void On_Frame_Update();
	void setFrameFade(UnsignedInt frameIncreaseTime, UnsignedInt decayFrameTime);

private:
	char _pad0[0xD0];
	Vector3 Ambient; // +0xD4
	Vector3 Diffuse; // +0xE0
	char _pad1[0x14];
	float FarAttenStart; // +0x100
	float FarAttenEnd; // +0x104
	char _pad2[0x144 - 0x108];
	bool m_enabled; // +0x144
	bool m_decayRange; // +0x145
	bool m_decayColor; // +0x146
	char _pad3;
	UnsignedInt m_curDecayFrameCount; // +0x148
	UnsignedInt m_curIncreaseFrameCount; // +0x14C
	UnsignedInt m_decayFrameCount; // +0x150
	UnsignedInt m_increaseFrameCount; // +0x154
	float m_targetRange; // +0x158
	Vector3 m_targetAmbient; // +0x15C
	Vector3 m_targetDiffuse; // +0x168
};

void W3DDynamicLight::On_Frame_Update()
{
	if (!m_enabled)
		return;

	float scale;
	if (m_curIncreaseFrameCount > 0 && m_increaseFrameCount > 0) {
		--m_curIncreaseFrameCount;
		scale = static_cast<float>(m_increaseFrameCount - m_curIncreaseFrameCount)
			/ static_cast<float>(m_increaseFrameCount);
	} else if (m_decayFrameCount == 0) {
		scale = 1.0f;
	} else {
		--m_curDecayFrameCount;
		if (m_curDecayFrameCount == 0) {
			m_enabled = false;
			return;
		}
		scale = static_cast<float>(m_curDecayFrameCount)
			/ static_cast<float>(m_decayFrameCount);
	}

	if (m_decayRange) {
		FarAttenEnd = scale * m_targetRange;
		if (FarAttenEnd < FarAttenStart)
			FarAttenEnd = FarAttenStart;
	}
	if (m_decayColor) {
		Ambient = m_targetAmbient * scale;
		Diffuse = m_targetDiffuse * scale;
	}
}

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
