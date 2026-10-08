// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ScriptEngine::reset, retail 0x00209ABE (855B), slot 9 of the vtable at
// 0x007E3D70 (ScriptEngine_init.cpp).
//
// Identity (target): the WorldBuilder twin 0xB33190 carries the name
// ScriptEngine::reset and asserts "m_allObjectTypeLists should be empty" at
// ScriptEngine.cpp line 1121. Its call list matches retail's in order, each
// callee read at the retail REL32: GameEngine slot 18 with GlobalData +0x28,
// InGameUI::setInputEnabled 0x0029AB35, Mouse::setVisibility 0x001EE5D6, the
// ScriptActions/ScriptConditions reset (slot 9), the five map clears
// 0x00206EC7..0x00206F6B, Sin/Cos, cleanupSequentialScript 0x00204733,
// removeObjectTypes 0x002046E4 and the pointer-vector erase 0x001FF51F, the
// range erases 0x00207F40 and 0x00207F0D, the list clear 0x0023DAA5, the
// ScienceType vector erase 0x00532803, ScriptList 0x003B7720/0x003B774B,
// SidesList::getSideInfo 0x002035BA, SidesInfo::setScriptList 0x003297F3,
// BfmeOwnedStringState::resetOwnedObject 0x00357E4C and 0x00204984.
// The member stores follow the WB twin's order. The breeze constants are
// Zero Hour's expressions with BFME2's factors (0x3CE1307A = 0.035f*PI/4,
// 0x3C80ADFD = 0.02f*PI/4); WB computes the period as frames*5*2.
// Donor: Zero Hour ScriptEngine::reset for the engine/UI resets, the breeze
// defaults, the sequential-script and object-type loops and the per-player
// clears. The WB debug statistics block is compiled out of retail.
//
// Shared bodies. Retail folds every list clear here to 0x0023DAA5 (WB calls
// three different instantiations), so the lists are viewed as list<int>, the
// name the ledger rows there. The +0x1A120 named-object vector of 8-byte
// AsciiString pairs is cleared through the FXBoneInfo spelling of the folded
// erase at 0x00207F0D, as ScriptEngine_rva0020A7C9.cpp does.
#include "ascii_string.h"
#include <list>
#include <vector>

struct FXBoneInfo
{
	AsciiString m_boneName;
	const void *m_template;
};

struct BfmeStringRecord00204A30
{
	~BfmeStringRecord00204A30();

	unsigned int word0;
	AsciiString text0;
	unsigned int word1;
	AsciiString text1;
	unsigned int word2;
};

// This TU only calls the range erases owned by FXBoneInfoVectorErase.cpp and
// BfmeStringRecordErase00207F40.cpp; declaration-only views keep STLport
// from emitting second copies of their helpers here.
namespace _STL
{
template <> class vector<FXBoneInfo, allocator<FXBoneInfo> >
{
public:
	typedef FXBoneInfo *iterator;
	iterator begin() { return m_start; }
	iterator end() { return m_finish; }
	iterator erase(iterator first, iterator last);
	void clear() { erase(begin(), end()); }

private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};

template <> class vector<BfmeStringRecord00204A30, allocator<BfmeStringRecord00204A30> >
{
public:
	typedef BfmeStringRecord00204A30 *iterator;
	iterator begin() { return m_start; }
	iterator end() { return m_finish; }
	iterator erase(iterator first, iterator last);
	void clear() { erase(begin(), end()); }

private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};
}

typedef int Int;
typedef float Real;

extern int g_Va00DBA4E4;
#define LOGICFRAMES_PER_SECOND g_Va00DBA4E4
#define PI 3.14159265359f

Real Sin(Real x);
Real Cos(Real x);

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class ObjectTypes;
class SequentialScript;

class Rva00206593
{
public:
	void rva00206EC7();

private:
	char m_tree[0xC];
};

class Rva002065C8
{
public:
	void rva00206EF0();

private:
	char m_tree[0xC];
};

class Rva002065FD
{
public:
	void rva00206F19();

private:
	char m_tree[0xC];
};

class Rva00206632
{
public:
	void rva00206F42();

private:
	char m_tree[0xC];
};

class Rva00206667
{
public:
	void rva00206F6B();

private:
	char m_tree[0xC];
};

class BfmeOwnedStringState
{
public:
	void resetOwnedObject();

private:
	char m_body[0x10];
};

class Rva00204136
{
public:
	void rva00204984();

private:
	char m_body[0xC];
};

