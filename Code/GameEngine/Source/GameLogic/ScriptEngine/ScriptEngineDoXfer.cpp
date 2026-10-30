// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata /O1 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /D_STLP_NO_EXCEPTIONS /arch:SSE /G7 /DBFME_SNAPSHOT_CAPITALIZED_SLOTS
// stlport46
//
// ScriptEngine::DoXfer, retail 0x0020A859 (6131 B): the script engine's save
// game block, version 5. Retail evidence: the Snapshot thunk of the
// ScriptEngine vtable, WorldBuilder's ScriptEngine.cpp lines 4309..4923 (its
// four DEBUG_CRASH texts name m_sequentialScripts, MAX_ATTACK_PRIORITIES,
// m_namedObjects, m_namedReveals and m_allObjectTypeLists) and the rowed
// helpers it calls. Zero Hour's ScriptEngine::xfer supplies the section order
// and the member names; BFME 2 turned the counters and flags into keyed maps
// and added the living-world maps, the per-player special power lists and the
// version 2/3 maps after the object type lists.
//
// Retail compiles the list fills 0x0020700F and 0x00207F91 (and the list
// push_back 0x00207B90) in this unit ahead of DoXfer; defined here with a
// visible STLport push_back they give retail's loop entries. m_namedObjects is
// cleared through the folded erase at 0x00207F0D (FXBoneInfo view below), and
// the STL helpers retail folds by ICF have alias rows naming this unit. The
// EH graph is exact, so its unwind funclets are rowed here as $L labels.
// History of the walls this closed:
//   reverse/attempt_support/script-engine-doxfer-20a859/README.md
#include "ascii_string.h"
#include <map>
#include <list>
#include <vector>
#include "Common/Snapshot.h"
#include "../../Common/GameLogicObjectLookupView.h"
#include "../../Common/BfmeSpecialPowerTimer8.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
// Suppress this TU's non-retail copy of ?_M_create_node@?$list@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@V?$allocator@U?:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString; struct NoCaseTreeValue4;
namespace _STL { template <> _List_node<pair<AsciiString const ,NoCaseTreeValue4> > * list<pair<AsciiString const ,NoCaseTreeValue4>,allocator<pair<AsciiString const ,NoCaseTreeValue4> > >::_M_create_node(pair<AsciiString const ,NoCaseTreeValue4> const &); }
// Suppress this TU's non-retail copy of ??$_Construct@HH@_STL@@YAXPAHABH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _Construct<int,int>(int *,int const &); }

class GameLogic;
extern GameLogic *TheGameLogic;

namespace _STL {
template<class T,class L,class R>
static inline bool operator!=(const _Rb_tree_iterator<T,L>& a,const _Rb_tree_iterator<T,R>& b) {
 return a._M_node!=b._M_node;
}
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a, const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef short Short;
typedef float Real;
typedef bool Bool;

struct XferVersion
{
	XferVersion(UnsignedByte version, UnsignedByte currentVersion) :
		m_version(version), m_currentVersion(currentVersion)
	{
	}
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

// Operand declarations precede the shared interface; their layouts are not
// needed by this unit's virtual transfers.
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
#include "../../../Include/Common/BfmeXfer.h"

// Native constructor 0x0060C36E and throw type CFFD18 identify the real class.
class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &);
	~XferException();
	char *text;
	int tag;
};

struct ScriptCounter
{
	int m_value;
	bool m_isCountdownTimer;
	bool m_isMillisecondTimer;
	ScriptCounter() : m_value(0), m_isCountdownTimer(false), m_isMillisecondTimer(false) {}
};

typedef _STL::pair<AsciiString,AsciiString> ScriptKey;
struct TeamLess0019B850 : _STL::less<ScriptKey> {};
typedef _STL::map<ScriptKey,ScriptCounter> ScriptCounterMap;
struct ScriptFlag
{
	Bool m_value;
	ScriptFlag() : m_value(false) {}
};
typedef _STL::map<ScriptKey,ScriptFlag> ScriptFlagMap;
typedef _STL::map<ScriptKey,int,TeamLess0019B850> ScriptDefaultIntMap;
namespace _STL { template <> ScriptDefaultIntMap::_Rep_type::_Link_type ScriptDefaultIntMap::_Rep_type::_M_create_node(const ScriptDefaultIntMap::value_type &); }

typedef _STL::map<ScriptKey,AsciiString> ScriptStringMap;
typedef _STL::map<AsciiString,unsigned char> ScriptByteMap;

