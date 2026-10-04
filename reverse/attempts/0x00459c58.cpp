// ?rva00459C58@SiegeDockingBehavior@@UAE_NW4ObjectID@@@Z
// partial score=0.9 date=2026-10-04
// cl: /O1 /DNDEBUG /MD
//
// ?rva00459C58@SiegeDockingBehavior@@UAE_NW4ObjectID@@@Z, retail 0x00459C58,
// 104 bytes: slot 3 of the vtable 0x00C41404 that SiegeDockingBehavior's
// ctors (0x004599AE, 0x00459DCF) install at +0x20. For a live Object (rowed
// findObjectByID) it first runs the primary member 0x00459B68 (pinned; it
// tidies the dock-slot vector at +0x24), then answers true when some dock
// slot is free (its +0x20 empty) and either the Object's template has bit 3
// of its +0x119 byte or the slot's +0x04 is empty. Compiled with the +0x20
// subobject this. Names by address.
enum ObjectID
{
	INVALID_ID = 0
};

struct Rva00459C58Template
{
	unsigned char m_pad000[0x119];
	unsigned char m_119; // +0x119
};

class Object
{
public:
	const Rva00459C58Template *getTemplate() const { return m_template; }
private:
	unsigned char m_pad00[4];
	const Rva00459C58Template *m_template; // +0x04
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

struct Rva00459C58Dock
{
	unsigned char m_pad00[4];
	void *m_04; // +0x04
	unsigned char m_pad08[0x20 - 8];
	void *m_20; // +0x20
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
private:
	unsigned char m_pad04[0x20 - 4];
};

class Rva00459C58Interface
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual bool rva00459C58(ObjectID id) = 0;
protected:
	unsigned int dockCount() const { return (unsigned int)(m_docksEnd - m_docks); }
	Rva00459C58Dock **m_docks; // +0x24 (+0x04 here)
	Rva00459C58Dock **m_docksEnd; // +0x28
};

class SiegeDockingBehavior : public BehaviorModule, public Rva00459C58Interface
{
public:
	virtual bool rva00459C58(ObjectID id);
	void rva00459B68();
};

bool SiegeDockingBehavior::rva00459C58(ObjectID id)
{
	Object *obj = TheGameLogic->findObjectByID(id);
	if (obj == 0)
		return false;
	rva00459B68();
	unsigned int count = dockCount();
	if (count == 0)
		return false;
	for (unsigned int i = 0; i < count; ++i)
	{
		Rva00459C58Dock *dock = m_docks[i];
		if (dock->m_20 == 0)
		{
			if ((obj->getTemplate()->m_119 & 8) || dock->m_04 == 0)
				return true;
		}
	}
	return false;
}
