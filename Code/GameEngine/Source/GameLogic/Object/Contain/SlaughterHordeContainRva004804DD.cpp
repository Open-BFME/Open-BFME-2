// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// SlaughterHordeContain's slot-29 chain (??_7SlaughterHordeContain 0x00C48AA0;
// CitadelSlaughterHordeContain inherits it). The amount at +0x9E4 and the
// template name at +0x9E8 are the members the rowed xfer transfers.
//
// ?rva004804DD@SlaughterHordeContain@@AAEXPAVObject@@@Z, retail 0x004804DD, 167 bytes.
// For an object slot 33 accepts (CitadelSlaughterHordeContain's rowed
// 0x004807C7), with a positive amount and a name set: looks the name up
// through TheThingFactory (rowed rva002D06CA) and, when the owner's
// controlling player differs from the object's and the lookup succeeds,
// records the amount on both players' records at Player+0x3BC (rowed
// addObjectsLost on ours, pinned 0x0039CF1D on theirs); then clears the amount
// and the name.
//
// ?rva00479B7F@SlaughterHordeContain@@UAEXPAVObject@@@Z, retail 0x00480584, 27 bytes.
// Slot 29: the member above, then HordeGarrisonContain's slot 29 (rowed
// 0x00479B7F, whose address name it carries so cl 7.1 places it there).
// Method identities are not established.

#include "ascii_string.h"

class Player;

class ScoreKeeper
{
public:
	void addObjectsLost(unsigned int key, int amount);
	void rva0039CF1D(void *key, Player *other, unsigned int amount);
};

class Player
{
public:
	unsigned char m_pad00[0x3BC];
	ScoreKeeper m_3BC;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *s);
};

extern class ThingFactory *TheThingFactory;

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

class HordeGarrisonContain
{
public:
	SLOT08(s00,s01,s02,s03,s04,s05,s06,s07)
	SLOT08(s08,s09,s0A,s0B,s0C,s0D,s0E,s0F)
	SLOT08(s10,s11,s12,s13,s14,s15,s16,s17)
	virtual void s18(); virtual void s19(); virtual void s1A(); virtual void s1B();
	virtual void s1C();
	virtual void rva00479B7F(Object *obj);
	virtual void s1E(); virtual void s1F();
protected:
	const void *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x9E4 - 0x0C];
};

class SlaughterHordeContain : public HordeGarrisonContain
{
public:
	virtual void rva00479B7F(Object *obj);
	virtual void s20();
	virtual bool rva004807C7(Object *obj);
private:
	void rva004804DD(Object *obj);

	unsigned int m_9E4;
	AsciiString m_9E8;
};

// ?rva004804DD@SlaughterHordeContain@@AAEXPAVObject@@@Z @0x004804DD
void SlaughterHordeContain::rva004804DD(Object *obj)
{
	if (!rva004807C7(obj))
		return;
	if (m_9E4 <= 0)
		return;
	if (((const StringBase<char> *)&m_9E8)->isEmpty())
		return;
	if (obj == 0)
		return;

	Player *ours = m_object->getControllingPlayer();
	Player *theirs = obj->getControllingPlayer();
	void *found = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&m_9E8);
	if (ours != theirs && found)
	{
		ours->m_3BC.addObjectsLost((unsigned int)found, m_9E4);
		theirs->m_3BC.rva0039CF1D(found, ours, m_9E4);
	}
	m_9E4 = 0;
	m_9E8.clear();
}

// ?rva00479B7F@SlaughterHordeContain@@UAEXPAVObject@@@Z @0x00480584
void SlaughterHordeContain::rva00479B7F(Object *obj)
{
	rva004804DD(obj);
	HordeGarrisonContain::rva00479B7F(obj);
}