struct NoCaseTreeValue4
{
	unsigned int m_value;
	NoCaseTreeValue4() : m_value(0) {}
};
typedef _STL::list<_STL::pair<const AsciiString,NoCaseTreeValue4> > ListAsciiStringValue;
void __cdecl Rva0020596AConstruct(void *dest, const void *source);
namespace _STL {
template <> _List_node<pair<const AsciiString, NoCaseTreeValue4> > *
list<pair<const AsciiString, NoCaseTreeValue4>, allocator<pair<const AsciiString, NoCaseTreeValue4> > >::_M_create_node(const pair<const AsciiString, NoCaseTreeValue4> &value)
{
    _Node *node = (_Node *)allocator<char>::allocate(sizeof(_Node), 0);
    Rva0020596AConstruct(&node->_M_data, &value);
    return node;
}
}

typedef _STL::list<BfmeSpecialPowerTimer8> ListSpecialPowerTimer;
typedef _STL::list<AsciiString> ListAsciiString;
typedef _STL::list<int> ListInt;
typedef _STL::list<_STL::pair<AsciiString,Coord3D> > ListAsciiStringCoord3D;

struct BfmeFloat4Record00469C61
{
	unsigned int m_frame;
	Coord3D m_position;
	BfmeFloat4Record00469C61() {}
	// Retail's _Construct (0x469C61) calls this copy constructor out of line (0x4254E).
	__declspec(noinline) BfmeFloat4Record00469C61(const BfmeFloat4Record00469C61 &o) : m_frame(o.m_frame)
	{ m_position.x = o.m_position.x; m_position.y = o.m_position.y; m_position.z = o.m_position.z; }
};
typedef _STL::list<BfmeFloat4Record00469C61> ListToppleRecord;

struct BfmeStringRecord00204A30
{
	unsigned long word0;
	AsciiString text0;
	float word1;
	AsciiString text1;
	int word2;
	~BfmeStringRecord00204A30();
};

class Object
{
	char m_pad[0x74];
public:
	ObjectID m_id;
	ObjectID getID() const { return m_id; }
};

// Retail clears m_namedObjects through the folded eight-byte-pair range erase
// at 0x00207F0D, rowed as vector<FXBoneInfo>::erase in FXBoneInfoVectorErase.cpp.
// As in ScriptEngine_rva0020A7C9.cpp, which clears the same vector, call it
// through a declaration-only view so this unit emits no second erase copy.
struct FXBoneInfo
{
	AsciiString m_boneName;
	const void *m_template;
};

namespace _STL
{
template <> class vector<FXBoneInfo, allocator<FXBoneInfo> >
{
public:
	typedef FXBoneInfo *iterator;
	iterator begin() { return m_start; }
	iterator end() { return m_finish; }
	iterator erase(iterator first, iterator last);

private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};
}

struct Rva0020A227Element
{
	AsciiString key;
	Object *obj;
	Rva0020A227Element() : obj(0) {}
};

// Retail 0x0020479E (Rva0020479ECtor.cpp): stores only, so loading needs no
// unwind state around the allocation.
struct SequentialScriptQuad
{
	int m_count0;
	int m_index0;
	int m_count1;
	int m_index1;
	SequentialScriptQuad() : m_count0(0), m_index0(-1), m_count1(0), m_index1(-1) {}
};

// Snapshot occupies offset zero; this view spells its four retail slots.
class SequentialScript
{
public:
	SequentialScript() : m_04(0), m_08(0), m_0c(0), m_10(0), m_24(0), m_28(0) {}
	virtual ~SequentialScript(); // Rva00205224Dtor.cpp (0x00205224)
protected:
	virtual void loadPostProcess();
public:
	virtual const char *GetSnapshotName();
protected:
	virtual void xfer(Xfer *xfer);
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	SequentialScriptQuad m_14;
	unsigned char m_24;
	int m_28;
};

class ObjectTypes : public Snapshot
{
public:
	ObjectTypes();
protected:
	virtual void LoadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void DoXfer(Xfer *xfer);
	char m_data[0x10];
};

class AttackPriorityInfo : public Snapshot
{
protected:
	virtual void LoadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void DoXfer(Xfer *xfer);
	char m_data[0xC];
};

class Rva00203D4EA;
void Rva00203D4EChain(Rva00203D4EA *xfer, void *key);
void XferLivingWorldArmyID(Xfer *xfer, int *id);
void XferLivingWorldPlayerID(Xfer *xfer, int *id);
void XferObjectID(Xfer *xfer, ObjectID *id);
void XferGameDifficulty(Xfer *xfer, int *difficulty);
unsigned long CRC_String(const char *text);
unsigned long Rva003ECA13Get(const AsciiString &text);
Xfer *xferListInt(Xfer *xfer, ListInt *list);
Xfer *Rva00206923XferList(Xfer *xfer, ListSpecialPowerTimer *list);
Xfer *xferList2069F0(Xfer *xfer, ListToppleRecord *list);
Xfer *Rva0020700FXfer(Xfer *xfer, ListAsciiString *list);
Xfer *Rva002070F7Xfer(Xfer *xfer, ListSpecialPowerTimer *lists);
Xfer *Rva00207F91XferList(Xfer *xfer, ListAsciiStringValue *list);
Xfer *Rva00208081Xfer(Xfer *xfer, void *lists);
Xfer *Rva002080DAXferList(Xfer *xfer, ListAsciiStringCoord3D *list);
Xfer *Rva00209A09Xfer(Xfer *xfer, ListAsciiStringValue *lists);

