// cl: /O1 /DNDEBUG /MD
//
// ?rva00462213@RunOffMapBehavior@@UAEXXZ, retail 0x00462213, 17 bytes: slot 5
// of the primary vtable 0x00C4307C that RunOffMapBehavior's ctor 0x0046217B
// installs (BehaviorModule base 0x00253330; interfaces at +0x0C 0x00C42FC0
// and +0x10 0x00C42F1C). Unless the module data's +0x10 byte is set, runs
// slot 0 of the +0x10 interface (retail 0x004622FC) as a tail call. Names by
// address.
class Object;

struct RunOffMapBehaviorModuleData
{
	unsigned char m_pad00[0x10];
	bool m_10; // +0x10
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4();
	virtual void rva00462213();
protected:
	const RunOffMapBehaviorModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class Rva004622FCInterface
{
public:
	virtual void rva004622FC() = 0;
};

class RunOffMapBehavior : public BehaviorModule, public BehaviorModuleInterface, public Rva004622FCInterface
{
public:
	virtual void rva00462213();
	virtual void rva004622FC();
};

void RunOffMapBehavior::rva00462213()
{
	if (!m_moduleData->m_10)
		rva004622FC();
}
