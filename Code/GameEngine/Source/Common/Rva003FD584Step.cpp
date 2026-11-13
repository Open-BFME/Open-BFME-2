// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva003FD584@Rva003FD584@@QAE_N_N@Z retail 0x003FD584..0x003FD64D
// (201 bytes). Steps a control-point cursor: when the flag argument is set
// the +0x18 index advances (by ten with shift held and the global data
// +0x88 flag set: Keyboard::isShift 0x00232683 and TheWritableGlobalData);
// when the rowed boundary check Rva00064880Tree::atEnd 0x00504182 on the
// +0x0C tree reports the end it returns true. Otherwise a default
// Rva00064390 record (inline ctor of the rowed 0x003FD398) is filled by the
// pinned lookup 0x005042F2 and its position (rowed copy 0x002BE7DB) and
// degree angle (times the pi/180 constant) go to the rowed camera mover
// 0x002BECCD on g_00DFEF18. WorldBuilder twin 0x0105D6D0 has the same
// shape. Class identity is address-derived.

#include "../../Include/GameClient/KeyboardClass.h"
extern Keyboard *TheKeyboard;

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva003FD584GlobalData
{
	char m_pad000[0x88];
	bool m_flag88; // +0x88
};

#include "../../Include/Common/Rva002BE7DBValue.h"

#include "../../Include/Common/Rva002BE7DB.h"

class Rva00064390
{
public:
	__declspec(dllimport) __forceinline Rva00064390()
	{
		m_18 = 0;
		m_00 = 0.0f;
		m_04 = 0.0f;
		m_08 = 0.0f;
		m_0c = 0.0f;
		m_10 = 0.5f;
		m_14 = 0.5f;
	}

	float m_00;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
	int m_18;
};

struct Rva005042F2Key;
class Rva005042F2
{
public:
	bool rva005042F2(unsigned int time, Rva005042F2Key *out);
};

class Rva00064880Tree
{
public:
	bool atEnd(unsigned int limit);
	bool rva005042F2(unsigned int index, Rva00064390 *out);

	void *m_00;
	void *m_04;
};

struct RvaFloatPair
{
	float x, y;
	RvaFloatPair() {}
	RvaFloatPair(const RvaFloatPair &rvaFloatPair) { x = rvaFloatPair.x; y = rvaFloatPair.y; }
	~RvaFloatPair() {}
};

class Rva002BECCD
{
public:
	void rva002BECCD(RvaFloatPair pair, float height);
};

class Rva002D3627Host;
class LivingWorld; extern LivingWorld *TheLivingWorld;

class Rva003FD584
{
public:
	bool rva003FD584(bool advance);

private:
	char m_pad000[0x0C];
	Rva00064880Tree m_controlPoints; // +0x0C
	char m_pad014[0x18 - 0x14];
	unsigned int m_index18;   // +0x18
};

bool Rva003FD584::rva003FD584(bool advance)
{
	if (advance)
	{
		++m_index18;
		if (m_controlPoints.atEnd(m_index18))
			return true;
		if (TheKeyboard->isShift() && reinterpret_cast<Rva003FD584GlobalData *>(TheWritableGlobalData)->m_flag88)
			m_index18 += 9;

		Rva00064390 record;
		reinterpret_cast<Rva005042F2 *>(&m_controlPoints)->rva005042F2(m_index18, reinterpret_cast<Rva005042F2Key *>(&record));
		Rva002BE7DBValue position;
		reinterpret_cast<Rva002BECCD *>(((Rva002D3627Host *)TheLivingWorld))->rva002BECCD(
			reinterpret_cast<const RvaFloatPair &>(reinterpret_cast<const Rva002BE7DB *>(&record)->rva002BE7DB(position)),
			record.m_0c * 0.017453292f);
	}
	return false;
}
