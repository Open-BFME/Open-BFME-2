// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata /ICode/GameEngine/Include/Common /ICode/Libraries/Include /ICode/GameEngine/Source /ICode/GameEngine/Include
// stlport
//
// ?Rva00498B8BGet@@YAEPAVObject@@@Z, retail 0x00498B8B, 36 bytes.
// Evidence: calls rowed 0x0028B511 Object::rva0028B511; flag byte at +0x108 bit 2; caller at 0x00498F5E pushes one pointer and tests al; free shape mov ecx [esp+4].

#include "ascii_string.h"
#include "../../../../Include/Common/ObjectModule.h"
#include "../../../Common/Thing/thing.h"

enum NameKeyType { NK_UNKNOWN = 0 };

enum ArmorSetType { ARMORSET_NONE = 0 };

enum ObjectID;

// How the rowed setFlag 0x006BF3C0 names its argument, one of the module
// data's geometry-name AsciiStrings.
class BfmeStrF9
{
public:
	unsigned char m_pad[4];
};

class BfmeObjF9
{
public:
	void setFlag(const BfmeStrF9 &name, char flag);
};

// The object's template as this unit reads it: +0xB0 the gate's cylinder
// radius, +0x108 the flag byte the rowed test 0x00498B8B masks with 4.
class ThingTemplate
{
public:
	char m_pad00[0xB0];
	float m_B0; // +0xB0
	char m_padB4[0x108 - 0xB4];
	unsigned char m_flag108; // +0x108
};

class Object : public Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	Object *getNextObject() const { return m_next; }
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	Player *getControllingPlayer() const;
	int rva0028B511() const;
	void clearArmorSetFlag(ArmorSetType v);
	void setArmorSetFlag(ArmorSetType v);
	void rva0028AB75(bool v);

protected:
	friend class GateOpenAndCloseBehavior;
	Module *findModule(NameKeyType key) const;

private:
	unsigned char m_pad060[0x74 - 0x60];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x88 - 0x78];
	AsciiString m_name; // +0x88
	Object *m_next; // +0x8C
	unsigned char m_pad090[0xA8 - 0x90];
public:
	BfmeObjF9 m_objA8; // +0xA8
private:
	unsigned char m_pad0A9[0x438 - 0xA9];
	unsigned char m_438; // +0x438
};

unsigned char __cdecl Rva00498B8BGet(Object *object)
{
	if (object == 0)
		return 0;
	else
	{
		const ThingTemplate *inner = object->getTemplate();
		if ((inner->m_flag108 & 4) != 0)
			return 0;
		return (unsigned char)(object->rva0028B511() == 1);
	}
}
