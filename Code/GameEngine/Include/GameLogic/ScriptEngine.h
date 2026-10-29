#pragma once
// ScriptEngine: canonical BFME2 header (hand-written; header_adopt_lane's
// generator emits no virtuals, and this class is polymorphic).
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
//
// Target facts, read off game.dat:
//  - The ctor 0x00208343 calls SubsystemInterface's ctor 0x001B4E63, stores the
//    Snapshot base table 0x00BBB554 at +0x0C, then ScriptEngine's own tables:
//    0x007E3D70 at +0x00 and 0x007E3D60 at +0x0C. The dtor 0x0020A2B0 stores
//    the same pair. So ScriptEngine : SubsystemInterface (12 bytes) at +0 and
//    Snapshot at +0x0C; its own data starts at +0x10.
//  - Table 0x007E3D70 has exactly SubsystemInterface's fourteen slots (the
//    string "ScriptEngine" follows slot 13). ScriptEngine overrides slot 0
//    (??_G 0x0020C0C7), 1 init (0x00205AFD), 9 reset (0x00209ABE) and 10 update
//    (0x0020D065) and adds no virtual of its own. Views that declared 26 or
//    more slots (getUnitNamed in slot 26, getActionTemplate in slot 10) never
//    called them; getActionTemplate and getUnitNamed are non-virtual rows
//    (0x00203926, 0x003588E7).
//  - Table 0x007E3D60 (the Snapshot subobject): slot 0 is the this-adjusting
//    thunk 0x002086BD (sub ecx,0xC), slot 3 DoXfer (0x0020A859).
//  - GameEngine::init allocates 0x1A500 bytes before calling the ctor
//    (push 0x1A500 at 0x0022F511), so sizeof is 0x1A500.
//
// The base is the 14-slot SubsystemInterface of subsystem_bfme2, the same
// header the canonical ScriptActions (ScriptActionsBFME2.h) derives from: its
// slots 1, 9 and 10 are exactly the ones ScriptEngine overrides.
//
// Members: every ScriptEngine row of reverse/functions.csv, with the access,
// constness and parameter types its decorated name states (I = protected,
// Q = public, U = public virtual), plus the members views call that have no
// row yet (marked "unrowed"). Addresses are target RVAs.
//
// Data: only the profiling tail is named (ScriptEngine_init.cpp reads it);
// +0x10..+0x1A4E0 stays opaque until the member types (counter/flag maps,
// action/condition template arrays, per-player lists) have shared headers.
// Units whose private view names other fields stay queued in
// reverse/header_queue.tsv.
#ifndef CANONICAL_SCRIPTENGINE_H
#define CANONICAL_SCRIPTENGINE_H

// subsystem_interface.h spells loadIniFilesFromLegend's return Bool; the
// canonical ScriptActions header declares the same typedef before it.
typedef bool Bool;
#include "../../../../reference/shims/subsystem_bfme2/subsystem_interface.h"
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class ActionTemplate;
class AsciiString;
class AssetList;
struct AssetLoadMode;
class AttackPriorityInfo;
struct BfmeStringRecord00204A30;
class Condition;
class ConditionTemplate;
struct Coord3D;
class Object;
class ObjectTypes;
class Parameter;
class Player;
class PolygonTrigger;
struct Rva003412E0Node;
class Rva003558C0Arr;
class Rva00355950Arr;
class Script;
class ScriptAction;
struct ScriptCounter;
class SequentialScript;
class Team;
class TeamPrototype;
class Xfer;
enum ObjectID;
enum ScienceType;

class ScriptEngine : public SubsystemInterface, public Snapshot
{
	friend class ScriptActions;
	friend class ScriptConditions;

public:
	typedef std::vector<SequentialScript *> VecSequentialScriptPtr;
	typedef VecSequentialScriptPtr::iterator VecSequentialScriptPtrIt;

	ScriptEngine();										// 0x00208343
	virtual ~ScriptEngine();							// 0x0020A2B0 (slot 0: ??_G 0x0020C0C7)

	virtual void init();								// 0x00205AFD, slot 1
	virtual void reset();								// 0x00209ABE, slot 9
	virtual void update();								// 0x0020D065, slot 10

