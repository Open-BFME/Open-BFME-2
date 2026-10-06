// cl: /DNDEBUG /MD /EHsc
// ?rva004A44B1@Rva004A44B1@@QAEXXZ, retail 0x004A44B1, 122 bytes.
// Evidence: static BoneFXUpdate key via TheNameKeyGenerator->nameToKey (same as StructureCollapseUpdate::doCollapseDoneStuff at 0x004A4DBE and poolkey at 0x004A429F); Object::findModule row 0x0028B6D6; BoneFXUpdate::stopAllBoneFX row 0x00487A95; GameLogic::destroyObject row 0x00242C09; caller 0x004A46BF.
// Same UpdateModule layout as StructureCollapseUpdate (m_object at +8).

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Module;
class Object;
class BoneFXUpdate;
class GameLogic;
class NameKeyGenerator;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *s);
};

class Module
{
public:
	virtual ~Module();
};

class BoneFXUpdate : public Module
{
public:
	void stopAllBoneFX();
};

class Rva004A44B1;
class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend class Rva004A44B1;
};

class GameLogic
{
public:
	void destroyObject(Object *obj);
};

extern class NameKeyGenerator *TheNameKeyGenerator;
extern class GameLogic *TheGameLogic;

struct Holder04
{
	unsigned char m_pad[0xf4];
	unsigned char m_flag;
};

class Rva004A44B1
{
public:
	void rva004A44B1();

private:
	const void *m_vtable;
	Holder04 *m_04;
	Object *m_object;
};

void Rva004A44B1::rva004A44B1()
{
	static NameKeyType key_BoneFXUpdate = TheNameKeyGenerator->nameToKey("BoneFXUpdate");
	Module *mod = m_object->findModule(key_BoneFXUpdate);
	if (mod != 0)
		((BoneFXUpdate *)mod)->stopAllBoneFX();
	if (m_04->m_flag == 1)
		TheGameLogic->destroyObject(m_object);
}
