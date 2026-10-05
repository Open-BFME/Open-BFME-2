// cl: /O1 /DNDEBUG /MD
//
// ?rva0049C592@Rva0049C592@@QAEXXZ @0x0049C592 70B.
// Looks up the id at +0x40. A live object and the object from 0x2931F5
// both clear status 0x42. The id is then masked to 0.

enum ObjectID
{
	OID_NONE = 0
};

enum ObjectStatusTypes
{
	OS_42 = 0x42
};

class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
	Object *rva002931F5(bool flag);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Rva0049C592
{
public:
	void rva0049C592();

private:
	char m_pad[0x40];
	unsigned int m_id;
};

void Rva0049C592::rva0049C592()
{
	unsigned int id = m_id;
	if (id == 0)
		return;
	Object *obj = TheGameLogic->findObjectByID((ObjectID)id);
	if (obj != 0)
	{
		obj->setStatus(OS_42, false);
		Object *other = obj->rva002931F5(false);
		if (other != 0)
			other->setStatus(OS_42, false);
	}
	m_id &= 0;
}
