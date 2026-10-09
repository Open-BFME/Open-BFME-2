// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva003FB7DB@Rva003FDCEB@@QAEXXZ
// retail 0x003FB7DB..0x003FB9C7 (493 bytes) thiscall RET 0.
//
// A render-object fade's per-frame step, shared by six vtables (absolute
// references 0x00837C3C 0x00837C74 0x0086D81C 0x008744F4 0x008747C4
// 0x008766C4) and called directly from 0x003FDB93 and 0x003FDCEE; the
// WorldBuilder twin 0x01070A90 has the same shape. Fading in or out (modes
// 1 and 2) runs a linear ramp over +0x34 frames; pulsing (mode 3) ramps up
// from +0x3C to +0x40, holds to +0x44, ramps down to +0x48 and stops at the
// +0x54 floor. Slot 9 fires on the ramp's first frame, slot 10 when it ends.
// The value, scaled by +0x98 and kept at +0x9C, becomes the render object's
// opacity (kind 0, W3DUtility's SetOpacity 0x0010E87A) or its emissive
// colour (kind 1, the +0xA0 colour, SetEmissive 0x0010E676); slots 4, 6
// and 5 then run every frame. The method keeps its pinned spelling.

typedef float Real;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class RenderObjClass;

Bool Rva0010E87A_SetOpacity(RenderObjClass *robj, Real opacity);
Bool Rva0010E676_SetEmissive(RenderObjClass *robj, Real r, Real g, Real b);

class Rva003FDCEB
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();				// +0x10
	virtual void v05();				// +0x14
	virtual void v06();				// +0x18
	virtual void v07();
	virtual void v08();
	virtual void onRampStart();			// +0x24
	virtual void onRampEnd();			// +0x28

	void rva003FB7DB();

private:
	unsigned char m_pad04[0x08 - 0x04];
	RenderObjClass *m_robj;			// +0x08
	unsigned char m_pad0C[0x2C - 0x0C];
	int m_mode;				// +0x2C, 0 idle 1 fade in 2 fade out 3 pulse
	int m_kind;				// +0x30, 0 opacity 1 emissive
	UnsignedInt m_duration;			// +0x34
	UnsignedInt m_frame;			// +0x38
	UnsignedInt m_rampUpStart;		// +0x3C
	UnsignedInt m_rampUpEnd;		// +0x40
	UnsignedInt m_rampDownStart;		// +0x44
	UnsignedInt m_rampDownEnd;		// +0x48
	int m_phase;				// +0x4C
	unsigned char m_pad50[0x54 - 0x50];
	Real m_floor;				// +0x54
	unsigned char m_pad58[0x98 - 0x58];
	Real m_scale;				// +0x98
	Real m_value;				// +0x9C
	Real m_color[3];			// +0xA0
};

void Rva003FDCEB::rva003FB7DB()
{
	if (m_mode != 0)
	{
		Real value = 0.0f;
		if (m_mode == 1 || m_mode == 2)
		{
			if (m_frame == 0)
				onRampStart();
			value = (Real)(m_mode == 1 ? m_frame : m_duration - m_frame) / (Real)m_duration;
			++m_frame;
			if (m_frame > m_duration)
				onRampEnd();
		}
		else if (m_mode == 3)
		{
			++m_frame;
			m_phase = 0;
			if (m_frame > m_rampDownEnd)
				onRampEnd();
			else if (m_frame > m_rampDownStart)
			{
				value = (Real)(m_rampDownEnd - m_frame) / (Real)(m_rampDownEnd - m_rampDownStart);
				m_phase = 2;
			}
			else if (m_frame > m_rampUpEnd)
				value = 1.0f;
			else if (m_frame >= m_rampUpStart)
			{
				value = (Real)(m_frame - m_rampUpStart) / (Real)(m_rampUpEnd - m_rampUpStart);
				m_phase = 1;
				if (m_frame == m_rampUpStart)
					onRampStart();
			}
			if (m_phase == 2 && value <= m_floor)
			{
				value = m_floor;
				onRampEnd();
			}
		}

		value *= m_scale;
		m_value = value;
		if (m_kind == 0)
			Rva0010E87A_SetOpacity(m_robj, value);
		else if (m_kind == 1)
			Rva0010E676_SetEmissive(m_robj, value * m_color[0], value * m_color[1], value * m_color[2]);
	}
	v04();
	v06();
	v05();
}
