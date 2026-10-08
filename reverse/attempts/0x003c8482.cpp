// ?doLoadAllTransports@ScriptActions@@IAEXABVAsciiString@@@Z
// partial score=0.85 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ScriptActions::doLoadAllTransports, retail 0x003C8482 (487B), from
// WorldBuilder's and Zero Hour's ScriptActions.cpp (name, statement order):
// partition a team's units into its transports with PartitionSolver and send
// each unit into the transport chosen for it.
//
// Target facts: the team lookup passes false; transports are kind-of bit
// 0x15 and report their capacity through contain slot 0x70 after the
// null-preserving cast from the +0x20 contain interface; a unit whose
// container is kind-of bit 0x6D is counted as that container, its slot count
// comes from Object 0x0028FBBE before its id is read, and an id already in
// the unit list is not added twice (both are BFME2 additions to Zero Hour's
// loop); the solver's ctor is 0x00567348, solve 0x005675B3, its destructor
// 0x003C649E; the enter command is AICommandInterface 0x0026C347 at
// AIUpdateInterface +0x20 with no locomotor set choice ahead of it.
//
// Three STLport callees are ICF folds whose addresses already carry other
// real names, so their element types keep address-derived spellings:
// push_back 0x00539A2E and the solution copy ctor 0x004334D7 (the 8-byte
// element folds), and getSolution 0x002A9808 (folded with
// PlayerTemplate::getPreferredColor). The unit and transport lists are
// handed to the solver's ctor as its EntriesVec, the same 8-byte layout.

#include "ascii_string.h"
#include <vector>
#include "../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

enum CommandSourceType { CMD_FROM_SCRIPT = 1 };
typedef unsigned int UnsignedInt;

// pair<ObjectID, UnsignedInt>: (unit, slots) or (transport, capacity).
struct Rva003C8482Entry
{
	Rva003C8482Entry(const ObjectID &a, const UnsignedInt &b) : first(a), second(b) {}
	static Rva003C8482Entry make(const ObjectID &a, const UnsignedInt &b) { return Rva003C8482Entry(a, b); } // make_pair
	ObjectID first;
	UnsignedInt second;
};

// pair<ObjectID, ObjectID>: (unit, transport).
struct Rva003C8482Assignment
{
	ObjectID first;
	ObjectID second;
};

typedef _STL::vector<_STL::pair<ObjectID, UnsignedInt> > EntriesVec;
typedef _STL::vector<_STL::pair<ObjectID, UnsignedInt> > SpacesVec;
typedef _STL::vector<Rva003C8482Assignment> Rva003C8482SolutionVec;

enum SolutionType { PREFER_FAST_SOLUTION = 0, PREFER_CORRECT_SOLUTION = 0x7FFFFFFF };

class PartitionSolver
{
public:
	PartitionSolver(const EntriesVec &data, const SpacesVec &spaces, SolutionType howToSolve);
	~PartitionSolver();
	void solve(void);
	const Rva003C8482SolutionVec &rva002A9808(void) const; // getSolution

private:
	SolutionType m_howToSolve;
	EntriesVec m_data;
	SpacesVec m_spacesForData;
	Rva003C8482SolutionVec m_currentSolution;
	UnsignedInt m_currentSolutionLeftovers;
	Rva003C8482SolutionVec m_bestSolution;
};

class ContainModuleInterface
{
public:
#define CONTAIN_SLOT(n) virtual void slot##n();
	CONTAIN_SLOT(0) CONTAIN_SLOT(1) CONTAIN_SLOT(2) CONTAIN_SLOT(3)
	CONTAIN_SLOT(4) CONTAIN_SLOT(5) CONTAIN_SLOT(6) CONTAIN_SLOT(7)
	CONTAIN_SLOT(8) CONTAIN_SLOT(9) CONTAIN_SLOT(10) CONTAIN_SLOT(11)
	CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14) CONTAIN_SLOT(15)
	CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23)
	CONTAIN_SLOT(24) CONTAIN_SLOT(25) CONTAIN_SLOT(26) CONTAIN_SLOT(27)
#undef CONTAIN_SLOT
	virtual UnsignedInt getContainMax() const; // slot 0x70
};

class UpdateModule
{
public:
	virtual ~UpdateModule();

private:
	unsigned char m_pad04[0x20 - 0x04];
};

class TransportContain : public UpdateModule, public ContainModuleInterface
{
};

class ThingTemplate
{
public:
	__forceinline bool isKindOf(int t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }

private:
	unsigned char m_pad[0x108];
	unsigned char m_kindOf[0x20];
};

class AICommandInterface
{
public:
	void rva0026C347(Object *obj, CommandSourceType cmdSource); // aiEnter
};

class AIUpdateInterface
{
public:
	unsigned char m_pad[0x20];
	AICommandInterface m_command;
};

class Thing
{
public:
	virtual ~Thing();
};

class Object : public Thing
{
public:
	virtual ~Object();
	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline bool isKindOf(int t) const { return getTemplate()->isKindOf(t); }
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	int rva0028FBBE(); // transport slot count
	ObjectID getID() const { return m_id; }
	Object *getContainedBy() const { return m_containedBy; }

private:
	const ThingTemplate *m_template;
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id;
	unsigned char m_pad78[0x250 - 0x78];
	ContainModuleInterface *m_contain;
	unsigned char m_pad254[4];
	AIUpdateInterface *m_ai;
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy;
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }

private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool);
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doLoadAllTransports(const AsciiString &teamName);
};

void ScriptActions::doLoadAllTransports(const AsciiString &teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	_STL::vector<Rva003C8482Entry> vecOfUnits;
	_STL::vector<Rva003C8482Entry> vecOfTransports;

	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		if (!obj)
			continue;

		if (obj->isKindOf(0x15)) {
			ContainModuleInterface *contain = obj->getContain();
			if (contain)
				vecOfTransports.push_back(Rva003C8482Entry::make(obj->getID(), ((TransportContain *)obj->getContain())->getContainMax()));
		} else {
			Object *container = obj->getContainedBy();
			if (container && container->isKindOf(0x6D))
				obj = container;
			Rva003C8482Entry entry = Rva003C8482Entry::make(obj->getID(), obj->rva0028FBBE());
			bool found = false;
			for (_STL::vector<Rva003C8482Entry>::iterator it = vecOfUnits.begin(); it != vecOfUnits.end(); ++it) {
				if (entry.first == (*it).first) {
					found = true;
					break;
				}
			}
			if (!found)
				vecOfUnits.push_back(entry);
		}
	}

	PartitionSolver partition(*(const EntriesVec *)&vecOfUnits, *(const SpacesVec *)&vecOfTransports, PREFER_FAST_SOLUTION);
	partition.solve();
	Rva003C8482SolutionVec solution = partition.rva002A9808();
	for (int i = 0; i < solution.size(); ++i) {
		Object *unit = TheGameLogic->findObjectByID(solution[i].first);
		Object *trans = TheGameLogic->findObjectByID(solution[i].second);
		if (!unit || !trans)
			continue;
		if (unit->getAIUpdateInterface())
			unit->getAIUpdateInterface()->m_command.rva0026C347(trans, CMD_FROM_SCRIPT);
	}
}
