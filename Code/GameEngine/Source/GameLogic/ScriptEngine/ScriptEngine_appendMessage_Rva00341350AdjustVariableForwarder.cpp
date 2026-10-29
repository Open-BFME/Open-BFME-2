// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine
// platformsdk
//
// ScriptEngine.cpp's script-debugger helper _adjustVariable (0x002054FF), its
// forwarder (0x00206559) and its one in-TU caller ScriptEngine::update
// (0x0020D065, 1004B).
//
// ?Rva00341350AdjustVariableForwarder@@YGXABVAsciiString@@HD@Z
// retail 0x00206559, 32 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_appendMessage.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text).
// class-gate: allow AsciiString the donor's own view; the placed body is byte-exact under it
// stlport
//
// _adjustVariable takes `str` live in EDI, saves only ESI and returns
// without popping arguments: MSVC 7.1's private convention for a static
// helper, which it gets only beside its callers.  That is why it stays
// `static` here with update, which calls it from the debug-window block.
//
// ScriptEngine::update, retail 0x0020D065 (1004B).
// Identity (target): vtable slot of ScriptEngine's update (UAEXXZ), and the
// WorldBuilder twin 0xB34480 carries the name with the same callee order:
// GameLogic 0x001DCD1C and BitFlags<7,LivingWorldTurnPhase>::test on the
// LivingWorldLogic turn phase, createNamedCache-position 0x0020A7C9,
// particleEditorUpdate 0x00204032, closeWindows (ScriptActions slot +0x3C),
// the end-game message 0x00203BE9, updateFades 0x002036CC, the
// ScriptActions/ScriptConditions update slot +0x28, getNthPlayer,
// keyToName, getSideInfo, walkNamed/walkChild, updateTeamStates,
// list<int>::clear, evaluateAndProgressAllSequentialScripts, isTimeFast and
// _adjustVariable.
// Donor: Zero Hour ScriptEngine.cpp:5503 update (first-update, close-window
// and end-game timers, fades, countdown decrement, side loop, team states,
// UI interactions, sequential scripts, st_CurrentFrame, debug variables).
// BFME 2 adds the turn-phase gate, the scope latch on m_currentScope per
// side, the slow-script timing log and the "scope/name" debug keys; its
// counters and flags are maps keyed by (scope, name).

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}
#include <map>
#include <vector>
#include <stdio.h>
#include <windows.h>

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

typedef int Int;
typedef bool Bool;

// The shared empty string retail substitutes for a null buffer.

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"


#include "../../Common/GameLogicObjectLookupView.h"

// The three-pointer vector living at GlobalData+0x10F4 in BFME 2 (+0x11E0 in
// the BFME 1 donor; both retail readers here, 0x002053FA and 0x002054FF, load
// [TheWritableGlobalData+0x10F4]/[+0x10F8]).  Only begin/end are witnessed
// here, so the members keep offset-derived names.
class GlobalData10F4StringVec
{
public:
	AsciiString *begin() const { return m_start; }
	AsciiString *end() const { return m_finish; }

private:
	AsciiString *m_start;					// +0x00
	AsciiString *m_finish;					// +0x04
	AsciiString *m_endOfStorage;				// +0x08
};

class GlobalData
{
public:
	unsigned char m_unknown00[0x10f4];
	GlobalData10F4StringVec m_stringVec10F4;		// +0x10F4
};

// ScriptEngine::update (0x0020D065).
enum NameKeyType;

// WorldBuilder's twin tests the turn phase through
// BitFlags<7,LivingWorldTurnPhase>::test (BitFlags.h:383): an unchecked word
// and mask test on an unsigned index.
enum LivingWorldTurnPhase;

template <unsigned int NUMBITS, class T> class BitFlags
{
public:
	Bool test(T bit) const
	{
		unsigned int i = bit;
		return (m_bits[i >> 5] & (1 << (i & 31))) != 0;
	}

private:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<7, LivingWorldTurnPhase> LivingWorldTurnPhaseFlags;

class LivingWorldLogic
{
public:
	LivingWorldTurnPhase getTurnPhase() const { return m_turnPhase; }
	Int getFrameFC() const { return m_frameFC; }

private:
	unsigned char m_unknown00[0xf4];
	LivingWorldTurnPhase m_turnPhase;			// +0xF4 (WB member name)
	Int m_unknownF8;
	Int m_frameFC;						// +0xFC
};

class ScriptActions
{
public:
	virtual void v00(); virtual void v01(); virtual void v02();
	virtual void v03(); virtual void v04(); virtual void v05();
	virtual void v06(); virtual void v07(); virtual void v08();
	virtual void v09();
	virtual void update();					// +0x28
	virtual void v11(); virtual void v12(); virtual void v13();
	virtual void v14();
	virtual void closeWindows(Bool suppressDialogs);	// +0x3C
};

#include "../../../Include/GameLogic/ScriptConditions.h"

class Player
{
public:
	NameKeyType getPlayerNameKey() const { return m_playerNameKey; }

private:
	unsigned char m_unknown00[0x50];
	NameKeyType m_playerNameKey;				// +0x50
};

class PlayerList
{
public:
	Player *getNthPlayer(Int i);				// 0x002A7A29
	void updateTeamStates();				// 0x002A7B1C
};

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);		// 0x00148C95
};

