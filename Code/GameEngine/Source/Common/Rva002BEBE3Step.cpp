// cl: /O1 /arch:SSE /G7 /Oy- /DNDEBUG /MD
// ?rva002BEBE3@Rva002C021A@@QAEXXZ @0x002BEBE3 234B
// Progress step of the object stepped by rowed Rva002C021A::rva002C021A (tail jump when the byte at
// +0x78 is set): the progress at +0x74 advances by the rate at +0x7C (times ten while shift is held and
// a flag in the global data is set), is clamped to 1.0 (clearing the +0x78 active byte), then drives
// three virtual setters: the lerped scalar (+0x6C..+0x70) through slot 26, the vector interpolated
// between +0x54 and +0x60 through slot 22, and the scalar lerp (+0x80..+0x84) through slot 31.
// Evidence: target bytes and WB debug body 00D27590 (unnamed) structure; callees rowed
// Keyboard::isShift 0x00232683, BfmeStateDF::rva002BEACD 0x002BEACD and ::rva002BEAAC 0x002BEAAC
// (curve at +0x28), curve evaluator 0x00504BA9; shift global 0x00DFE720 is TheKeyboard.
// The shift/flag purposes (accelerated step) and the original class name are inferred, not proven.
#include "../../Include/GameClient/KeyboardClass.h"
extern Keyboard *TheKeyboard;

class GlobalData;
extern GlobalData *TheWritableGlobalData;

class Rva002BEBE3Flag
{
public:
	char m_pad[0x88];
	unsigned char m_livingWorldTurbo;
};

#include "../../Include/Common/FCurve.h"

struct BfmeStateDFVector3
{
	float x, y, z;
};

#include "../../Include/Common/BfmeStateDF.h"

class Rva002C021A
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c();
	virtual void slot50();
	virtual void slot54();
	virtual void setVector(BfmeStateDFVector3 *value);
	virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual void setScalar(float value);
	virtual void slot6c();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void setScalar2(float value);
	void rva002BEBE3();

private:
	unsigned char m_pad04[0x24];
	FCurve m_curve28;
	unsigned char m_pad2C[0x54 - 0x2C];
	BfmeStateDFVector3 m_from;
	BfmeStateDFVector3 m_to;
	float m_6c;
	float m_70;
	float m_progress;
	unsigned char m_active;
	unsigned char m_pad79[3];
	float m_rate;
	float m_80;
	float m_84;
};

void Rva002C021A::rva002BEBE3()
{
	if (TheKeyboard->isShift() && ((Rva002BEBE3Flag *)TheWritableGlobalData)->m_livingWorldTurbo)
		m_progress += m_rate * 10.0f;
	else
		m_progress += m_rate;
	if (m_progress >= 1.0f)
	{
		m_progress = 1.0f;
		m_active = 0;
	}
	float factor = m_curve28.operator()(m_progress);
	float start = m_6c;
	setScalar((m_70 - start) * factor + start);
	BfmeStateDFVector3 current;
	((BfmeStateDF *)this)->rva002BEACD(&m_from, &m_to, &current, m_progress);
	setVector(&current);
	float interpolatedValue = ((BfmeStateDF *)this)->rva002BEAAC(m_80, m_84, m_progress);
	setScalar2(interpolatedValue);
}