class ScriptEngine
{
public:
	virtual void reset();

protected:
	typedef std::vector<SequentialScript *> VecSequentialScriptPtr;
	typedef VecSequentialScriptPtr::iterator VecSequentialScriptPtrIt;
	typedef std::vector<ObjectTypes *> VecObjectTypesPtr;
	typedef VecObjectTypesPtr::iterator VecObjectTypesPtrIt;

	void removeObjectTypes(ObjectTypes *typesToRemove);
	VecSequentialScriptPtrIt cleanupSequentialScript(VecSequentialScriptPtrIt it, bool cleanDanglers, bool removeEntry);

private:
	char m_pad04[0x10 - 0x04];
	VecSequentialScriptPtr m_sequentialScripts;		// +0x10
	char m_pad1C[0x190A0 - 0x1C];
	Rva00206593 m_map190A0;	// +0x190A0
	Rva002065C8 m_map190AC;	// +0x190AC
	Rva002065FD m_map190B8;	// +0x190B8
	Rva00206632 m_map190C4;	// +0x190C4
	Rva00206667 m_map190D0;	// +0x190D0
	char m_pad190DC[0x19100 - 0x190DC];
	BfmeOwnedStringState m_ownedStrings[256];	// +0x19100
	Int m_unknown1A100;					// +0x1A100
	Int m_unknown1A104;					// +0x1A104
	Int m_unknown1A108;					// +0x1A108
	AsciiString m_currentScope;			// +0x1A10C
	void *m_callingTeam;				// +0x1A110
	void *m_callingObject;				// +0x1A114
	void *m_conditionTeam;				// +0x1A118
	void *m_conditionObject;			// +0x1A11C
	std::vector<FXBoneInfo> m_namedObjects;	// +0x1A120
	bool m_unknown1A12C;				// +0x1A12C
	Int m_unknown1A130;					// +0x1A130
	Int m_unknown1A134;					// +0x1A134
	Int m_unknown1A138;					// +0x1A138
	bool m_unknown1A13C;				// +0x1A13C
	Real m_unknown1A140;				// +0x1A140
	Real m_unknown1A144;				// +0x1A144
	Real m_unknown1A148;				// +0x1A148
	Int m_unknown1A14C;					// +0x1A14C
	Int m_unknown1A150;					// +0x1A150
	Int m_unknown1A154;					// +0x1A154
	Int m_unknown1A158;					// +0x1A158
	Int m_unknown1A15C;					// +0x1A15C
	Int m_unknown1A160;					// +0x1A160
	Rva00204136 m_objectCounts[20];	// +0x1A164
	std::list<int> m_list1A254;			// +0x1A254
	std::list<int> m_list1A258;			// +0x1A258
	std::list<int> m_list1A25C;			// +0x1A25C
	std::list<int> m_list1A260;			// +0x1A260
	std::list<int> m_list1A264;			// +0x1A264
	std::list<int> m_triggeredSpecialPowers[20];	// +0x1A268
	std::list<int> m_midwaySpecialPowers[20];		// +0x1A2B8
	std::list<int> m_finishedSpecialPowers[20];		// +0x1A308
	std::list<int> m_completedUpgrades[20];			// +0x1A358
	std::vector<ScienceType> m_acquiredSciences[20];	// +0x1A3A8
	std::list<int> m_list1A498;			// +0x1A498
	std::vector<BfmeStringRecord00204A30> m_namedReveals;	// +0x1A49C
	Real m_breezeDirection;				// +0x1A4A8
	Real m_breezeDirectionX;			// +0x1A4AC
	Real m_breezeDirectionY;			// +0x1A4B0
	Real m_breezeIntensity;				// +0x1A4B4
	Real m_breezeLean;					// +0x1A4B8
	Real m_breezeRandomness;			// +0x1A4BC
	short m_breezePeriod;				// +0x1A4C0
	short m_breezeVersion;				// +0x1A4C2
	Int m_unknown1A4C4;					// +0x1A4C4
	VecObjectTypesPtr m_allObjectTypeLists;	// +0x1A4C8
	bool m_freezeByScript;				// +0x1A4D4
	bool m_unknown1A4D5;				// +0x1A4D5
	bool m_unknown1A4D6;				// +0x1A4D6
	bool m_unknown1A4D7;				// +0x1A4D7
};

class GlobalData
{
public:
	char m_pad[0x28];
	Int m_framesPerSecondLimit;			// +0x28
};
extern GlobalData *TheWritableGlobalData;

class GameEngine
{
public:
	virtual ~GameEngine();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void setFramesPerSecondLimit(Int fps);	// slot 18 (+0x48)
};
extern GameEngine *TheGameEngine;