// The script tree walkers keep their address-derived parameter types
// (ScriptEngine_rva0020A7C9.cpp, ScriptEngineArrWalk_Rva0020C0E3.cpp).
struct Rva003412E0Node;
class Rva00355950Arr;
class Rva003558C0Arr;

class ScriptList
{
public:
	Rva003412E0Node *getScriptGroup() { return m_firstGroup; }
	Rva003412E0Node *getScript() { return m_firstScript; }

private:
	void *m_vtbl;
	Rva003412E0Node *m_firstGroup;				// +0x04
	Rva003412E0Node *m_firstScript;				// +0x08
};

// BFME 2 keeps each side's script list by value at +0x08
// (SidesInfoSetScriptList.cpp).
class SidesInfo
{
public:
	ScriptList *getScriptList() { return &m_scriptList; }

private:
	unsigned char m_unknown00[0x8];
	ScriptList m_scriptList;				// +0x08
};

class SidesList
{
public:
	__declspec(dllimport) __forceinline Int getNumSides() { return m_numSides; }
	SidesInfo *getSideInfo(Int ndx);			// 0x002035BA

private:
	unsigned char m_unknown00[0x3c];
	Int m_numSides;						// +0x3C
};

// The scope latch on m_currentScope: restores the saved string when it goes
// out of scope (Rva002048A2Ctor.cpp).
class Rva002048A2
{
public:
	Rva002048A2(AsciiString *dest, const AsciiString &src);	// 0x002048A2
	virtual ~Rva002048A2();					// 0x002048EC

private:
	AsciiString m_valueToRestore;
	AsciiString *m_whereToStore;
};

