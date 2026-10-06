// cl: /MD
// ?rva0039922D@CastleBehavior@@QAEXPAURva00398E4AArg@@@Z @0x0039922D 70B evidence: float at arg+0x70 vs 0.0 at 0x00BBAEAC; this+8 ObjectID via findObjectByID rowed 0x00049DC5; CastleBehavior key via rva0003955DA rowed 0x003955DA; module via findModule rowed 0x0028B6D6; then rva00398E4A rowed 0x00398E4A.
// Honest-address method on proven class (Object-rva precedent).
enum ObjectID
{
	OBJECTID_INVALID = 0
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum CommandSourceType
{
	CMDSOURCE_0 = 0
};

class Module;
class Object;
class Rva00398E4AArg;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
};

class ObjectWithPub : public Object
{
public:
	using Object::findModule;
};

struct Rva00398E4AArg
{
	char m_pad00[0xc];
	unsigned int m_bits;
	char m_pad10[0x70 - 0x10];
	float m_70;
};

class CastleBehavior
{
public:
	virtual ~CastleBehavior();
	void rva0039922D(Rva00398E4AArg *arg);
	static NameKeyType rva0003955DA();
	void rva00398E4A(Rva00398E4AArg *arg);
private:
	unsigned char m_pad04[8 - 4];
	ObjectID m_08;
};

void CastleBehavior::rva0039922D(Rva00398E4AArg *arg)
{
	if (arg->m_70 > 0.0f)
	{
		Object *obj = TheGameLogic->findObjectByID(m_08);
		if (obj == 0)
			return;
		NameKeyType key = CastleBehavior::rva0003955DA();
		Module *mod = ((ObjectWithPub *)obj)->findModule(key);
		if (mod == 0)
			return;
		((CastleBehavior *)mod)->rva00398E4A(arg);
	}
}
