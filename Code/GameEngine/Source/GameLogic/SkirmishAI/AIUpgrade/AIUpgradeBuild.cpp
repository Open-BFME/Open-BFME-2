// cl: /O1 /DNDEBUG /MD
//
// AIUpgrade::build, retail 0x0059738A (78 bytes, ret 4), vtable slot beside
// getCostPerTick in the AIUpgrade tables (refs 0x00870BC4, 0x00870C0C,
// 0x0087667C).
// Identity (target): WorldBuilder's debug AIUpgrade.cpp lines 36..37 names it
// (wb-lead 2/callgraph): the builder object (ObjectID +0x08) runs the upgrade's
// command button (+0x30) through Object::doCommandButton (0x00296749, flags
// 1 and 0), then the object query 0x0028BC58(0) is asked through its slot 6
// about the button's +0x24 field, and that answer is returned.
// The slot-6 receiver and the argument are not identified by target evidence
// and stay opaque.

enum ObjectID
{
	INVALID_ID = 0
};

class CommandButton
{
public:
	int getField24() const { return m_field24; }

private:
	unsigned char m_pad00[0x24];
	int m_field24; // +0x24 retail-measured
};

// Opaque receiver returned by Object::rva0028BC58; slot 6 answers the query.
class Rva0028BC58Result
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual char slot6(int value);
};

class Object
{
public:
	void doCommandButton(const CommandButton *commandButton, int cmdSource, bool flags);
	void *rva0028BC58(int which);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class AIUpgrade
{
public:
	virtual ~AIUpgrade();
	virtual bool build(void *context);

private:
	unsigned char m_pad04[0x08 - 0x04];
	ObjectID m_builderID; // +0x08
	unsigned char m_pad0C[0x30 - 0x0C];
	const CommandButton *m_commandButton; // +0x30
};

bool AIUpgrade::build(void *context)
{
	TheGameLogic->findObjectByID(m_builderID)->doCommandButton(m_commandButton, 1, 0);
	ObjectID id = m_builderID;
	Rva0028BC58Result *result = (Rva0028BC58Result *)TheGameLogic->findObjectByID(id)->rva0028BC58(0);
	return result->slot6(m_commandButton->getField24()) ? true : false;
}
