// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// ?rva0039B57F@Rva0039ADF3@@QAEXPAURva0039B57FData@@H@Z, retail 0x0039B57F
// (179 bytes, RET 8): the slot after the Object experience tracker's xfer
// (vtable 0x0081AD34, class Rva0039ADF3 of ExperienceTrackerXfer.cpp; the
// tracked Object at +0x34). It applies a level record: the change is queued
// with TheDelayedExperienceLevelGrantSystem (rowed append 0x00420F0E), the
// Object's drawable takes the record's +0xA4 value (rowed 0x0027290C), the
// tracker its name (+0x10, rowed 0x0039AF76) and level (+0xFC, rowed
// 0x0039B20C). Past level 1, the first time (+0x20), for an Object whose
// template lacks the 0x80 flag at +0x108, its controlling player's +0x3BC
// record counts it as a hero (template +0x113 bit 4, rowed 0x0039B632) or,
// unless it has status 0x26, as a unit (rowed 0x0039B64D).
// Address-derived names; storage view without constructor or vtable.
#include "ascii_string.h"

struct Rva0039B57FData
{
	unsigned char m_pad000[0x10];
	AsciiString m_name;		// +0x10
	unsigned char m_pad014[0xA4 - 0x14];
	int m_A4;			// +0xA4
	unsigned char m_pad0A8[0xFC - 0xA8];
	int m_level;			// +0xFC
};

struct Rva0039B57FTemplate
{
	unsigned char m_pad000[0x108];
	unsigned char m_108;		// +0x108
	unsigned char m_pad109[0x113 - 0x109];
	unsigned char m_113;		// +0x113
};

class Drawable
{
public:
	void rva0027290C(int value);
};

class Rva0039B632 { public: void rva0039B632(int value); };
class Rva0039B64D { public: void rva0039B64D(int value); };

class Player
{
public:
	unsigned char m_pad000[0x3BC];
	Rva0039B632 m_3BC;		// +0x3BC
};

#include "../../Common/Thing/thing.h"

enum ObjectStatusTypes
{
	OBJECT_STATUS_26 = 0x26
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	Player *getControllingPlayer() const;
	__declspec(dllimport) __forceinline Drawable *getDrawable() const { return ((const Thing *)this)->getDrawable(); }
	unsigned char m_pad000[0x04];
	const Rva0039B57FTemplate *m_template;	// +0x04
};

class Rva00420F0EHost { public: void append(int a, int b, int c); };
class DelayedExperienceLevelGrantSystem;
extern DelayedExperienceLevelGrantSystem *TheDelayedExperienceLevelGrantSystem;

class Rva0039AF76 { public: void rva0039AF76(const AsciiString &name); };
class Rva0039B20C { public: void rva0039B20C(void *level); };
class Rva0039ADF3
{
public:
	void rva0039B57F(Rva0039B57FData *data, int value);
private:
	unsigned char m_pad00[0x20];
	bool m_counted;			// +0x20
	unsigned char m_pad21[0x34 - 0x21];
	Object *m_object;		// +0x34
};

void Rva0039ADF3::rva0039B57F(Rva0039B57FData *data, int value)
{
	((Rva00420F0EHost *)TheDelayedExperienceLevelGrantSystem)->append((int)data, (int)m_object, value);
	Drawable *draw = m_object->getDrawable();
	if (draw)
		draw->rva0027290C((int)&data->m_A4);
	((Rva0039AF76 *)this)->rva0039AF76(data->m_name);
	((Rva0039B20C *)this)->rva0039B20C((void *)data->m_level);
	if (data->m_level > 1 && !m_counted)
	{
		Object *obj = m_object;
		if (!(obj->m_template->m_108 & 0x80))
		{
			m_counted = true;
			if (obj->m_template->m_113 & 4)
			{
				Player *player = obj->getControllingPlayer();
				player->m_3BC.rva0039B632(1);
			}
			else if (!obj->testStatus(OBJECT_STATUS_26))
			{
				Player *player = obj->getControllingPlayer();
				((Rva0039B64D *)&player->m_3BC)->rva0039B64D(1);
			}
		}
	}
}