	// Snapshot slots, spelled the way the unit selected Snapshot.h's.
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void LoadPostProcess();
#else
	virtual void loadPostProcess();
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName();
#else
	virtual const char *GetSnapshotName() const;
#endif
#else
	virtual void crc(Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void DoXfer(Xfer *xfer);					// 0x0020A859, Snapshot slot 3
#else
	virtual void xfer(Xfer *xfer);
#endif

	const ActionTemplate *getActionTemplate(int type);	// 0x00203926
	const ConditionTemplate *getConditionTemplate(int type);	// 0x00203941
	void rva00203BE9();									// 0x00203BE9
	bool rva00203F0E(void *);							// 0x00203F0E
	void rva00203FA8(int);								// 0x00203FA8
	void setSequentialTimer(Object *obj, int frameCount);	// 0x00203FCF
	void setSequentialTimer(Team *team, int frameCount);	// 0x00204002
	void rva002047CF();									// 0x002047CF
	void _bfme_updateClientDebugFrame();				// 0x00204806
	void initTemplateNameKeys();						// 0x00204D87
	void rva00205140(SequentialScript *);				// 0x00205140
	void rva0020517D(Object *);							// 0x0020517D
	void rva002051B7(Object *);							// 0x002051B7
	void AppendDebugMessage(const AsciiString &strToAdd, bool mustAddToFront);	// 0x00205263
	void rva00205358(AssetList *, AssetLoadMode *);		// 0x00205358
	Player *getCurrentPlayer();							// 0x00205C93
	AsciiString rva00205CE7(AsciiString);				// 0x00205CE7
	AttackPriorityInfo *findAttackInfo(const AsciiString &name, bool addIfNotFound);	// 0x00205D5D
	const AttackPriorityInfo *getAttackInfo(const AsciiString &name);	// 0x00205DDD
	void setPriorityDefault(ScriptAction *pAction);		// 0x002061D7
	int getObjectCount(int playerIndex, const AsciiString &objectTypeName) const;	// 0x00206255
	void checkConditionsForTeamNames(Script *pScript, const AsciiString &teamName);	// 0x002062A8
	void rva002064CB(Team *);							// 0x002064CB
	void rva002064D0();									// 0x002064D0
	void appendSequentialScript(const SequentialScript *scriptToSequence);	// 0x00207557
	void newMap();										// 0x00207C02
	void setObjectCount(int playerIndex, const AsciiString &objectTypeName, int newCount);	// 0x00207DF4
	const char *name() const;							// 0x002086B7
	void *rva002086C5(AsciiString);						// 0x002086C5
	void *rva0020881A(AsciiString);						// 0x0020881A
	void rva00208968(const AsciiString &, Object *);	// 0x00208968
	void rva00208A09(const AsciiString &, AsciiString);	// 0x00208A09
	void rva00208B2C(const AsciiString &, Team *);		// 0x00208B2C
	void rva00208BCD(const AsciiString &, AsciiString);	// 0x00208BCD
	void *rva00208CF0(AsciiString);						// 0x00208CF0
	void *rva00208DB8(AsciiString);						// 0x00208DB8
	void *rva00208E99(AsciiString);						// 0x00208E99
	bool evaluateFlag(Condition *pCondition);			// 0x00209382
	bool evaluateTimer(Condition *pCondition);			// 0x00209486
	bool evaluateConditions(Script *pScript, Team *thisTeam, Player *player);	// 0x00209748
	void rva00209811(const AsciiString &, unsigned char);	// 0x00209811
	void executeScript(Script *pScript, const AsciiString &scope);	// 0x00209E15
	void executeSequentialScript(Script *pScript, const AsciiString &scope);	// 0x0020A073
	bool rva0020A1D0(const AsciiString &, Script *, Team *, Player *);	// 0x0020A1D0
	void rva0020A586(void *, void *);					// 0x0020A586
	void addObjectToCache(Object *pNewObject, const AsciiString &name);	// 0x0020A5FF
	void walkNamed(Rva00355950Arr *list, Rva003412E0Node *node, bool flag);	// 0x0020A775
	void rva0020A7C9();									// 0x0020A7C9
	void walkChild(Rva003558C0Arr *list, Rva003412E0Node *node);	// 0x0020C0E3
	void rva0020C140(const AsciiString &, const AsciiString &, Team *);	// 0x0020C140
	void callSubroutine(ScriptAction *pAction);			// 0x0020C3BB
	void evaluateAndProgressAllSequentialScripts();		// 0x0020C83F
	void rva0020CDA2();									// 0x0020CDA2
	void rva0020CE13();									// 0x0020CE13
	Player *getSkirmishEnemyPlayer();					// 0x00356F6E
	void rva00356FAF(int);								// 0x00356FAF
	TeamPrototype *rva003570D1(AsciiString);			// 0x003570D1
	bool rva003571B8(int, const AsciiString &, bool, int);	// 0x003571B8
	bool rva0035721A(int, const AsciiString &, bool, int);	// 0x0035721A
	bool rva0035727C(int, const AsciiString &, bool, int);	// 0x0035727C
	bool rva003572DE(int, const AsciiString &, bool, int);	// 0x003572DE
	void rva00357340(void *, Coord3D *);				// 0x00357340
	bool didUnitExist(const AsciiString &unitName);		// 0x0035743F
	int rva00357475(const AsciiString &name, bool *matchedSpecialName = 0);	// 0x00357475
	ObjectTypes *getObjectTypes(const AsciiString &objectTypeList);	// 0x00357651
	PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);	// 0x0035768D
	void doNamedMapReveal(const AsciiString &revealName);	// 0x003577DA
	void undoNamedMapReveal(const AsciiString &revealName);	// 0x0035789D
	void rva00357960(const AsciiString &, Object *);	// 0x00357960
	void rva00357A03(int, ScienceType);					// 0x00357A03
	bool rva00357A36(const AsciiString &, bool);		// 0x00357A36
	bool rva00357A97(const AsciiString &, bool);		// 0x00357A97
	bool rva00357AF8(void *);							// 0x00357AF8
	bool rva00357B3D(int, ObjectID, bool);				// 0x00357B3D
	int rva00357B82(Parameter *);						// 0x00357B82
	void rva00357C1F(void *, void *);					// 0x00357C1F
	void rva00357D52(const AsciiString &);				// 0x00357D52
	void rva00357D86(const AsciiString &);				// 0x00357D86
	void rva00357DAC(const AsciiString &);				// 0x00357DAC
	void rva00357DD2(const AsciiString &);				// 0x00357DD2
	void rva00357E7B(int, const AsciiString &, int);	// 0x00357E7B
	void rva00357EAD(int, const AsciiString &, int);	// 0x00357EAD
	void rva00357EDF(int, const AsciiString &, int);	// 0x00357EDF
	void rva00357F11(int, const AsciiString &, int);	// 0x00357F11
	void notifyOfAcquiredScience(int playerIndex, ScienceType science);	// 0x00357F43
	bool rva00357F5E(const AsciiString &, bool);		// 0x00357F5E
	bool rva00358076(const AsciiString &, bool);		// 0x00358076
	void rva0035818E(const AsciiString &, Coord3D *);	// 0x0035818E
	void doObjectTypeListMaintenance(const AsciiString &objectList, const AsciiString &objectType, bool addObject);	// 0x00358286
	Team *getTeamNamed(AsciiString teamName, bool exact = false);	// 0x003584E9
	BfmeStringRecord00204A30 *createNamedMapReveal(const AsciiString &, const AsciiString &, float, const AsciiString &, int);	// 0x00358853
	Object *getUnitNamed(Parameter *pUnitParm);			// 0x003588E7
	Object *getUnitNamed(const AsciiString &unitName);	// unrowed; 27 views call it
	void initConditionTemplates();						// 0x003CF6B7
	void initActionTemplates();							// 0x003D46DB

