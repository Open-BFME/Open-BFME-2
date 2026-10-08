// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// Object::addAttributeModifierToPool  retail 0x0028EA91 (177 B)
// Object::removeAttributeModifierFromPool  retail 0x0028EB42 (152 B)
// Names: WorldBuilder's Object.cpp (both named; retail drops the debug
// warning about one-character names and the horde command-point assert).
// Target evidence: a name of length 1 is refused; a horde (contain at +0x250,
// vtable +0x7C) forwards to its own slot (+0x1D8 add with a zero and the
// value, +0x1DC remove with a zero); otherwise the AttributeModifierPoolUpdate
// module takes the change, bracketed by the controlling player's command
// point removal/re-add (WB Player::removeCommandPoints/addCommandPoints,
// rowed as placeholders) when the template's +0x61C bonus is positive.
// The pool callees 0x00403E72 (WB AttributeModifierPoolUpdate::
// addModifierToPool) and 0x00403744 (WB unnamed; remove by symmetry) are
// pinned. Horde/contain class names are placeholders.
#include "ascii_string.h"

class Object;
class Player;
struct Rva002A7588In;

// Player::removeCommandPoints / addCommandPoints per WorldBuilder; rowed under
// a placeholder owner.
class Rva002A9B58
{
public:
	void rva002A9B58(Rva002A7588In *obj);		// 0x002A9B58
	void rva002A9B35(Rva002A7588In *obj);		// 0x002A9B35
};

class AttributeModifierPoolUpdate
{
public:
	bool addModifierToPool(const AsciiString &name, int value);	// 0x00403E72
	void removeModifierFromPool(const AsciiString &name);		// 0x00403744
};

class Rva0028EA91Horde
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0A();
	virtual void slot0B();
	virtual void slot0C();
	virtual void slot0D();
	virtual void slot0E();
	virtual void slot0F();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot1A();
	virtual void slot1B();
	virtual void slot1C();
	virtual void slot1D();
	virtual void slot1E();
	virtual void slot1F();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot2A();
	virtual void slot2B();
	virtual void slot2C();
	virtual void slot2D();
	virtual void slot2E();
	virtual void slot2F();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot3A();
	virtual void slot3B();
	virtual void slot3C();
	virtual void slot3D();
	virtual void slot3E();
	virtual void slot3F();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot4A();
	virtual void slot4B();
	virtual void slot4C();
	virtual void slot4D();
	virtual void slot4E();
	virtual void slot4F();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot5A();
	virtual void slot5B();
	virtual void slot5C();
	virtual void slot5D();
	virtual void slot5E();
	virtual void slot5F();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot6A();
	virtual void slot6B();
	virtual void slot6C();
	virtual void slot6D();
	virtual void slot6E();
	virtual void slot6F();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	// vtable +0x1D8 / +0x1DC
	virtual void addAttributeModifierToPoolSlot(const AsciiString &name, int zero, int value);
	virtual void removeAttributeModifierFromPoolSlot(const AsciiString &name, int zero);
};

class Rva0028EA91Contain
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0A();
	virtual void slot0B();
	virtual void slot0C();
	virtual void slot0D();
	virtual void slot0E();
	virtual void slot0F();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot1A();
	virtual void slot1B();
	virtual void slot1C();
	virtual void slot1D();
	virtual void slot1E();
	virtual Rva0028EA91Horde *getHorde();	// vtable +0x7C
};

class ThingTemplate
{
public:
	int getCommandPointBonus() const { return m_commandPointBonus; }
private:
	unsigned char m_pad[0x61c];
	int m_commandPointBonus;		// +0x61C
};

class Object
{
public:
	bool addAttributeModifierToPool(const AsciiString &name, int value);
	void removeAttributeModifierFromPool(const AsciiString &name);
	Rva0028EA91Contain *getContain() const { return m_contain; }
	const ThingTemplate *getTemplate() const { return m_template; }
	Player *getControllingPlayer() const;
private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;

	void *m_vtbl;
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad08[0x250 - 8];
	Rva0028EA91Contain *m_contain;		// +0x250
};

bool Object::addAttributeModifierToPool(const AsciiString &name, int value)
{
	if (name.getLength() == 1)
		return false;

	Rva0028EA91Contain *contain = getContain();
	Rva0028EA91Horde *horde = contain ? contain->getHorde() : 0;
	if (horde)
	{
		horde->addAttributeModifierToPoolSlot(name, 0, value);
		return true;
	}

	AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
	if (pool)
	{
		Player *player = getControllingPlayer();
		bool commandPoints = player && getTemplate()->getCommandPointBonus() > 0;
		if (commandPoints)
			((Rva002A9B58 *)player)->rva002A9B58((Rva002A7588In *)this);
		if (pool->addModifierToPool(name, value))
		{
			if (commandPoints)
				((Rva002A9B58 *)player)->rva002A9B35((Rva002A7588In *)this);
			return true;
		}
	}
	return false;
}

void Object::removeAttributeModifierFromPool(const AsciiString &name)
{
	if (name.getLength() == 1)
		return;

	Rva0028EA91Contain *contain = getContain();
	Rva0028EA91Horde *horde = contain ? contain->getHorde() : 0;
	if (horde)
	{
		horde->removeAttributeModifierFromPoolSlot(name, 0);
		return;
	}

	AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
	if (pool)
	{
		Player *player = getControllingPlayer();
		bool commandPoints = player && getTemplate()->getCommandPointBonus() > 0;
		if (commandPoints)
			((Rva002A9B58 *)player)->rva002A9B58((Rva002A7588In *)this);
		pool->removeModifierFromPool(name);
		if (commandPoints)
			((Rva002A9B58 *)player)->rva002A9B35((Rva002A7588In *)this);
	}
}
