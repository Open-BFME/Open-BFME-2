// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /O1 /arch:SSE /G7 /MD /EHsc
// ?rva002BEFE5@Rva002BEFE5@@QAEXPBURva002BEFE5Vec@@MMI@Z @0x002BEFE5 185B
// Honest address name: REF through 2 data table slots, neighbours ZeroSetter disables and purecalls.
// Evidence: TheMouse + empty UnicodeString tooltip, virtuals +0x64/+0x74/+0x78, members +0x54..+0x84.
#include "unicode_string.h"

#include "../../../Libraries/Include/Lib/RGBColor.h"
#include "../../Include/GameClient/Mouse.h"
extern Mouse *TheMouse;

struct Rva002BEFE5Vec { float x, y, z; };

class Rva002BEFE5 {
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual float v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29(void *p);
	virtual float v30();
	char _pad04[0x50];
	char m_startPosition[12];
	float m_targetX;
	float m_64;
	float m_targetZ;
	float m_startZoom;
	float m_targetZoom;
	float m_moveProgress;
	unsigned char m_isMoving;
	char _pad79[3];
	float m_moveRate;
	float m_80;
	float m_84;
	void rva002BEFE5(const Rva002BEFE5Vec *position, float a1, float zoom, unsigned int duration);
};

void Rva002BEFE5::rva002BEFE5(const Rva002BEFE5Vec *position, float a1, float zoom, unsigned int duration)
{
	TheMouse->rva001EEA6D(UnicodeString(UnicodeString::TheEmptyString), 0, 0, 1.0f);
	v29(m_startPosition);
	m_80 = v30();
	m_isMoving = 1;
	m_moveProgress = 0.0f;
	m_moveRate = 1.0f / (float)duration;
	*(Rva002BEFE5Vec *)&m_targetX = *position;
	m_targetZ = 0.0f;
	m_84 = a1;
	m_startZoom = v25();
	float t = zoom;
	m_targetZoom = t < 0.0f ? 0.0f : (t > 1.0f ? 1.0f : t);
}