// The slow-script name list at 0x00DFE174; this TU only clears it, through
// the out-of-line erase at 0x0002CCFC (VectorAsciiStringErase.cpp).
namespace _STL
{
template <> class vector<AsciiString, allocator<AsciiString> >
{
public:
	typedef AsciiString *iterator;
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

// BFME 2 scopes Zero Hour's counter and flag arrays by (script scope, name)
// in two maps; update reads the counter value, its countdown flag and the
// seconds-display flag the debug window gets, and the flag value.
typedef _STL::pair<AsciiString, AsciiString> ScopedName;

struct ScriptCounter
{
	Int value;						// node +0x18
	Bool isCountdownTimer;					// node +0x1C
	Bool showSeconds;					// node +0x1D
};

typedef _STL::map<ScopedName, ScriptCounter> CounterMap;
typedef _STL::map<ScopedName, Bool> FlagMap;

enum TFade
{
	FADE_NONE
};

class Rva00203B47Host { public: Bool rva00203B47(); };
class ScriptEngine
{
public:
	virtual void update();
	/* the rowed Rva00203B47Host::rva00203B47 */ __declspec(dllimport) __forceinline Bool isTimeFast() { return ((Rva00203B47Host *)this)->rva00203B47(); }					// 0x00203B47
	void rva0020A7C9();					// 0x0020A7C9
	void rva00203BE9();					// 0x00203BE9, end game
	void walkNamed(Rva00355950Arr *list, Rva003412E0Node *node, bool flag);	// 0x0020A775
	void walkChild(Rva003558C0Arr *list, Rva003412E0Node *node);		// 0x0020C0E3
	void evaluateAndProgressAllSequentialScripts();	// 0x0020C83F

protected:
	void particleEditorUpdate();				// 0x00204032
	void updateFades();					// 0x002036CC

private:
	unsigned char m_unknown04[0x190a0 - 0x04];
	CounterMap m_counters;					// +0x190A0
	FlagMap m_flags;					// +0x190AC
	unsigned char m_unknown190B8[0x1a104 - 0x190b8];
	Int m_endGameTimer;					// +0x1A104
	Int m_closeWindowTimer;					// +0x1A108
	AsciiString m_currentScope;				// +0x1A10C
	unsigned char m_unknown1A110[0x1a12c - 0x1a110];
	Bool m_firstUpdate;					// +0x1A12C
	Player *m_currentPlayer;				// +0x1A130
	Int m_unknown1A134;					// +0x1A134
	TFade m_fade;						// +0x1A138
	unsigned char m_unknown1A13C[0x1a264 - 0x1a13c];
	_STL::list<int> m_uiInteractions;			// +0x1A264
	unsigned char m_unknown1A268[0x1a4d8 - 0x1a268];
	Bool m_bfme1A4D8;					// +0x1A4D8
};

// Zero Hour's st_DebugDLL is the global the data ledger defines at
// 0x00DFE158: update() keeps its read after the byte store at +0x1A4D8,
// which a file static whose address is never taken would let cl hoist.
extern int st_DebugDLL;
#define TheScriptDebugWindowDLL ((HMODULE)st_DebugDLL)
// File static as in the Zero Hour ScriptEngine.cpp.
static int st_CurrentFrame;					// 0x00DFE160
extern GlobalData *TheWritableGlobalData;			// 0x00DFE758
extern GameLogic *TheGameLogic;					// 0x00DFE78C
extern ScriptEngine *TheScriptEngine;				// 0x00DFE16C
extern LivingWorldLogic *TheLivingWorldLogic;			// 0x00DFEF10
extern PlayerList *ThePlayerList;				// 0x00DFEEE8
extern NameKeyGenerator *TheNameKeyGenerator;			// 0x00DF36A4
extern SidesList *TheSidesList;					// 0x00E01D58
extern ScriptActions *TheScriptActions;				// 0x00E02D98
extern ScriptConditions *TheScriptConditions;			// 0x00E02E04
extern unsigned int g_Va00E02D64;				// 0x00E02D64
extern unsigned int g_00DFE174;				// 0x00DFE174

// SetTheSidesList hand-off to the debug window (ScriptEngine_setSides.cpp).
void rva00203C21();

extern bool BFME2ScriptDebugLiteMode;					// 0x00E02D78

// ?_appendMessage@@YAXABVAsciiString@@_N1@Z
// Retail 0x002053FA, 261 bytes (the donor's ScriptEngine_appendMessage.cpp
// _appendMessage): the Zero Hour twin (ScriptEngine.cpp
// _appendMessage), reading the same debug-lite flag and the GlobalData string
// vector at +0x10F4.  BFME 2 takes the logged frame from the living-world
// logic (+0xFC) when GameLogic 0x001DCD1C says so, as two format calls that cl
// cross-jumps into one tail.  Ordinary cdecl.
void _appendMessage(const AsciiString &str, Bool isTrueMessage,
	Bool shouldPause)
{
	if (BFME2ScriptDebugLiteMode)
		return;
	if (!TheScriptDebugWindowDLL)
		return;

	for (AsciiString *name = TheWritableGlobalData->m_stringVec10F4.begin();
		 name != TheWritableGlobalData->m_stringVec10F4.end();
		 ++name)
	{
		if (((const StringBase<char> &)str).startsWith((const StringBase<char> &)*name))
			return;
	}

	{
		AsciiString msg;
		GameLogic *logic = TheGameLogic;
		if (!logic->rva001DCD1C())
			msg.format("%d ", logic->getFrame());
		else
			msg.format("%d ", TheLivingWorldLogic->getFrameFC());
		if (isTrueMessage)
			((StringBase<char> *)&msg)->concat("Run script - ");
		else
			((StringBase<char> *)&msg)->concat("Run script false -");
		msg.concat(str);

		HMODULE module = TheScriptDebugWindowDLL;
		if (!module)
			return;

		FARPROC proc;
		if (shouldPause)
			proc = GetProcAddress(module, "AppendMessageAndPause");
		else
			proc = GetProcAddress(module, "AppendMessage");
		if (!proc)
			return;

		((void(__cdecl *)(const char *))proc)(msg.str());
	}
}

// Retail 0x002054FF, 224 bytes (BFME 1: 0x0033EB70, 297 bytes): the Zero Hour
// twin at ScriptEngine.cpp:9389
// (same "AdjustVariableAndPause"/"AdjustVariable" GetProcAddress pair and
// "%d" formatting of the value).  BFME adds the same early-outs as
// _appendMessage plus a TheScriptEngine->isTimeFast() guard, and a trailing
// flag selecting "%d (%0.2f secs)" with the value divided by the logic frame
// rate.  Same private
// convention: str live in EDI and no argument pop.
// BFME 2 turns Zero Hour's LOGICFRAMES_PER_SECOND into this global int (5);
// retail divides by it in memory (fidiv) rather than by a folded constant.
extern int BfmeLogicFramesPerSecond;					// 0x00DBA4E4

static void _adjustVariable(const AsciiString &str, Int value,
	Bool shouldPause, Bool showSeconds)
{
	if (BFME2ScriptDebugLiteMode)
		return;
	if (TheScriptEngine->isTimeFast())
		return;
	if (!TheScriptDebugWindowDLL)
		return;

	for (AsciiString *name = TheWritableGlobalData->m_stringVec10F4.begin();
		 name != TheWritableGlobalData->m_stringVec10F4.end();
		 ++name)
	{
		if (((const StringBase<char> &)str).startsWith((const StringBase<char> &)*name))
			return;
	}

	char buff[32];
	if (showSeconds)
		sprintf(buff, "%d (%0.2f secs)", value, (float)value / BfmeLogicFramesPerSecond);
	else
		sprintf(buff, "%d ", value);

	HMODULE module = TheScriptDebugWindowDLL;
	if (!module)
		return;

	FARPROC proc;
	if (shouldPause)
		proc = GetProcAddress(module, "AdjustVariableAndPause");
	else
		proc = GetProcAddress(module, "AdjustVariable");
	if (!proc)
		return;

	((void(__cdecl *)(const char *, const char *))proc)(str.str(), buff);
}

// Address-derived wrapper for retail 0x00341350. It forwards the caller's
// string through _adjustVariable's private EDI convention.
void __stdcall Rva00341350AdjustVariableForwarder(const AsciiString &str,
	Int value, char shouldPause)
{
	_adjustVariable(str, value, shouldPause, false);
}
void ScriptEngine::update()
{
	if (TheGameLogic->rva001DCD1C()
		&& !((const LivingWorldTurnPhaseFlags *)&g_Va00E02D64)->test(
			TheLivingWorldLogic->getTurnPhase()))
		return;

	if (m_firstUpdate) {
		rva0020A7C9();
		particleEditorUpdate();
		m_firstUpdate = false;
	} else {
		particleEditorUpdate();
	}

	if (m_closeWindowTimer > 0) {
		m_closeWindowTimer--;
		if (m_closeWindowTimer < 1)
			TheScriptActions->closeWindows(false);
	}
	if (m_endGameTimer > 0) {
		m_endGameTimer--;
		if (m_endGameTimer < 1)
			rva00203BE9();
	}

	if (m_fade != FADE_NONE)
		updateFades();

	if (m_endGameTimer >= 0)
		return;

	if (TheScriptActions)
		TheScriptActions->update();
	if (TheScriptConditions)
		TheScriptConditions->update();

	Int i;
	for (CounterMap::iterator it = m_counters.begin(), end = m_counters.end(); it != end; ++it) {
		if (it->second.isCountdownTimer) {
			Int value = it->second.value;
			if (value >= 0)
				it->second.value = value - 1;
		}
	}

	_STL::vector<AsciiString> *slowScripts = (_STL::vector<AsciiString> *)&g_00DFE174;
	slowScripts->clear();

	unsigned long startTime = timeGetTime();

	for (i = 0; i < TheSidesList->getNumSides(); i++) {
		m_currentPlayer = ThePlayerList->getNthPlayer(i);
		Rva002048A2 scope(&m_currentScope,
			TheNameKeyGenerator->keyToName(m_currentPlayer->getPlayerNameKey()));
		// The side's by-value script list: retail adds 8 and tests the sum
		// (mov/add/je). The member-address spelling emits lea/test and frees
		// the register that retail spends on timeGetTime, keeping i in EDI.
		ScriptList *pSL = (ScriptList *)((char *)TheSidesList->getSideInfo(i) + 8);
		if (pSL) {
			walkNamed((Rva00355950Arr *)pSL, pSL->getScript(), true);
			walkChild((Rva003558C0Arr *)pSL, pSL->getScriptGroup());
		}
		m_currentPlayer = NULL;
	}

	unsigned long elapsed = timeGetTime() - startTime;
	if (elapsed > 10) {
		char buf[256];
		sprintf(buf, "slow script on logic frame %d = %d ms\n", TheGameLogic->getFrame(), elapsed);
		Int n = 1;
		for (AsciiString *asciiString = slowScripts->begin(); asciiString != slowScripts->end(); ++asciiString, ++n)
			sprintf(buf, "    %d %s\n", n, asciiString->str());
	}

	ThePlayerList->updateTeamStates();

	m_uiInteractions.clear();

	m_bfme1A4D8 = true;
	evaluateAndProgressAllSequentialScripts();
	st_CurrentFrame++;
	m_bfme1A4D8 = false;

	if (TheScriptDebugWindowDLL && !isTimeFast()) {
		rva00203C21();
		for (CounterMap::iterator cit = m_counters.begin(), cend = m_counters.end(); cit != cend; ++cit) {
			AsciiString name = cit->first.first;
			name += '/';
			name += cit->first.second;
			if (cit->second.showSeconds)
				_adjustVariable(name.str(), cit->second.value, false, true);
			else
				_adjustVariable(name.str(), cit->second.value, false, false);
		}
		for (FlagMap::iterator fit = m_flags.begin(), fend = m_flags.end(); fit != fend; ++fit) {
			AsciiString name = fit->first.first;
			name += '/';
			name += fit->first.second;
			_adjustVariable(name.str(), fit->second, false, false);
		}
	}
}
