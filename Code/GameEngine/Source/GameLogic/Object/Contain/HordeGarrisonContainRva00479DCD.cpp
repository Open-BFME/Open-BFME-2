// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva00479DCD@Rva00479DCD@@QAEXPAVObject@@H@Z, retail 0x00479DCD..0x00479E62
// (149 bytes, RET 8). A contain-interface method of the garrison contain
// whose outer object starts 0x20 bytes before this interface (its rowed
// 0x00479BA1 and HordeGarrisonContain 0x00479B3A are called there). For a
// non-null object:
//   - an object the +0x9C0 record already knows (rowed 0x00588B8A) goes
//     through 0x00479BA1 and the record's entry is told through its slot 74;
//   - otherwise an object with status 0x26 goes to 0x00479B3A;
//   - otherwise it goes through 0x00479BA1 and its drawable, when the rowed
//     0x00270260 test holds, is unhidden (pinned Drawable::setDrawableHidden).
// The record's first word then becomes the current frame plus the module
// data's +0xAC delay. WorldBuilder's twin (0x011A7E10) is unnamed.

#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

enum ObjectStatusTypes
{
	OBJECT_STATUS_26 = 0x26
};

class Drawable
{
public:
	void setDrawableHidden(bool hidden);
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	Drawable *getDrawable() const;
};

class Rva00270260
{
public:
	bool rva00270260();
};

class Rva0047A040Base9E0
{
public:
	void *rva00588B8A(void *key);
	int m_nextFrame;						// +0x00
};

class Rva00479BA1
{
public:
	void rva00479BA1(Object *obj);
};

class Rva00479B3A
{
public:
	void rva00479B3A(Object *obj);
};

struct Rva00479DCDData
{
	unsigned char m_pad00[0xAC];
	int m_delayAC;
};

class Rva00479DCDEntry
{
public:
#define V(n) virtual void pad##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73)
#undef V
	virtual void slot74();
};

class Rva00479DCD
{
public:
	void rva00479DCD(Object *obj, int unused);

private:
	char *outer() { return reinterpret_cast<char *>(this) - 0x20; }
	Rva00479DCDData *outerData() { return *reinterpret_cast<Rva00479DCDData **>(reinterpret_cast<char *>(this) - 0x1C); }

	unsigned char m_pad00[0x9C0];
	Rva0047A040Base9E0 m_record9C0;			// +0x9C0
};

void Rva00479DCD::rva00479DCD(Object *obj, int /*unused*/)
{
	if (!obj)
		return;

	void *entry = m_record9C0.rva00588B8A(obj);
	if (entry)
	{
		reinterpret_cast<Rva00479BA1 *>(outer())->rva00479BA1(obj);
		static_cast<Rva00479DCDEntry *>(entry)->slot74();
	}
	else if (obj->testStatus(OBJECT_STATUS_26) == true)
	{
		reinterpret_cast<Rva00479B3A *>(outer())->rva00479B3A(obj);
	}
	else
	{
		reinterpret_cast<Rva00479BA1 *>(outer())->rva00479BA1(obj);
		Drawable *draw = obj->getDrawable();
		if (draw && reinterpret_cast<Rva00270260 *>(draw)->rva00270260() == true)
			draw->setDrawableHidden(false);
	}
	m_record9C0.m_nextFrame = outerData()->m_delayAC + TheGameLogic->getFrame();
}
