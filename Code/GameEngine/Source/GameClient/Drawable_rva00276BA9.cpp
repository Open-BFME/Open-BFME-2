// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// ?rva00276BA9@Drawable@@QAEX_N@Z, retail 0x00276BA9..0x00276CFB (338 bytes),
// thiscall RET 4. Sibling of the rowed tint-status refresh Drawable::rva00275598
// (Drawable_rva00275598.cpp): it creates the +0x8C tint envelope on demand
// (operator new 0x50 plus rowed ctor 0x00271826, no EH frame as in that
// sibling), then -- when the global tint setting TheCloudEffectManager exists and its
// slot +0x3C test holds -- samples a value at the Drawable's position (pinned
// 0x00276470) through the setting's +0x54 or +0x58 virtual, chosen by its mode
// tests 0x0026FFF7 (mode 1/2) and rowed 0x0027000E (mode 3/4). At or below
// -25 / at or above 25 / in between it moves the tint status word at +0x120
// between bits 1 2 4 8, and on the -25 and middle paths optionally pushes the
// setting's +0x30 colour into the envelope (rowed 0x002747B8).
// WorldBuilder's twin (0x00CA4BF0) is unnamed; it keeps two separate colour
// copies (one per path, merged in retail) and builds the position argument as
// a destructible temporary (its address is stored to the frame before each
// virtual call in both builds). The argument class, the colour struct and the
// argument meaning are inferred views; the method name is address-derived.
#include "Coord3D.h"

#include "../../../Libraries/Include/Lib/RGBColor.h"

// The position argument of the setting's +0x54/+0x58 virtuals: built from a
// Coord3D and destroyed by the callee.
class Rva0027070CPoint
{
public:
	Rva0027070CPoint(const Coord3D &c) : m_x(c.x), m_y(c.y), m_z(c.z) {}
	~Rva0027070CPoint() {}

private:
	float m_x;
	float m_y;
	float m_z;
};

class Rva00271826
{
public:
	Rva00271826() throw();
	char m_pad00[0x50];
};

class Rva002747B8
{
public:
	void rva002747B8(float a, float b, float c);
	char m_pad00[0x1C];
private:
	float m_1C; // +0x1C
	float m_20; // +0x20
	float m_24; // +0x24
	int m_28; // +0x28
	int m_2C; // +0x2C
	int m_30; // +0x30
	int m_34; // +0x34
	unsigned char m_38; // +0x38
	char m_pad39[0x3];
};

class Rva0027070CGlobal
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual bool slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50();
	virtual float slot54(Rva0027070CPoint pos);
	virtual float slot58(Rva0027070CPoint pos);

	unsigned char m_pad04[0x30 - 0x04];
	RGBColor m_color30;
};

extern Rva0027070CGlobal *TheCloudEffectManager;

class Rva0026FFF7
{
public:
	int get() const;	// rowed ?get@Rva0026FFF7@@QBEHXZ
};

#include "../../Include/GameClient/Rva0027000E.h"

#include "../../Include/Common/Rva00276470Drawable.h"

#include <new>

#include "../../Include/GameClient/Drawable.h"

void Drawable::rva00276BA9(bool apply)
{
	if (m_8C == 0)
		m_8C = new Rva00271826;
	if (TheCloudEffectManager == 0 || !TheCloudEffectManager->slot3C())
		return;
	const Coord3D *pos = ((Rva00276470Drawable *)this)->rva00276470();
	float value;
	Rva0027070CGlobal *setting = TheCloudEffectManager;
	if ((unsigned char)((Rva0026FFF7 *)setting)->get())
		value = TheCloudEffectManager->slot54(*pos);
	else if (((Rva0027000E *)setting)->rva0027000E())
		value = TheCloudEffectManager->slot58(*pos);
	else
		return;
	if (value <= -25.0f)
	{
		if (m_120 & 8)
		{
			m_120 = 4;
			return;
		}
		if (!(m_120 & 2))
			m_120 = 2;
		if (apply)
		{
			RGBColor color = TheCloudEffectManager->m_color30;
			(((Rva002747B8 *)m_8C)->*reinterpret_cast<void (Rva002747B8::*)(RGBColor)>(&Rva002747B8::rva002747B8))(color);
		}
		return;
	}
	else if (value >= 25.0f)
	{
		if (m_120 & 4)
		{
			m_120 = 8;
			return;
		}
		if (!(m_120 & 1))
			m_120 = 1;
		return;
	}
	else
	{
		if (m_120 & 1)
			m_120 = 4;
		else if (m_120 & 2)
			m_120 = 8;
	}
	if (apply)
	{
		RGBColor color = TheCloudEffectManager->m_color30;
		(((Rva002747B8 *)m_8C)->*reinterpret_cast<void (Rva002747B8::*)(RGBColor)>(&Rva002747B8::rva002747B8))(color);
	}
}