class InGameUI
{
public:
	void setInputEnabled(bool enable);
};
extern InGameUI *TheInGameUI;

class Mouse
{
public:
	void setVisibility(bool visible);
};
extern Mouse *TheMouse;

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void reset();
};

class ScriptActions : public SubsystemInterface
{
};
extern ScriptActions *TheScriptActions;

class ScriptConditions : public SubsystemInterface
{
};
extern ScriptConditions *TheScriptConditions;

class ScriptList
{
public:
	ScriptList();
	~ScriptList();

private:
	char m_body[0x4C];
};

class SidesInfo
{
public:
	void setScriptList(ScriptList *scriptList);
};

class SidesList
{
public:
	Int getNumSides() { return m_numSides; }
	SidesInfo *getSideInfo(Int side);

private:
	char m_pad[0x3C];
	Int m_numSides;						// +0x3C
};
extern SidesList *TheSidesList;

void ScriptEngine::reset()
{
	if (TheGameEngine && TheWritableGlobalData)
		TheGameEngine->setFramesPerSecondLimit(TheWritableGlobalData->m_framesPerSecondLimit);

	if (TheInGameUI)
		TheInGameUI->setInputEnabled(true);
	if (TheMouse)
		TheMouse->setVisibility(true);

	if (TheScriptActions)
		TheScriptActions->reset();
	if (TheScriptConditions)
		TheScriptConditions->reset();

	m_unknown1A100 = 1;
	m_unknown1A104 = -1;
	m_unknown1A108 = -1;
	m_unknown1A12C = true;
	m_callingTeam = 0;
	m_callingObject = 0;
	m_conditionTeam = 0;
	m_conditionObject = 0;
	m_unknown1A130 = 0;
	m_unknown1A134 = 0;
	m_unknown1A15C = 0;
	m_unknown1A160 = 0;
	m_unknown1A138 = 0;
	m_unknown1A14C = 0;
	m_unknown1A140 = 1.0f;
	m_unknown1A144 = 0.0f;
	m_unknown1A150 = 0;
	m_unknown1A154 = 0;
	m_unknown1A158 = 0;
	m_unknown1A148 = 0.0f;
	m_unknown1A13C = false;
	m_unknown1A4D7 = false;

	m_map190A0.rva00206EC7();
	m_map190AC.rva00206EF0();
	m_map190B8.rva00206F19();
	m_map190C4.rva00206F42();
	m_map190D0.rva00206F6B();

	m_breezeDirection = PI/3;
	m_breezeDirectionX = Sin(m_breezeDirection);
	m_breezeDirectionY = Cos(m_breezeDirection);
	m_breezeIntensity = 0.035f*PI/4.0f;
	m_breezeLean = 0.02f*PI/4.0f;
	m_breezePeriod = LOGICFRAMES_PER_SECOND*5*2;
	m_breezeRandomness = 0.2f;
	m_breezeVersion = 0;

	m_freezeByScript = false;
	m_unknown1A4C4 = 1;
	m_unknown1A4D5 = true;
	m_unknown1A4D6 = false;

	while (!m_sequentialScripts.empty())
		cleanupSequentialScript(m_sequentialScripts.begin(), true, true);

	VecObjectTypesPtrIt it;
	for (it = m_allObjectTypeLists.begin(); it != m_allObjectTypeLists.end(); it = m_allObjectTypeLists.begin()) {
		if (*it)
			removeObjectTypes(*it);
		else
			m_allObjectTypeLists.erase(it);
	}

	m_namedReveals.clear();
	m_namedObjects.clear();

	m_list1A254.clear();
	m_list1A260.clear();
	m_list1A258.clear();
	m_list1A25C.clear();
	m_list1A264.clear();

	Int i;
	for (i = 0; i < 20; i++) {
		m_triggeredSpecialPowers[i].clear();
		m_midwaySpecialPowers[i].clear();
		m_finishedSpecialPowers[i].clear();
		m_acquiredSciences[i].clear();
		m_completedUpgrades[i].clear();
	}

	if (TheSidesList) {
		Int numSides = TheSidesList->getNumSides();
		for (i = 0; i < numSides; i++) {
			ScriptList emptyList;
			TheSidesList->getSideInfo(i)->setScriptList(&emptyList);
		}
	}

	for (i = 0; i < 256; i++)
		m_ownedStrings[i].resetOwnedObject();
	for (i = 0; i < 20; i++)
		m_objectCounts[i].rva00204984();

	m_list1A498.clear();
}
