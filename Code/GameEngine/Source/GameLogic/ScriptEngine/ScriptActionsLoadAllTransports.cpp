// cl: /G7 /O1 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /I. /D_STLP_NO_EXCEPTIONS
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
// ZH semantic donor at BFME1 cee35b7d8; WB FFF700 independently
// identifies this action and its branch order. Native 003C8482..003C8669.
// Native storage is eight-byte ObjectID/count and ObjectID/ObjectID pairs.
// Shared BfmeE8 providers implement push539A2E and copy4334D7; the original
// target template spelling is not inferred from these folded bodies.
// Visible native iterator49/advance32 and lookup37/hash47 reproduce all
// their bytes and relocations and preserve the parent register allocation.

#include "ascii_string.h"
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
#include <vector>
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

enum CommandSourceType { CMD_FROM_SCRIPT = 1 };
typedef unsigned int UnsignedInt;

// Existing retail-compatible storage providers carry two 32-bit words.
struct BfmeE8 { int a,b; };
// Keep the shared push provider 0x00539A2E: declared only, so this unit
// emits neither push_back nor its overflow (the decl-only overflow alone
// left a push_back copy that is not retail's body).
namespace _STL {
template <> void vector<BfmeE8, allocator<BfmeE8> >::push_back(const BfmeE8 &);
}
typedef _STL::pair<ObjectID,UnsignedInt> TransportPartitionEntry;
typedef BfmeE8 TransportPartitionAssignment;
typedef _STL::vector<_STL::pair<ObjectID, UnsignedInt> > EntriesVec;
typedef _STL::vector<_STL::pair<ObjectID, UnsignedInt> > SpacesVec;
typedef _STL::vector<TransportPartitionAssignment> TransportSolutionStorage;

static __forceinline void pushEntry(_STL::vector<BfmeE8> &vec, const TransportPartitionEntry &entry) { reinterpret_cast<_STL::vector<BfmeE8>&>(vec).push_back(reinterpret_cast<const BfmeE8&>(entry)); }

enum SolutionType { PREFER_FAST_SOLUTION = 0, PREFER_CORRECT_SOLUTION = 0x7FFFFFFF };

class PartitionSolver
{
public:
	PartitionSolver(const EntriesVec &data, const SpacesVec &spaces, SolutionType howToSolve);
	~PartitionSolver();
	void solve(void);
	const _STL::vector<_STL::pair<ObjectID,ObjectID> > &getSolution(void) const; // getSolution

private:
	SolutionType m_howToSolve;
	EntriesVec m_data;
	SpacesVec m_spacesForData;
	TransportSolutionStorage m_currentSolution;
	UnsignedInt m_currentSolutionLeftovers;
	TransportSolutionStorage m_bestSolution;
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

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail { public: unsigned char m_carrier[4]; };
class BfmeObjectDlinkBase { public: Object *dlink_next_TeamMemberList() const; const ThingTemplate *m_template; unsigned char m_pad[0x60]; };
class Object : public Thing, public BfmeObjectDlinkBase, public BfmeObjectVbptrCarrier
{
public:
	virtual ~Object();
	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline bool isKindOf(int t) const { return getTemplate()->isKindOf(t); }
	__declspec(dllimport) __forceinline ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	int getTransportSlotCount(); // transport slot count
	ObjectID getID() const { return m_id; }
	Object *getContainedBy() const { return m_containedBy; }

private:
	unsigned char m_pad70[4];
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
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc next):m_cur(cur),m_next(next) {}
	__declspec(noinline) void advance() { if(m_cur) m_cur=(m_cur->*m_next)(); }
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }

private:
	OBJCLASS *m_cur;
	GetNextFunc m_next;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
private:
	unsigned char m_pad[0x38];
	Object *m_head;
};

inline __declspec(noinline) DLINK_ITERATOR<Object> Team::iterate_TeamMemberList() const { return DLINK_ITERATOR<Object>(m_head, &Object::dlink_next_TeamMemberList); }
#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;


// Storage and traversal from native _M_find2888D4 and pinned STLport reference.
struct TransportObjectLookupNode { TransportObjectLookupNode *next; ObjectID key; Object *object; };
struct TransportObjectLookupBuckets {
 TransportObjectLookupNode **begin,**end,**capacity;
 unsigned int size() const { return end-begin; }
 TransportObjectLookupNode *const &operator[](unsigned int i) const { return begin[i]; }
};
struct TransportObjectLookupMap { unsigned char hashEqual[4]; TransportObjectLookupBuckets buckets; };
inline __declspec(noinline) ObjectIdNode *ObjectIdMap::find(const ObjectID &id) {
 TransportObjectLookupMap *map=(TransportObjectLookupMap*)this;
 unsigned int bucket=(unsigned int)id % map->buckets.size();
 TransportObjectLookupNode *node;
 for(node=map->buckets[bucket];node && node->key!=id;node=node->next) {}
 return (ObjectIdNode*)node;
}

inline __declspec(noinline) Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == INVALID_OBJECT_ID)
		return 0;
	ObjectIdNode *node = m_map.find(id);
	if (node == 0)
		return 0;
	return node->object;
}



void ScriptActions::doLoadAllTransports(const AsciiString &teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	_STL::vector<BfmeE8> vecOfUnits;
	_STL::vector<BfmeE8> vecOfTransports;

	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		if (!obj)
			continue;

		if (obj->isKindOf(0x15)) {
			ContainModuleInterface *contain = obj->getContain();
			if (contain)
				pushEntry(vecOfTransports, _STL::make_pair(obj->getID(), ((TransportContain *)obj->getContain())->getContainMax()));
		} else {
			Object *container = obj->getContainedBy();
			if (container && container->isKindOf(0x6D))
				obj = container;
			TransportPartitionEntry entry = _STL::make_pair(obj->getID(), obj->getTransportSlotCount());
			bool found = false;
			for (_STL::vector<BfmeE8>::iterator it = vecOfUnits.begin(); it != vecOfUnits.end(); ++it) {
				if (entry.first == (*it).a) {
					found = true;
					break;
				}
			}
			if (!found)
				pushEntry(vecOfUnits, entry);
		}
	}

	PartitionSolver partition(*(const EntriesVec *)&vecOfUnits, *(const SpacesVec *)&vecOfTransports, PREFER_FAST_SOLUTION);
	partition.solve();
	TransportSolutionStorage solution = reinterpret_cast<const TransportSolutionStorage &>(partition.getSolution());
	for (int i = 0; i < solution.size(); ++i) {
		Object *unit = TheGameLogic->findObjectByID((ObjectID)solution[i].a);
		Object *trans = TheGameLogic->findObjectByID((ObjectID)solution[i].b);
		if (!unit || !trans)
			continue;
		if (unit->getAIUpdateInterface())
			unit->getAIUpdateInterface()->m_command.rva0026C347(trans, CMD_FROM_SCRIPT);
	}
}