	// Unrowed members single views call (no ledger row states their ABI yet).
	unsigned short unidentified_0034DB40(Parameter *playerParm);	// body 0x0034DB40
	unsigned short unidentified_0034DB40(const AsciiString &name);	// ILT thunk 0x000230B5
	Script *rva00357130(const AsciiString &scriptName, AsciiString *objectName);
	Script *rva003573C4(const AsciiString &owner, const AsciiString &name, AsciiString *outName);
	void rva0020D451(AsciiString &scope, void *action, Script *script, const AsciiString &scriptName, int flags);
	AsciiString getStats(float *curTimePtr, float *script1Time, float *script2Time);
	void applyNamed(void *obj, void *slot);
	bool isFrozen();

protected:
	void updateFades();									// 0x002036CC
	void setFade(ScriptAction *pAction);				// 0x00203777
	void setSway(ScriptAction *pAction);				// 0x0020385F
	void particleEditorUpdate();						// 0x00204032
	void removeObjectTypes(ObjectTypes *typesToRemove);	// 0x002046E4
	VecSequentialScriptPtrIt cleanupSequentialScript(VecSequentialScriptPtrIt it, bool cleanDanglers, bool removeEntry);	// 0x00204733
	void enableScript(ScriptAction *pAction);			// 0x00204FBB
	void disableScript(ScriptAction *pAction);			// 0x0020507F
	void setPriorityThing(ScriptAction *pAction);		// 0x00205EEC
	void setPriorityKind(ScriptAction *pAction);		// 0x0020611D
	ScriptCounter *bfmeCounter(AsciiString name);		// 0x0020874B
	bool *bfmeFlagForWrite(AsciiString name);			// 0x002088A0
	bool evaluateCounter(Condition *pCondition);		// 0x00208F61
	void setCounterToThreat(ScriptAction *pAction, bool);	// 0x00209003
	void setCounter(ScriptAction *pAction, int, bool, bool);	// 0x00209144
	void addCounter(ScriptAction *pAction);				// 0x002092F8
	void subCounter(ScriptAction *pAction);				// 0x0020933D
	void setFlag(ScriptAction *pAction, bool);			// 0x00209405
	void setTimer(ScriptAction *pAction, bool millisecondTimer, bool random);	// 0x002094CB
	void pauseTimer(ScriptAction *pAction);				// 0x002095CA
	void restartTimer(ScriptAction *pAction);			// 0x002095FF
	void adjustTimer(ScriptAction *pAction, bool millisecondTimer, bool add);	// 0x00209639
	bool evaluateCondition(Condition *pCondition);		// 0x002096E2
	void executeActions(ScriptAction *pActionHead, void *, void *);	// 0x0020C5C7

private:
	unsigned char m_opaque10[0x1A4E0 - 0x10];			// +0x10, see the header comment
	double m_numFrames;									// +0x1A4E0
	double m_totalUpdateTime;							// +0x1A4E8
	double m_maxUpdateTime;								// +0x1A4F0
};													// sizeof 0x1A500 (8-byte aligned)

extern ScriptEngine *TheScriptEngine;					// 0x009FE16C

#endif // CANONICAL_SCRIPTENGINE_H
