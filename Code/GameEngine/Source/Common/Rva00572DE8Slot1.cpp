// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?rva00572E0F@Rva00572DE8@@QAEXPAVRva002C5D8B@@PAVPlayer@@H@Z @0x00572E0F 174B
// Slot 1 of vtable 0x0086E094 (class Rva00572DE8, ctor 0x00572DD4 in Rva00572DE8Ctor.cpp).
// Evidence: vtable slot, chain via 0x002C5D8B, neighbours Rva005CB23CDerived and DispDwordLeaFieldGetters.
// If record+0x16C > 1 and player lacks Upgrade_RingHero, walk GameLogic objects for template flag 0x82000 at +0x120 then forward via 0x002C5D8B with float at g_00DFEEF8+0x884.
#include "ascii_string.h"

class UpgradeTemplate;
class Object;
class Player;
class GameLogic;
class UpgradeCenter;

extern GameLogic *TheGameLogic;
extern "C" UpgradeCenter *TheUpgradeCenter;

struct Rva002A8AB1Record
{
	char m_pad000[0x16C];
	int m_16C;
};

struct Rva002A8F24
{
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

class Player
{
public:
	bool rva002AB87D(const UpgradeTemplate *tmpl) const;
};

class GameLogic
{
public:
	Object *getFirstObject();
};

struct Rva00572E0FTemplate
{
	char m_pad000[0x120];
	unsigned int m_120;
};

class Object
{
public:
	char m_pad000[4];
	void *m_04;
	char m_pad008[0x8C - 8];
	Object *m_next;
};

class Rva002C5D8B
{
public:
	void rva002C5D8B(Object *obj, float value);
};

class Rva005CB22A
{
public:
	Rva005CB22A(void *held);
	virtual ~Rva005CB22A();
	void *m_held;
};

class Rva00572DE8 : public Rva005CB22A
{
public:
	Rva00572DE8();
	virtual ~Rva00572DE8();
	void rva00572E0F(Rva002C5D8B *dst, Player *player, int unused);
};

void Rva00572DE8::rva00572E0F(Rva002C5D8B *dst, Player *player, int unused)
{
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(player);
	if (record->m_16C > 1) {
		const UpgradeTemplate *tmpl = TheUpgradeCenter->findUpgrade(AsciiString("Upgrade_RingHero"));
		if (!player->rva002AB87D(tmpl)) {
			Object *obj = TheGameLogic->getFirstObject();
			while (obj) {
				Rva00572E0FTemplate *t = (Rva00572E0FTemplate *)obj->m_04;
				if ((t->m_120 & 0x82000) != 0) {
					dst->rva002C5D8B(obj, *(float *)((char *)g_00DFEEF8 + 0x884));
					break;
				}
				obj = obj->m_next;
			}
		}
	}
	(void)unused;
}