class Rva00206593 { public: void rva00206EC7(); };
class Rva002065C8 { public: void rva00206EF0(); };
class Rva002065FD { public: void rva00206F19(); };
class Rva00206632 { public: void rva00206F42(); };
class Rva00206667 { public: void rva00206F6B(); };
class Rva0020669C { public: void rva00206F94(); };
class Rva002066D1 { public: void rva00206FBD(); };
class Rva00206706 { public: void rva00206FE6(); };

enum { MAX_ATTACK_PRIORITIES = 256, MAX_PLAYER_COUNT = 20 };

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

class ScriptEngine : public SubsystemInterface, public Snapshot
{
public:
	typedef _STL::vector<SequentialScript *> VecSequentialScriptPtr;
	typedef _STL::vector<Rva0020A227Element> VecNamedRequests;
	typedef _STL::vector<BfmeStringRecord00204A30> VecNamedReveal;
	typedef _STL::vector<ObjectTypes *> AllObjectTypes;
	virtual void LoadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void DoXfer(Xfer *xfer);
protected:

	VecSequentialScriptPtr m_sequentialScripts;          // 0x10
	char m_pad1C[0x190A0 - 0x1C];
	ScriptCounterMap m_counters;                          // 0x190A0
	ScriptFlagMap m_flags;                                // 0x190AC
	ScriptDefaultIntMap m_objectIDs;                      // 0x190B8
	ScriptDefaultIntMap m_values;                         // 0x190C4
	ScriptByteMap m_byteFlags;                            // 0x190D0
	ScriptDefaultIntMap m_players;                        // 0x190DC
	ScriptDefaultIntMap m_armies;                         // 0x190E8
	ScriptStringMap m_strings;                            // 0x190F4
	AttackPriorityInfo m_attackPriorityInfo[MAX_ATTACK_PRIORITIES]; // 0x19100
	Int m_numAttackInfo;                                  // 0x1A100
	Int m_endGameTimer;                                   // 0x1A104
	Int m_closeWindowTimer;                               // 0x1A108
	AsciiString m_currentTrackName;                       // 0x1A10C
	char m_pad1A110[0x1A120 - 0x1A110];
	VecNamedRequests m_namedObjects;                      // 0x1A120
	Bool m_firstUpdate;                                   // 0x1A12C
	char m_pad1A12D[0x1A138 - 0x1A12D];
	Int m_fade;                                           // 0x1A138
	char m_pad1A13C[4];
	Real m_minFade;                                       // 0x1A140
	Real m_maxFade;                                       // 0x1A144
	Real m_curFadeValue;                                  // 0x1A148
	Int m_curFadeFrame;                                   // 0x1A14C
	Int m_fadeFramesIncrease;                             // 0x1A150
	Int m_fadeFramesHold;                                 // 0x1A154
	Int m_fadeFramesDecrease;                             // 0x1A158
	UnsignedInt m_unknown1A15C;                           // 0x1A15C
	UnsignedInt m_unknown1A160;                           // 0x1A160
	char m_pad1A164[0x1A254 - 0x1A164];
	ListInt m_completedVideo;                             // 0x1A254
	ListSpecialPowerTimer m_testingSpeech;                // 0x1A258
	ListSpecialPowerTimer m_testingAudio;                 // 0x1A25C
	ListInt m_uiInteractions;                             // 0x1A260
	ListInt m_list1A264;                                  // 0x1A264
	ListSpecialPowerTimer m_triggeredSpecialPowers[MAX_PLAYER_COUNT]; // 0x1A268
	ListSpecialPowerTimer m_midwaySpecialPowers[MAX_PLAYER_COUNT];    // 0x1A2B8
	ListSpecialPowerTimer m_finishedSpecialPowers[MAX_PLAYER_COUNT];  // 0x1A308
	ListSpecialPowerTimer m_completedUpgrades[MAX_PLAYER_COUNT];      // 0x1A358
	char m_acquiredSciences[0xF0];                        // 0x1A3A8
	ListToppleRecord m_toppleDirections;                  // 0x1A498
	VecNamedReveal m_namedReveals;                        // 0x1A49C
	Real m_breezeDirection;                               // 0x1A4A8
	Real m_breezeDirectionX;                              // 0x1A4AC
	Real m_breezeDirectionY;                              // 0x1A4B0
	Real m_breezeIntensity;                               // 0x1A4B4
	Real m_breezeLean;                                    // 0x1A4B8
	Real m_breezeRandomness;                              // 0x1A4BC
	Short m_breezePeriod;                                 // 0x1A4C0
	Short m_breezeVersion;                                // 0x1A4C2
	Int m_gameDifficulty;                                 // 0x1A4C4
	AllObjectTypes m_allObjectTypeLists;                  // 0x1A4C8
	Bool m_bool1A4D4;                                     // 0x1A4D4
	Bool m_objectsShouldReceiveDifficultyBonus;           // 0x1A4D5
	Bool m_ChooseVictimAlwaysUsesNormal;                  // 0x1A4D6
	Bool m_freezeByScript;                                // 0x1A4D7
};

