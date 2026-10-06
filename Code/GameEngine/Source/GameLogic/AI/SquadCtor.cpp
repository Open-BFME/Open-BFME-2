// cl: /O1 /MD
// stlport
// Squad::Squad, native 0x00268CAC..0x00268CD6 (42B).
// Identity: AIStateMachine::setGoalTeam 0x0035042D and setGoalAIGroup 0x00350462
// call it on a fresh 0x1C-byte operator new block; the body installs vftable
// 0x00BF9D60, whose slot 0 is the rowed deleting destructor 0x0026AF6A, slot 2
// the name getter returning "Squad" (0x00268CD6) and slot 3 the rowed
// Squad::xfer 0x004D6EC4.
// Layout: two STLport vectors at +4 and +0x10 (the Zero Hour Squad members
// m_objectIDs and m_objectsCached), both built through the ICF-shared
// _Vector_base constructor 0x00211E58. Retail has no EH state between the two
// member constructions, so this unit compiles without an EH option, like the
// verified PlayerAITypeSet sibling.
#include <vector>

enum ObjectID
{
	INVALID_ID = 0
};

class Object;
class Xfer;

class Squad
{
public:
	Squad();
	virtual ~Squad();

protected:
	virtual void loadPostProcess();
	virtual const char *getSnapshotName() const;
	virtual void xfer(Xfer *xfer);

private:
	_STL::vector<ObjectID> m_objectIDs;
	_STL::vector<Object *> m_objectsCached;
};

Squad::Squad()
{
}