// Retail compiles both list fills in DoXfer's TU before it, and c2 reuses
// their summary that `list` does not escape: DoXfer's loops 1, 3 and 4 then
// enter by jmp-to-test as in retail (handoff README round 4).
static __forceinline UnsignedInt asciiListSize(const ListAsciiString *list)
{
	const _STL::_List_node_base *head = list->_M_node._M_data;
	const _STL::_List_node_base *at = head->_M_next;
	UnsignedInt result = 0;
	while (at != head) { at = at->_M_next; ++result; }
	return result;
}

Xfer *Rva0020700FXfer(Xfer *xfer, ListAsciiString *list)
{
	XferVersion version(1, 1);
	xfer->operator==((Xfer::Version &)version);

	UnsignedInt count = asciiListSize(list);
	xfer->operator==("std::list").operator==(count);

	if (xfer->IsStoring()) {
		ListAsciiString::_Node *sentinel = (ListAsciiString::_Node *)list->_M_node._M_data;
		ListAsciiString::_Node *node = (ListAsciiString::_Node *)sentinel->_M_next;
		while (node != sentinel) {
			xfer->operator==(node->_M_data);
			node = (ListAsciiString::_Node *)node->_M_next;
		}
	} else {
		if (!list->empty()) {
			throw XferException(4, "List must be empty on load");
		}
		AsciiString value;
		while (count != 0) {
			--count;
			xfer->operator==(value);
			list->push_back(value);
		}
		--count;
	}
	return xfer;
}

class Rva00203D6AA;
void Rva00203D6AChain(Rva00203D6AA *a, void *b);

Xfer *Rva00207F91XferList(Xfer *xfer, ListAsciiStringValue *list)
{
	XferVersion version(1, 1);
	xfer->operator==((Xfer::Version &)version);

	UnsignedInt count = (UnsignedInt)list->size();
	xfer->operator==("std::list").operator==(count);

	if (xfer->IsStoring())
	{
		ListAsciiStringValue::_Node *sentinel = (ListAsciiStringValue::_Node *)list->_M_node._M_data;
		ListAsciiStringValue::_Node *node = (ListAsciiStringValue::_Node *)sentinel->_M_next;
		while (node != sentinel)
		{
			Rva00203D6AChain((Rva00203D6AA *)xfer, &node->_M_data);
			node = (ListAsciiStringValue::_Node *)node->_M_next;
		}
	}
	else
	{
		if (!list->empty())
		{
			throw XferException(4, "List must be empty on load");
		}

		ListAsciiStringValue::value_type value;
		while (count != 0)
		{
			--count;
			Rva00203D6AChain((Rva00203D6AA *)xfer, &value);
			list->push_back(value);
		}
		--count;
	}
	return xfer;
}

void ScriptEngine::DoXfer(Xfer *xfer)
{
	Int i;

	if (xfer->IsCRC())
		return;

	XferVersion version(1, 5);
	xfer->operator==((Xfer::Version &)version);
	xfer->operator==(m_freezeByScript);
	xfer->operator==(m_currentTrackName);

	// sequential scripts
	UnsignedShort sequentialScriptCount = m_sequentialScripts.size();
	xfer->operator==(sequentialScriptCount);
	SequentialScript *sequentialScript;
	if (xfer->IsStoring())
	{
		VecSequentialScriptPtr::iterator it;
		for (it = m_sequentialScripts.begin(); it != m_sequentialScripts.end(); ++it)
		{
			sequentialScript = *it;
			xfer->operator==(*((Snapshot *)sequentialScript));
		}
	}
	else
	{
		if (m_sequentialScripts.size() != 0)
			throw XferException(5, 0);
		for (UnsignedShort i = 0; i < sequentialScriptCount; ++i)
		{
			sequentialScript = new SequentialScript;
			m_sequentialScripts.push_back(sequentialScript);
			xfer->operator==(*((Snapshot *)sequentialScript));
		}
	}

	// counters
	UnsignedShort countersSize = m_counters.size();
	xfer->operator==(countersSize);
	if (xfer->IsStoring())
	{
		ScriptCounterMap::iterator end = m_counters.end();
		for (ScriptCounterMap::iterator it = m_counters.begin(); it != end; ++it)
		{
			xfer->operator==(const_cast<ScriptKey &>(it->first).first);
			xfer->operator==(const_cast<ScriptKey &>(it->first).second);
			xfer->operator==(it->second.m_value);
			xfer->operator==(it->second.m_isCountdownTimer);
		}
	}
	else
	{
		((Rva00206593 *)&m_counters)->rva00206EC7();
		for (i = 0; i < countersSize; ++i)
		{
			ScriptKey key;
			xfer->operator==(key.first);
			xfer->operator==(key.second);
			ScriptCounter counter;
			xfer->operator==(counter.m_value);
			xfer->operator==(counter.m_isCountdownTimer);
			m_counters.insert(_STL::make_pair(key, counter));
		}
	}

	// flags
	UnsignedShort flagsSize = m_flags.size();
	xfer->operator==(flagsSize);
	if (xfer->IsStoring())
	{
		ScriptFlagMap::iterator end = m_flags.end();
		for (ScriptFlagMap::iterator it = m_flags.begin(); it != end; ++it)
		{
			xfer->operator==(const_cast<ScriptKey &>(it->first).first);
			xfer->operator==(const_cast<ScriptKey &>(it->first).second);
			xfer->operator==(it->second.m_value);
		}
	}
	else
	{
		((Rva002065C8 *)&m_flags)->rva00206EF0();
		for (i = 0; i < flagsSize; ++i)
		{
			ScriptKey key;
			xfer->operator==(key.first);
			xfer->operator==(key.second);
			ScriptFlag flag;
			xfer->operator==(flag.m_value);
			m_flags.insert(_STL::make_pair(key, flag));
		}
	}

	// living world players, armies and strings
	if (version.m_currentVersion >= 4)
	{
		Int count;
		if (xfer->IsLoading())
		{
			xfer->operator==(count);
			while (count > 0)
			{
				ScriptKey key;
				Rva00203D4EChain((Rva00203D4EA *)xfer, &key);
				UnsignedInt army;
				XferLivingWorldArmyID(xfer, (int *)&army);
				m_armies.insert(ScriptDefaultIntMap::value_type(key, army));
				--count;
			}
			xfer->operator==(count);
			while (count > 0)
			{
				ScriptKey key;
				Rva00203D4EChain((Rva00203D4EA *)xfer, &key);
				AsciiString value;
				xfer->operator==(value);
				m_strings.insert(ScriptStringMap::value_type(key, AsciiString(value)));
				--count;
			}
			xfer->operator==(count);
			while (count > 0)
			{
				ScriptKey key;
				Rva00203D4EChain((Rva00203D4EA *)xfer, &key);
				UnsignedInt player;
				XferLivingWorldPlayerID(xfer, (int *)&player);
				m_players.insert(ScriptDefaultIntMap::value_type(key, player));
				--count;
			}
		}
		else
		{
			count = m_armies.size();
			xfer->operator==(count);
			ScriptDefaultIntMap::iterator it = m_armies.begin();
			ScriptDefaultIntMap::iterator end = m_armies.end();
			while (it != end)
			{
				ScriptKey key(it->first);
				Rva00203D4EChain((Rva00203D4EA *)xfer, &key);
				Int army = it->second;
				XferLivingWorldArmyID(xfer, &army);
				++it;
			}
			count = m_strings.size();
			xfer->operator==(count);
			ScriptStringMap::iterator sit = m_strings.begin();
			ScriptStringMap::iterator send = m_strings.end();
			while (sit != send)
			{
				ScriptKey key(sit->first);
				Rva00203D4EChain((Rva00203D4EA *)xfer, &key);
				AsciiString value(sit->second);
				xfer->operator==(value);
				++sit;
			}
			count = m_players.size();
			xfer->operator==(count);
			ScriptDefaultIntMap::iterator pit = m_players.begin();
			ScriptDefaultIntMap::iterator pend = m_players.end();
			while (pit != pend)
			{
				ScriptKey key(pit->first);
				Rva00203D4EChain((Rva00203D4EA *)xfer, &key);
				Int player = pit->second;
				XferLivingWorldPlayerID(xfer, &player);
				++it;
			}
		}
	}
	else if (xfer->IsLoading())
	{
		((Rva002066D1 *)&m_armies)->rva00206FBD();
		((Rva0020669C *)&m_players)->rva00206F94();
		((Rva00206706 *)&m_strings)->rva00206FE6();
	}

	// attack priority info
	UnsignedShort attackPriorityInfoSize = m_numAttackInfo;
	xfer->operator==(attackPriorityInfoSize);
	if (attackPriorityInfoSize > MAX_ATTACK_PRIORITIES)
		throw XferException(5, 0);
	for (i = 0; i < attackPriorityInfoSize; ++i)
		xfer->operator==(m_attackPriorityInfo[i]);
	xfer->operator==(m_numAttackInfo);
	xfer->operator==(m_endGameTimer);
	xfer->operator==(m_closeWindowTimer);

	// named objects
	UnsignedShort namedObjectsCount = m_namedObjects.size();
	xfer->operator==(namedObjectsCount);
	AsciiString namedObjectName;
	Object *obj;
	ObjectID objectID;
	if (xfer->IsStoring())
	{
		VecNamedRequests::iterator it;
		for (it = m_namedObjects.begin(); it != m_namedObjects.end(); ++it)
		{
			namedObjectName = it->key;
			xfer->operator==(namedObjectName);
			obj = it->obj;
			objectID = obj ? obj->getID() : INVALID_OBJECT_ID;
			XferObjectID(xfer, &objectID);
		}
	}
	else
	{
		Rva0020A227Element req;
		_STL::vector<FXBoneInfo> &named = (_STL::vector<FXBoneInfo> &)m_namedObjects;
		named.erase(named.begin(), named.end());
		for (UnsignedShort i = 0; i < namedObjectsCount; ++i)
		{
			xfer->operator==(namedObjectName);
			XferObjectID(xfer, &objectID);
			obj = TheGameLogic->findObjectByID(objectID);
			if (obj == 0 && objectID != INVALID_OBJECT_ID)
				throw XferException(5, 0);
			req.key = namedObjectName;
			req.obj = obj;
			m_namedObjects.push_back(req);
		}
	}

	// fade
	xfer->operator==(m_firstUpdate);
	xfer->XferRawBytes(&m_fade, sizeof(m_fade));
	xfer->operator==(m_minFade);
	xfer->operator==(m_maxFade);
	xfer->operator==(m_curFadeValue);
	xfer->operator==(m_curFadeFrame);
	xfer->operator==(m_fadeFramesIncrease);
	xfer->operator==(m_fadeFramesHold);
	xfer->operator==(m_fadeFramesDecrease);

	// lists saved by name before version 5, by CRC since
	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiString names;
		Rva0020700FXfer(xfer, &names);
		m_completedVideo.clear();
		for (ListAsciiString::iterator it = names.begin(); it != names.end(); ++it)
			m_completedVideo.push_back(CRC_String(it->str()));
	}
	else
		xferListInt(xfer, &m_completedVideo);

	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiString names;
		Rva0020700FXfer(xfer, &names);
		m_uiInteractions.clear();
		for (ListAsciiString::iterator it = names.begin(); it != names.end(); ++it)
			m_uiInteractions.push_back(CRC_String(it->str()));
	}
	else
		xferListInt(xfer, &m_uiInteractions);

	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiStringValue names;
		Rva00207F91XferList(xfer, &names);
		m_testingSpeech.clear();
		BfmeSpecialPowerTimer8 timer;
		timer.m_templateID = 0;
		timer.m_readyFrame = 0;
		for (ListAsciiStringValue::iterator it = names.begin(); it != names.end(); ++it)
		{
			timer.m_templateID = CRC_String(it->first.str());
			timer.m_readyFrame = it->second.m_value;
			m_testingSpeech.push_back(timer);
		}
	}
	else
		Rva00206923XferList(xfer, &m_testingSpeech);

	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiStringValue names;
		Rva00207F91XferList(xfer, &names);
		m_testingAudio.clear();
		BfmeSpecialPowerTimer8 timer;
		timer.m_templateID = 0;
		timer.m_readyFrame = 0;
		for (ListAsciiStringValue::iterator it = names.begin(); it != names.end(); ++it)
		{
			timer.m_templateID = CRC_String(it->first.str());
			timer.m_readyFrame = it->second.m_value;
			m_testingAudio.push_back(timer);
		}
	}
	else
		Rva00206923XferList(xfer, &m_testingAudio);

	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiString names;
		Rva0020700FXfer(xfer, &names);
		m_list1A264.clear();
		for (ListAsciiString::iterator it = names.begin(); it != names.end(); ++it)
			m_list1A264.push_back(CRC_String(it->str()));
	}
	else
		xferListInt(xfer, &m_list1A264);

	// per-player special power lists
	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiStringValue names[MAX_PLAYER_COUNT];
		Rva00209A09Xfer(xfer, names);
		BfmeSpecialPowerTimer8 timer;
		timer.m_templateID = 0;
		timer.m_readyFrame = 0;
		for (i = 0; i < MAX_PLAYER_COUNT; ++i)
		{
			ListSpecialPowerTimer *list = &m_triggeredSpecialPowers[i];
			list->clear();
			ListAsciiStringValue *old = &names[i];
			for (ListAsciiStringValue::iterator it = old->begin(); it != old->end(); ++it)
			{
				timer.m_templateID = CRC_String(it->first.str());
				timer.m_readyFrame = it->second.m_value;
				list->push_back(timer);
			}
		}
	}
	else
		Rva002070F7Xfer(xfer, m_triggeredSpecialPowers);

	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiStringValue names[MAX_PLAYER_COUNT];
		Rva00209A09Xfer(xfer, names);
		BfmeSpecialPowerTimer8 timer;
		timer.m_templateID = 0;
		timer.m_readyFrame = 0;
		for (i = 0; i < MAX_PLAYER_COUNT; ++i)
		{
			ListSpecialPowerTimer *list = &m_midwaySpecialPowers[i];
			list->clear();
			ListAsciiStringValue *old = &names[i];
			for (ListAsciiStringValue::iterator it = old->begin(); it != old->end(); ++it)
			{
				timer.m_templateID = CRC_String(it->first.str());
				timer.m_readyFrame = it->second.m_value;
				list->push_back(timer);
			}
		}
	}
	else
		Rva002070F7Xfer(xfer, m_midwaySpecialPowers);

	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiStringValue names[MAX_PLAYER_COUNT];
		Rva00209A09Xfer(xfer, names);
		BfmeSpecialPowerTimer8 timer;
		timer.m_templateID = 0;
		timer.m_readyFrame = 0;
		for (i = 0; i < MAX_PLAYER_COUNT; ++i)
		{
			ListSpecialPowerTimer *list = &m_finishedSpecialPowers[i];
			list->clear();
			ListAsciiStringValue *old = &names[i];
			for (ListAsciiStringValue::iterator it = old->begin(); it != old->end(); ++it)
			{
				timer.m_templateID = CRC_String(it->first.str());
				timer.m_readyFrame = it->second.m_value;
				list->push_back(timer);
			}
		}
	}
	else
		Rva002070F7Xfer(xfer, m_finishedSpecialPowers);

	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiStringValue names[MAX_PLAYER_COUNT];
		Rva00209A09Xfer(xfer, names);
		BfmeSpecialPowerTimer8 timer;
		timer.m_templateID = 0;
		timer.m_readyFrame = 0;
		for (i = 0; i < MAX_PLAYER_COUNT; ++i)
		{
			ListSpecialPowerTimer *list = &m_completedUpgrades[i];
			list->clear();
			ListAsciiStringValue *old = &names[i];
			for (ListAsciiStringValue::iterator it = old->begin(); it != old->end(); ++it)
			{
				timer.m_templateID = CRC_String(it->first.str());
				timer.m_readyFrame = it->second.m_value;
				list->push_back(timer);
			}
		}
	}
	else
		Rva002070F7Xfer(xfer, m_completedUpgrades);

	Rva00208081Xfer(xfer, m_acquiredSciences);

	// topple directions
	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiStringCoord3D names;
		Rva002080DAXferList(xfer, &names);
		m_toppleDirections.clear();
		BfmeFloat4Record00469C61 topple;
		topple.m_frame = 0;
		for (ListAsciiStringCoord3D::iterator it = names.begin(); it != names.end(); ++it)
		{
			topple.m_frame = CRC_String(it->first.str());
			topple.m_position = it->second;
			m_toppleDirections.push_back(topple);
		}
	}
	else
		xferList2069F0(xfer, &m_toppleDirections);

	// breeze
	xfer->operator==(m_breezeDirection);
	xfer->operator==(m_breezeDirectionX);
	xfer->operator==(m_breezeDirectionY);
	xfer->operator==(m_breezeIntensity);
	xfer->operator==(m_breezeLean);
	xfer->operator==(m_breezeRandomness);
	xfer->operator==(m_breezePeriod);
	xfer->operator==(m_breezeVersion);
	XferGameDifficulty(xfer, &m_gameDifficulty);
	xfer->operator==(m_bool1A4D4);

	// named reveals
	UnsignedShort namedRevealCount = m_namedReveals.size();
	xfer->operator==(namedRevealCount);
	xfer->operator==(m_unknown1A15C);
	xfer->operator==(m_unknown1A160);
	if (xfer->IsStoring())
	{
		VecNamedReveal::iterator it;
		for (it = m_namedReveals.begin(); it != m_namedReveals.end(); ++it)
		{
			xfer->operator==(*((UnsignedInt *)&it->word0));
			xfer->operator==(it->text0);
			xfer->operator==(it->word1);
			xfer->operator==(it->text1);
		}
	}
	else
	{
		if (m_namedReveals.empty() == false)
			throw XferException(5, 0);
		BfmeStringRecord00204A30 reveal;
		for (UnsignedShort i = 0; i < namedRevealCount; ++i)
		{
			if (version.m_currentVersion >= 5)
				xfer->operator==(*((UnsignedInt *)&reveal.word0));
			else
			{
				AsciiString name;
				xfer->operator==(name);
				reveal.word0 = Rva003ECA13Get(name);
			}
			xfer->operator==(reveal.text0);
			xfer->operator==(reveal.word1);
			xfer->operator==(reveal.text1);
			m_namedReveals.push_back(reveal);
		}
	}

	// object type lists
	UnsignedShort allObjectTypesCount = m_allObjectTypeLists.size();
	xfer->operator==(allObjectTypesCount);
	if (xfer->IsStoring())
	{
		AllObjectTypes::iterator it;
		ObjectTypes *objectTypes;
		for (it = m_allObjectTypeLists.begin(); it != m_allObjectTypeLists.end(); ++it)
		{
			objectTypes = *it;
			xfer->operator==(*(objectTypes));
		}
	}
	else
	{
		if (m_allObjectTypeLists.empty() == false)
			throw XferException(5, 0);
		ObjectTypes *objectTypes;
		for (UnsignedShort i = 0; i < allObjectTypesCount; ++i)
		{
			objectTypes = new ObjectTypes;
			xfer->operator==(*(objectTypes));
			m_allObjectTypeLists.push_back(objectTypes);
		}
	}

	xfer->operator==(m_objectsShouldReceiveDifficultyBonus);
	xfer->operator==(m_ChooseVictimAlwaysUsesNormal);

	if (xfer->IsLoading())
	{
		if (m_fade == 0)
		{
			m_fade = 4;
			m_curFadeFrame = 0;
			m_minFade = 1.0f;
			m_maxFade = 0.0f;
			m_fadeFramesIncrease = 0;
			m_fadeFramesHold = 0;
			m_fadeFramesDecrease = 0;
			m_curFadeValue = 0.0f;
		}
	}

	// keyed object IDs and values
	if (version.m_currentVersion >= 2)
	{
		if (xfer->IsLoading())
		{
			((Rva002065FD *)&m_objectIDs)->rva00206F19();
			UnsignedInt count = 0;
			xfer->operator==(count);
			for (UnsignedInt i = 0; i < count; ++i)
			{
				AsciiString first;
				AsciiString second;
				xfer->operator==(first);
				xfer->operator==(second);
				ObjectID id;
				XferObjectID(xfer, &id);
				ScriptKey key(first, second);
				_STL::pair<ScriptDefaultIntMap::iterator, bool> result = m_objectIDs.insert(_STL::make_pair(key, 0));
				result.first->second = id;
			}
			((Rva00206632 *)&m_values)->rva00206F42();
			count = 0;
			xfer->operator==(count);
			for (UnsignedInt j = 0; j < count; ++j)
			{
				AsciiString first;
				AsciiString second;
				xfer->operator==(first);
				xfer->operator==(second);
				UnsignedInt value;
				xfer->operator==(value);
				ScriptKey key(first, second);
				_STL::pair<ScriptDefaultIntMap::iterator, bool> result = m_values.insert(_STL::make_pair(key, 0));
				result.first->second = value;
			}
		}
		else if (xfer->IsStoring())
		{
			UnsignedInt count = m_objectIDs.size();
			xfer->operator==(count);
			for (ScriptDefaultIntMap::iterator it = m_objectIDs.begin(); it != m_objectIDs.end(); ++it)
			{
				ScriptKey key(it->first);
				ObjectID id = (ObjectID)it->second;
				xfer->operator==(key.first);
				xfer->operator==(key.second);
				XferObjectID(xfer, &id);
			}
			count = m_values.size();
			xfer->operator==(count);
			for (ScriptDefaultIntMap::iterator vit = m_values.begin(); vit != m_values.end(); ++vit)
			{
				ScriptKey key(vit->first);
				UnsignedInt value = vit->second;
				xfer->operator==(key.first);
				xfer->operator==(key.second);
				xfer->operator==(value);
			}
		}
	}

	// keyed byte flags
	if (version.m_currentVersion >= 3)
	{
		if (xfer->IsStoring())
		{
			UnsignedInt count = m_byteFlags.size();
			xfer->operator==(count);
			for (ScriptByteMap::iterator it = m_byteFlags.begin(); it != m_byteFlags.end(); ++it)
			{
				AsciiString name(it->first);
				unsigned char value = it->second;
				xfer->operator==(name);
				xfer->operator==(*((Bool *)&value));
			}
		}
		else if (xfer->IsLoading())
		{
			((Rva00206667 *)&m_byteFlags)->rva00206F6B();
			UnsignedInt count = 0;
			xfer->operator==(count);
			while (count > 0)
			{
				AsciiString name;
				unsigned char value = 0;
				xfer->operator==(name);
				xfer->operator==(*((Bool *)&value));
				m_byteFlags.insert(_STL::make_pair(name, value));
				--count;
			}
		}
	}
}
