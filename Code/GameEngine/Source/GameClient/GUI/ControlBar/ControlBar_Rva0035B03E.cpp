// cl: -DNDEBUG -DWIN32 -MD -D_STLP_USE_STATIC_LIB -EHsc -Ireference/open-bfme-1/inputs/vendor/stlport -Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc -Ireference/open-bfme-1/inputs/reference/shims/controlbarvtables -Ireference/open-bfme-1/inputs/reference/shims/controlbarlayout -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/ControlBar
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: ControlBar.cpp ///////////////////////////////////////////////////////////////////////////
// Author: Colin Day, March 2002
// Desc:   Context sensitive command interface
///////////////////////////////////////////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////

#define BFME_STLP_NODE_ALLOC
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Common/UnicodeString.h"

// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:
#define DEFINE_GUI_COMMMAND_NAMES
#define DEFINE_COMMAND_OPTION_NAMES
#define DEFINE_WEAPONSLOTTYPE_NAMES
#define DEFINE_RADIUSCURSOR_NAMES

#include "Common/ActionManager.h"
#include "Common/GameType.h"
#include "Common/MultiplayerSettings.h"
#include "Common/NameKeyGenerator.h"
#include "Common/OVERRIDE.h"
#include "Common/PlayerTemplate.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ProductionPrerequisite.h"
#include "Common/SpecialPower.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/Upgrade.h"
#include "Common/Recorder.h"

#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/Module/OCLUpdate.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Module/RebuildHoleBehavior.h"
#include "GameLogic/ScriptEngine.h"

#include "GameClient/AnimateWindowManager.h"
#include "GameClient/ControlBar.h"
#include "GameClient/ControlBarScheme.h"
#include "GameClient/Drawable.h"
#include "GameClient/Display.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GameText.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetProgressBar.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/InGameUI.h"
#include "GameClient/WindowVideoManager.h"
#include "GameClient/ControlBarResizer.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/HotKey.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameClient/GUICallbacks.h"

#include "GameNetwork/GameInfo.h"

// BFME's InGameUI vtable puts setGUICommand at slot 46; the ZH header lands it
// at 37, so the tail call comes out [eax+0x94] instead of [eax+0xb8]. Only the
// one slot is named; the rest stay anonymous because nothing here needs them.
class BFMERetailInGameUIVTable
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void setGUICommand(const void *cmd) = 0;
};

// The BFME object grew two context-parent slots and moved the selected-draw
// state one word past the Zero Hour layout.  Keep this view local to the
// reconstruction so the real ControlBar header remains untouched.
struct BfmeContextSwitchControlBarView
{
	char pad00[0x34];
	GameWindow *contextParent[10];
	Drawable *currentSelectedDrawable;
	ControlBarContext currContext;
	char pad64[0x9c];
	GameWindow *commandWindows[20];
	char pad150[0x1a0];
	void *contextOverlay;
};

struct BfmeContextSwitchSelectionState
{
	void *chat;
	Drawable *oldSelected;
};

class BfmeSourceCB
{
public:
	char m_bfmeHead[0x74];
	int m_bfmeValue;
};

class Gen_004AFA80
{
public:
	void bfmeTake(BfmeSourceCB *source);

private:
	int m_bfmeHead[7];
	int m_bfmeValue;
};

struct BfmeContextSwitchDrawableView
{
	char pad00[0xfc];
	BfmeSourceCB *object;
};

// Calls in the context arms are deliberately declaration-only.  This keeps
// each retail call boundary visible to the compiler instead of inlining an
// already-converted sibling body into this large dispatcher.
extern void j_0000d495(void);
extern void j_0000efe8(void);
extern void j_0001df4d(void);
extern void j_00034581(void);
class Rva0049E780Calls {
public:
    void commandSignature(Object *, Bool);
    void multiSignature(void);
    __forceinline void populateCommand(Object *object, Bool refresh) {
        typedef void (Rva0049E780Calls::*Method)(Object *, Bool);
        union { void (*raw)(void); Method member; } call;
        call.raw = j_0000d495;
        (this->*call.member)(object, refresh);
    }
    __forceinline void populateStructureInventory(Object *object, Bool refresh) {
        typedef void (Rva0049E780Calls::*Method)(Object *, Bool);
        union { void (*raw)(void); Method member; } call;
        call.raw = j_0001df4d;
        (this->*call.member)(object, refresh);
    }
    __forceinline void populateOCLTimer(Object *object) {
        typedef void (Rva0049E780Calls::*Method)(Object *);
        union { void (*raw)(void); Method member; } call;
        call.raw = j_00034581;
        (this->*call.member)(object);
    }
    __forceinline void populateMultiSelect(void) {
        typedef void (Rva0049E780Calls::*Method)(void);
        union { void (*raw)(void); Method member; } call;
        call.raw = j_0000efe8;
        (this->*call.member)();
    }
};

class BfmeContextSwitchBfmeTransitionMD
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
};

class BfmeContextSwitchInGameUI : public BFMERetailInGameUIVTable
{
public:
	virtual void slot47(void) = 0;
	virtual void slot48(void) = 0;
	virtual void slot49(void) = 0;
	virtual void slot50(void) = 0;
	virtual void slot51(void) = 0;
	virtual void slot52(void) = 0;
	virtual void slot53(void) = 0;
	virtual void slot54(void) = 0;
	virtual void slot55(void) = 0;
	virtual void slot56(void) = 0;
	virtual void slot57(void) = 0;
	virtual void slot58(void) = 0;
	virtual void slot59(void) = 0;
	virtual void slot60(void) = 0;
	virtual void slot61(void) = 0;
	virtual void slot62(void) = 0;
	virtual void slot63(void) = 0;
	virtual void slot64(void) = 0;
	virtual void slot65(void) = 0;
	virtual void slot66(void) = 0;
	virtual void slot67(void) = 0;
	virtual void slot68(void) = 0;
	virtual void slot69(void) = 0;
	virtual void slot70(void) = 0;
	virtual void setRadiusCursorNone(void) = 0;
};

class BfmeContextSwitchOverlaySink
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
};

class BfmeContextSwitchGameLogicView
{
public:
	char pad00[0x10c];
	Int mode;
};

class Rva0058C040
{
public:
	void invoke(void);
};

extern void j_00018f2f(void);
extern void j_0003367c(void);

class BfmeTransitionMD;
class Rva005127A0InGameChat;
class Glo012F4B98Type;
extern BfmeTransitionMD *g_bfmeTransitionMD;
extern Rva005127A0InGameChat *g_Rva005127A0InGameChat;
extern void *g_obj12F4C38;
class AptPalantir;
extern AptPalantir *TheAptPalantir;
// No recovered source name exists for this retail selection cache.
extern volatile Drawable *g_Rva012F340C;
#define BFME_CONTEXT_TRANSITION ((BfmeContextSwitchBfmeTransitionMD *)g_bfmeTransitionMD)
#define BFME_CONTEXT_INGAME_UI ((BfmeContextSwitchInGameUI *)TheInGameUI)
#define BFME_CONTEXT_IN_GAME_CHAT g_Rva005127A0InGameChat
#define BFME_CONTEXT_OBJECT_12F4C38 g_obj12F4C38
#define BFME_CONTEXT_GAME_LOGIC ((BfmeContextSwitchGameLogicView *)TheGameLogic)
#define BFME_CONTEXT_GLO_12F4B98 ((Rva0058C040 *)TheAptPalantir)
#define BFME_CONTEXT_SELECTION_CACHE g_Rva012F340C


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// PUBLIC /////////////////////////////////////////////////////////////////////////////////////////
ControlBar *TheControlBar = NULL;

void (Coord3D::*g_controlBarCoord3DSet)( const Coord3D * ) = &Coord3D::set;

const Image* ControlBar::m_rankVeteranIcon	= NULL;
const Image* ControlBar::m_rankEliteIcon		= NULL;
const Image* ControlBar::m_rankHeroicIcon		= NULL;

///////////////////////////////////////////////////////////////////////////////////////////////////
// CommandButton //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Retail loads TheScienceStore here, not TheControlBar, and calls
// ScienceStore::friend_lookupScience -- the seventeen bytes at 0x000B8F40 are
// mov ecx,[0x12ed7ac] ; push eax ; call 0x17503, and 0x00017503 is the
// incremental-link thunk for the matched friend_lookupScience body at
// 0x000E7240. Calling TheControlBar->showBuildTooltipLayout(window) reproduced
// those bytes only because a five-byte thunk row stood in for the callee, which
// is what targets/game/reverse/dir32_consistency_whitelist.txt recorded as a wrong name that
// still matched.
//
// The argument is passed straight through, so the cast is retail's shape rather
// than a conversion this code chose. The function's own name is still Zero
// Hour's guess and is very likely wrong too -- nothing in the image names it --
// but the global and the callee are now right.

/// mark the UI as dirty so the context of everything is re-evaluated
// ?markUIDirty@ControlBar@@QAEXXZ present-unmatched


// ?populatePurchaseScience@ControlBar@@IAEXPAVPlayer@@@Z
// Body in game/masm_dumps/_str3__populatePurchaseScience_ControlBar_IAEXPAVPlayer_Z_4A0B90.asm (exact 783B retail @ 0x004A0B90).
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// BFME's skill points are a Real at Player+0x25C, not an Int: every read floors
// them through the CRT and converts, which is what the float round trip
// (fld dword / floor / fstp dword / fistp) in retail is.  The two level bounds
// either side of the experience bar are plain Ints at +0x268 and +0x26C.
struct BfmePurchaseSciencePlayer
{
	Int getSkillPoints() const { return (Int)floorf( m_skillPoints ); }

	unsigned char m_unreconstructed_000[ 0x25c ];
	Real m_skillPoints;					///< retail this+0x25C
	unsigned char m_unreconstructed_260[ 0x268 - 0x260 ];
	Int m_skillPointsLevelUp;				///< retail this+0x268
	Int m_skillPointsLevelDown;				///< retail this+0x26C
};

//-------------------------------------------------------------------------------------------------
/** parse command definition */
//-------------------------------------------------------------------------------------------------
// ?parseCommand@CommandButton@@SAXPAVINI@@PAX1PBX@Z
// Body in game/masm_dumps/CommandButton_parseCommand.asm (exact 124B retail @ 0x49AB90).
// True body via unique TheGuiCommandNames table; queue 0x23E4F6 was INSIDE FUN_0063e420.
// BFME throws formatted "Command '%s' not found" + expanded name table vs ZH enum throw.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0CommandButton@@QAE@XZ present-unmatched

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1CommandButton@@MAE@XZ present-unmatched

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
Bool CommandButton::isValidObjectTarget(const Object* sourceObj, const Object* targetObj) const
{
	if (!sourceObj || !targetObj)
		return false;

	Relationship r = sourceObj->getRelationship(targetObj);

	return isValidRelationshipTarget(r);
}

//-------------------------------------------------------------------------------------------------
class BfmeCommandButtonProductionEntry
{
public:
	char m_unmodelled00[4];
	Int m_type;
	char m_unmodelled08[4];
	const UpgradeTemplate *m_upgrade;
};

class BfmeCommandButtonProductionUpdate
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual BfmeCommandButtonProductionEntry *firstProduction(void) = 0;
	virtual BfmeCommandButtonProductionEntry *nextProduction(
		const BfmeCommandButtonProductionEntry *) = 0;
};

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
struct BFMEDrawableObjectView
{
	char m_pad000[0xfc];
	Object *m_object;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// CommandSet /////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
/** These are the fields you can define in a command set, they correspond to physical
	* buttons in the GUI */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// bleah. shouldn't be const, but is. sue me. (srj)
// ?copyImagesFrom@CommandButton@@QBEXPBV1@_N@Z present-unmatched

//-------------------------------------------------------------------------------------------------
// bleah. shouldn't be const, but is. sue me. (Kris) -snork!
// ?copyButtonTextFrom@CommandButton@@QBEXPBV1@_N1@Z present-unmatched

//-------------------------------------------------------------------------------------------------
/** Parse a single command button definition */
//-------------------------------------------------------------------------------------------------
// ?parseCommandButton@CommandSet@@CAXPAVINI@@PAX1PBX@Z present-unmatched

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameClient/GUI/ControlBar/CommandSetConstructor.cpp
// ??0CommandSet@@QAE@ABVAsciiString@@@Z present-unmatched

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?friend_addToList@CommandSet@@QAEXPAPAV1@@Z present-unmatched

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??1CommandSet@@MAE@XZ present-unmatched

///////////////////////////////////////////////////////////////////////////////////////////////////
// ControlBar /////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ??0ControlBar@@QAE@XZ
// Body in ControlBar_ctor.asm (exact 819B retail).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/Common/ControlBarDestructorThunk.cpp
// ??1ControlBar@@UAE@XZ present-unmatched
void ControlBarPopupDescriptionUpdateFunc( WindowLayout *layout, void *param );

//-------------------------------------------------------------------------------------------------
/** Initialzie the control bar, this is our interface to the context sinsitive GUI */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarInitThunk.cpp
// ?init@ControlBar@@UAEXXZ present-unmatched

//-------------------------------------------------------------------------------------------------
/** Reset the context sensitive control bar GUI */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/Common/ControlBar_resetMethodThunk.cpp
// ?reset@ControlBar@@UAEXXZ present-unmatched

//-------------------------------------------------------------------------------------------------
/** Update phase, we can track if our selected object is destroyed, update button
	* percentages, status, enabled status etc */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_setControlBarSchemeByPlayerTemplate_Thunk.cpp
// ?update@ControlBar@@ present-unmatched

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?onDrawableDeselected@ControlBar@@QAEXPAVDrawable@@@Z present-unmatched

//-------------------------------------------------------------------------------------------------

// Matched via game/masm_dumps/ControlBar_getStarImage.asm @ 0x0049CC00


//-------------------------------------------------------------------------------------------------
// Matched via game/masm_dumps/ControlBar_onPlayerRankChanged.asm @ 0x0049DC90
// byte-exact reconstruction: game/GameEngine/Source/Common/ControlBar_onPlayerRankChanged_Thunk.cpp
// ?onPlayerRankChanged@ControlBar@@QAEXPBVPlayer@@@Z present-unmatched
// onPlayerRankChanged cannot come home: it stops two bytes short on the
// EH-temporary transposition, a known wall this
// toolchain does not cross. Recorded so nobody spends the cycle again.
//
// The merged form is otherwise EXACT. Every byte matches except one pair:
// retail writes the unwind cookie before loading ecx with the temporary's
// address (89 64 24 10 / 8b cc) and this toolchain emits them the other way
// round. That is the same residue as the 0x002F4080 and 0x002F74E0 families in
// targets/game/reverse/re_attempts.log, where /EHs, /GX, /MT, /G7, /O1, /Ox and /Gy were all
// tried and none moved it.
//
// Two levers DID work on the way there and are worth reusing:
//   - binding the local player's point total to a local on its own line gets
//     retail's compare form (member against register, not register against
//     memory);
//   - routing the local-player fetch through an in-class accessor on the view
//     fixes the register chain, so the walk reuses eax the way retail does
//     instead of switching to ecx one load earlier. That is a register
//     allocation difference that a source shape DID reach, which is worth
//     knowing, since register allocation is not source-controllable.
//
// The layout and behaviour are settled: PlayerList's local player at +0x0c, the
// player's science points at +0x264, ControlBar's UI-dirty flag at +0x24, the
// star flash at +0x2c8 and the last flashed value at +0x2cc. Two real
// differences from the reference: TransitionHandler::setGroup takes a SECOND
// argument, always zero, and the input test reads TWO bytes -- enabled at
// InGameUI+0x0d AND allowed at +0x0e -- so the arrow transition fires only when
// input is both enabled and allowed. The setGroup ILT at 0x00045C28 is pinned in
// targets/game/reverse/symbols.csv and was byte-proved by this attempt's rel32.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?onPlayerSciencePurchasePointsChanged@ControlBar@@QAEXPBVPlayer@@@Z present-unmatched

//-------------------------------------------------------------------------------------------------
/** Given the drawables that we have selected into our context sensitive UI, evaluate 
	* and perform all UI manipulations to make the GUI show to the user what we want them
	* to see */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarEvaluateContextUIThunk.cpp
// ?evaluateContextUI@ControlBar@@ present-unmatched

//-------------------------------------------------------------------------------------------------
/** Find a command button of the given name if present */
//-------------------------------------------------------------------------------------------------
// ?findNonConstCommandButton@ControlBar@@IAEPAVCommandButton@@ABVAsciiString@@@Z
// Retail does not call AsciiString::operator== here -- it inlines the whole
// comparison, reading each string's 16-bit length at header+4 and its payload at
// header+8, then a repe cmpsb over the shorter of the two and a length
// subtraction for the tie.  That is BFME's eight-byte string header, so the
// comparison is spelled against a TU-local view of it rather than against this
// tree's AsciiString, which puts the payload at header+4 and compares by strcmp.
struct BfmeControlBarStringHeader
{
	int refCount;
	unsigned short length;					///< retail header+0x04
	unsigned short capacity;
	char data[ 1 ];						///< retail header+0x08
};

struct BfmeControlBarStringView
{
	BfmeControlBarStringHeader *m_data;

	int compare( const BfmeControlBarStringView &string ) const
	{
		const BfmeControlBarStringView *self = this;
		const BfmeControlBarStringView *that = &string;
		int thatLen = that->m_data ? that->m_data->length : 0;
		const char *thatData = that->m_data ? &that->m_data->data[ 0 ] : (const char *)"";
		int thisLen = self->m_data ? self->m_data->length : 0;
		const char *thisData = self->m_data ? &self->m_data->data[ 0 ] : (const char *)"";
		int n = thisLen < thatLen ? thisLen : thatLen;
		int c = memcmp( thisData, thatData, n );
		if( c != 0 )
			return c;
		return thisLen - thatLen;
	}
};

// Overridable::getFinalOverride is inline AND recursive in the vendored header,
// so MSVC unrolls one level of the chain walk into this body where retail just
// calls it through ILT 0x000022BB.  Declared-not-defined on a view, the call
// survives -- the same lever the Team.cpp folds needed.
class BfmeControlBarOverridable
{
public:
	const BfmeControlBarOverridable *getFinalOverride() const;	///< ILT 0x000022BB
};

// One level of the override walk is inline: only a button that actually has an
// override at +0x04 reaches the out-of-line chain walk.
struct BfmeCommandButtonNode
{
	unsigned char m_unmodelled_000[ 0x04 ];
	const BfmeControlBarOverridable *m_override;		///< retail this+0x04
	unsigned char m_unmodelled_008[ 0x0c - 0x08 ];
	BfmeControlBarStringView m_name;			///< retail this+0x0c
	unsigned char m_unmodelled_010[ 0x14 - 0x10 ];
	const BfmeCommandButtonNode *m_next;			///< retail this+0x14

	const BfmeControlBarStringView &getName() const { return m_name; }
	const BfmeCommandButtonNode *getNext() const { return m_next; }
	const BfmeCommandButtonNode *getFinalOverride() const
	{
		if( m_override )
			return (const BfmeCommandButtonNode *)m_override->getFinalOverride();
		return this;
	}
};

struct BfmeControlBarButtonList
{
	unsigned char m_unmodelled_000[ 0x28 ];
	const BfmeCommandButtonNode *m_commandButtons;		///< retail this+0x28
};

struct Rva004A5E30ButtonView
{
	unsigned char m_unmodelled_000[ 0x10 ];
	int m_command;
	void *m_upgradeTemplate;
	UnsignedInt m_options;
	unsigned char m_unmodelled_01c[ 0x34 - 0x1c ];
	SpecialPowerTemplate *m_specialPower;
	unsigned char m_unmodelled_038[ 0x68 - 0x38 ];
	AsciiString m_unmodelled_068;
	unsigned char m_unmodelled_06c[ 0x84 - 0x6c ];
	std::vector<int> m_science;
	unsigned char m_unmodelled_090[ 0xa0 - 0x90 ];
	int m_unmodelled_0a0;
	unsigned char m_unmodelled_0a4[ 0x14d - 0xa4 ];
	unsigned char m_unknown_14d;
	unsigned char m_unmodelled_14e[ 4 ];
	unsigned char m_unknown_152;
	unsigned char m_unknown_153;

	int getCommandType() const { return m_command; }
	UnsignedInt getOptions() const { return m_options; }
	SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
	const std::vector<int> &getScienceVec() const { return m_science; }
	Rva004A5E30ButtonView *getNext() const { return (Rva004A5E30ButtonView *)m_upgradeTemplate; }
};

class Rva0049BA80
{
public:
	void call( Object *object, Bool refresh ) const;
};

class Gen_0049C4B0
{
public:
	void bfmeCopyFrom( Gen_0049C4B0 *source, bool notify );
};

class Gen_004B1720
{
public:
	void bfmeClear();
};

class BFMERetailCommandButton
{
public:
	void setButtonImage( const Image *image );
};

class Rva004A0340
{
public:
	const CommandSet *call( const AsciiString &name );
};

class Rva0049C590
{
public:
	const CommandButton *call( int index ) const;
};

class Rva0049EDE0
{
public:
	void call( GameWindow *window, const CommandButton *button );
};

class Rva0049DF00
{
public:
	void call( const Coord3D *location );
};
// field_0100[] holds GameWindow*. The 0x478390 body the call sites below used
// to reach through a cast stand-in (class Rva00478390) is retail's
// GameWindow::winHide, declared by the real GameClient/GameWindow.h included
// above as `Int winHide( Bool hide )`; they now name it directly.


struct Rva004A5E30ControlBarView
{
	unsigned char m_unmodelled_000[ 0x28 ];
	Rva004A5E30ButtonView *field_0028;
	unsigned char m_unmodelled_02c[ 0xd4 ];
	GameWindow *field_0100[ 20 ];
	unsigned char m_unmodelled_150[ 0x50 ];
	GameWindow *field_0150[ 20 ];
	unsigned char m_unmodelled_1f0[ 0x100 ];
	void *field_02f0;
};

struct Rva004A5E30OverrideView
{
	unsigned char m_unmodelled_000[ 0x2c ];
	AsciiString field_002c;
};

class Rva001CAF20
{
public:
	Rva004A5E30OverrideView *call();
};

class Rva000FA800
{
public:
	const Image *call( int index );
};

struct Rva004A5E30PlayerView
{
	unsigned char m_unmodelled_000[ 0x684 ];
	Rva000FA800 field_0684;
};

class Rva0013E4D0
{
public:
	Bool take( class Rva0036CA00Str &text );
};

class Rva000DF810
{
public:
	unsigned char call( Object *object );
};

class BfmeVecVLH
{
public:
	const ThingTemplate *rva000F9670( int index );
};

class Rva0036CA00Str;

class Rva004A5E30ContainView
{
public:
	virtual OpenContain *asOpenContain();
	virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04();
	virtual void slot05(); virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17(); virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24();
	virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28();
	virtual void slot29(); virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35(); virtual void slot36();
	virtual void slot37(); virtual void slot38(); virtual void slot39(); virtual void slot40();
	virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual Bool slot45();
};

struct Rva004A5E30ObjectView
{
	unsigned char m_unmodelled_000[ 0x1fc ];
	Rva004A5E30ContainView *m_contain;
};

class BFMERetailExitVTable
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual const Coord3D *getRallyPoint() const;
};

class Rva005976B0
{
public:
	void update( void *value );
};

class BfmeRva004A5950ControlBarContextCommandView
{
public:
	void call();
};

class Rva004B19E0
{
public:
	void apply( void *windows );
};

class Rva004A4090 : public std::vector<GameWindow *>
{
public:
	void call( unsigned count );
};

#define field_0028 (((Rva004A5E30ControlBarView *)this)->field_0028)
#define field_0100 (((Rva004A5E30ControlBarView *)this)->field_0100)
#define field_0150 (((Rva004A5E30ControlBarView *)this)->field_0150)
#define field_02f0 ((Rva004B19E0 *)((Rva004A5E30ControlBarView *)this)->field_02f0)


#undef field_02f0
#undef field_0150
#undef field_0100
#undef field_0028

//-------------------------------------------------------------------------------------------------
/** Allocate a new command button, assign name, and tie to list */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarNewCommandSet.cpp
// ?newCommandButton@ControlBar@@IAEPAVCommandButton@@ABVAsciiString@@@Z present-unmatched
// The newCommandButton / newCommandSet / newCommandSetOverride family cannot come
// home: class shape. Retail allocates 472 bytes for a CommandButton and 100 for a
// CommandSet; the vendored declarations give 224 and 92, and the allocation size
// comes from the class, not from anything a .cpp can cast. A view class with the
// right size would have to bring its own pool operator new, which would break the
// ??2CommandButton / ??2CommandSet rows THIS file owns -- so the workaround costs
// more rows than it converts. The eight-byte half of the same drift is visible in
// findNonConstCommandSet above, where a BFME command set holds twenty command
// slots against Zero Hour's eighteen; there it is only a displacement and a view
// reaches it.

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?newCommandButtonOverride@ControlBar@@IAEPAVCommandButton@@PAV2@@Z present-unmatched

//-------------------------------------------------------------------------------------------------
/** Parse a command set */
//-------------------------------------------------------------------------------------------------
/*static*/ void ControlBar::parseCommandSetDefinition( INI *ini )
{
	AsciiString name;
	CommandSet *commandSet;

	// read the name
	const char* c = ini->getNextToken();
	name.set( c );	

	// find existing item if present
	commandSet = TheControlBar->findNonConstCommandSet( name );
	if( commandSet == NULL )
	{

		// allocate a new item
		commandSet = TheControlBar->newCommandSet( name );
		if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES) {
			commandSet->markAsOverride();
		}
	}  // end if
	else if( ini->getLoadType() != INI_LOAD_CREATE_OVERRIDES )
	{
		//Holy crap, this sucks to debug!!!
		//If you have two different command sets, the previous
		//code would simply allow you to define multiple command set
		//with the same name, and just nuke the old button with the new one.
		//So, I (KM) have added this assert to notify in case of two same-name
		//command set.
		DEBUG_CRASH(( "[LINE: %d in '%s'] Duplicate commandset %s found!", ini->getLineNum(), ini->getFilename().str(), name.str() ));
		throw INI_INVALID_DATA;

		//@todo SUPPORT OVERRIDES -- JM
	} else {
		commandSet = TheControlBar->newCommandSetOverride(commandSet);
	}

	// sanity
	DEBUG_ASSERTCRASH( commandSet, ("parseCommandSetDefinition: Unable to allocate set '%s'\n", name.str()) );

	// parse the ini definition
	ini->initFromINI( commandSet, commandSet->friend_getFieldParse() );

}  // end parseCommandSetDefinition

//-------------------------------------------------------------------------------------------------
/** Find existing command set by name */
//-------------------------------------------------------------------------------------------------
// A BFME command set holds twenty command slots where Zero Hour's holds
// eighteen, so its next pointer lands at +0x60 rather than +0x58 -- and the name
// is compared the same inlined way findNonConstCommandButton above needs.
struct BfmeCommandSetNode
{
	unsigned char m_unmodelled_000[ 0x0c ];
	BfmeControlBarStringView m_name;			///< retail this+0x0c
	unsigned char m_unmodelled_010[ 0x60 - 0x10 ];		///< twenty command slots at +0x10
	BfmeCommandSetNode *m_next;				///< retail this+0x60

	const BfmeControlBarStringView &getName() const { return m_name; }
	BfmeCommandSetNode *friend_getNext() { return m_next; }
};

struct BfmeControlBarSetList
{
	unsigned char m_unmodelled_000[ 0x2c ];
	BfmeCommandSetNode *m_commandSets;			///< retail this+0x2c
};

// ?findNonConstCommandSet@ControlBar@@AAEPAVCommandSet@@ABVAsciiString@@@Z
//-------------------------------------------------------------------------------------------------
/** find existing command button if present	*/
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** Find existing command set by name */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** Allocate a new command set, link to list, initialize to default, and return it */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarNewCommandSet.cpp
// ?newCommandSet@ControlBar@@IAEPAVCommandSet@@ABVAsciiString@@@Z present-unmatched

//-------------------------------------------------------------------------------------------------
/** Create an overridden command set. */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameClient/ControlBar_newCommandSetOverride.cpp
// ?newCommandSetOverride@ControlBar@@IAEPAVCommandSet@@PAV2@@Z present-unmatched

//-------------------------------------------------------------------------------------------------
/** Process a button click for the context sensitive GUI */
//-------------------------------------------------------------------------------------------------
// ?processContextSensitiveButtonClick@ControlBar@@QAE?AW4CBCommandStatus@@PAVGameWindow@@W4GadgetGameMessage@@@Z present-unmatched

//-------------------------------------------------------------------------------------------------
/** Process a button click for the context sensitive GUI */
//-------------------------------------------------------------------------------------------------
// ?processContextSensitiveButtonTransition@ControlBar@@QAE?AW4CBCommandStatus@@PAVGameWindow@@W4GadgetGameMessage@@@Z present-unmatched


//-------------------------------------------------------------------------------------------------
/** Switch the user interface to the new context specified and fill out any of the
	* art and/or buttons that we need to for the new context using data from the object
	* passed in */
//-------------------------------------------------------------------------------------------------
// ?switchToContext@ControlBar@@IAEXW4ControlBarContext@@PAVDrawable@@@Z
// Retail switchToContext starts at RVA 0x0049E780; old 0x0049E901 claim was interior.

// BFME adds a FIFTH border type Zero Hour does not have. Retail's jump table
// covers switch values 1 through 5 as an identity map, so the arms are in source
// order and the new one follows the reference's four.
//
// The colour members are NOT declared in the enum's order -- the arms read
// this+0x280, +0x288, +0x284, +0x28c and +0x290 in case order -- so the offsets
// are proven while the pairing of the reference's names to them rests on BFME
// having kept the enum order and appended to it. The fifth has no reference name
// at all, hence the _bfme_ one.
struct BfmeControlBarBorderColors
{
	unsigned char m_unreconstructed_00[ 0x280 ];
	Color m_commandButtonBorderBuildColor;			///< retail this+0x280
	Color m_commandButtonBorderActionColor;			///< retail this+0x284
	Color m_commandButtonBorderUpgradeColor;		///< retail this+0x288
	Color m_commandButtonBorderSystemColor;			///< retail this+0x28c
	Color m_bfmeCommandButtonBorderFifthColor;		///< retail this+0x290
};

enum { COMMAND_BUTTON_BORDER_BFME_FIFTH = 5 };

// ?setCommandBarBorder@ControlBar@@AAEXPAVGameWindow@@W4CommandButtonMappedBorderType@@@Z


//-------------------------------------------------------------------------------------------------
/** Set the command data into the control */
//-------------------------------------------------------------------------------------------------
// ?setControlCommand@ControlBar@@ present-unmatched

//-------------------------------------------------------------------------------------------------
// ?cacheButtonImage@CommandButton@@QAEXXZ present-unmatched

//-------------------------------------------------------------------------------------------------
/** post process step, after all commands and command sets are loaded */
//-------------------------------------------------------------------------------------------------
// ?postProcessCommands@ControlBar@@IAEXXZ present-unmatched

//-------------------------------------------------------------------------------------------------
/** set the command for the button identified by the window name
	* NOTE that parent may be NULL, it only helps to speed up the search for a particular
	* window ID */
//-------------------------------------------------------------------------------------------------
// ?setControlCommand@ControlBar@@ present-unmatched

//-------------------------------------------------------------------------------------------------
/** show/hide the portrait window image */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** show/hide the portrait image by object.  We like to use this method as opposed to the
	* plain image one above so that we can build more intelligence into what portrait to
	* show for an object given its current state or object type */
//-------------------------------------------------------------------------------------------------
// ?setPortraitByObject@ControlBar@@IAEXPAVObject@@@Z
// Body in ControlBar_setPortraitByObject.asm (exact 739B retail).

// ControlBar::populateBeacon, retail 0x004A3830, 416 bytes.  The callback is
// the BEACON arm of switchToContext: its three function-local name keys and
// the reference ControlBarBeacon.cpp body identify the method.  BFME keeps
// the local-owner test and three-window visibility order.
// BFME's Object exposes getDrawable at vtable+0x28 (slot 10): Object's retail
// ctor at 0x001D29A0 stores vtable 0x0109EE58, and the independently matched
// 0x001BE440 body reads the +0x80 m_drawable field.  This callback uses the
// same proven local virtual view used by other BFME Object call sites.
class BfmeBeaconObjectGetDrawable
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual Drawable *getDrawable(void) const = 0;
};

// The caption callsite targets the already-real 58-byte body at 0x00416BD0.
// Its canonical Drawable spelling is still present-unmatched, so retain the
// independently matched address-derived ABI view rather than adding a pin.
// The raw body proves MSVC's hidden UnicodeString return storage at [esp+0xc]
// and returns that storage pointer in eax (ret 4).
class Rva00416BD0
{
public:
	UnicodeString getName(void);
};

// The portrait-looking ILT at 0x0002262E is not the named
// ControlBar::setPortraitByObject body: it jumps to the already matched 3-byte
// Gen_0049cfe0::m(int) body at 0x0049CFE0, whose raw body is ret 4.  The old
// AAE setPortraitByObject spelling therefore is not asserted here; call the
// existing RVA owner with its independently established thiscall ABI.
class Gen_0049cfe0
{
public:
	void m(Int value);
};

// ------------------------------------------------------------------------------------------------
/** Show a rally point marker at the world location specified.  If no location is specified
	* any marker that we might have visible is hidden */
// ------------------------------------------------------------------------------------------------
// BFME's rally-point marker differs from the reference in three ways that are
// all visible in the call sequence: newDrawable takes a third argument (retail
// pushes -1 after the status bits), setDrawableStatus is inlined to an OR into
// the dword at Drawable+0x110, and the whole position/orientation/colour block
// is guarded by `if (marker)`.  The reference guards only the creation arm and
// then dereferences the marker unconditionally -- under NDEBUG its
// DEBUG_ASSERTCRASH compiles away and nothing is left to stop a null.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *string );
	~BFMERetailAsciiString() { releaseBuffer(); }
private:
	void releaseBuffer();
	char *m_data;
};

// BFME's GameClient vtable is not the vendored one: findDrawableByID is slot 11
// (+0x2C) against slot 8 (+0x20) here, and destroyDrawable slot 24 (+0x60)
// against slot 19 (+0x4C).  Three virtuals ahead of findDrawableByID and two more
// between it and destroyDrawable that the reference header does not declare.
class BFMEGameClientDrawables
{
public:
	virtual void unused00() = 0;
	virtual void unused01() = 0;
	virtual void unused02() = 0;
	virtual void unused03() = 0;
	virtual void unused04() = 0;
	virtual void unused05() = 0;
	virtual void unused06() = 0;
	virtual void unused07() = 0;
	virtual void unused08() = 0;
	virtual void unused09() = 0;
	virtual void unused10() = 0;
	virtual Drawable *findDrawableByID( const DrawableID id ) = 0;	///< vtable +0x2C
	virtual void unused12() = 0;
	virtual void unused13() = 0;
	virtual void unused14() = 0;
	virtual void unused15() = 0;
	virtual void unused16() = 0;
	virtual void unused17() = 0;
	virtual void unused18() = 0;
	virtual void unused19() = 0;
	virtual void unused20() = 0;
	virtual void unused21() = 0;
	virtual void unused22() = 0;
	virtual void unused23() = 0;
	virtual void destroyDrawable( Drawable *draw ) = 0;		///< vtable +0x60
};

// Four fields the vendored headers place earlier than BFME does: the downwind
// angle at GlobalData+0x17C against +0x15C, the time of day at +0x218 against
// +0x204, and the player's day/night indicator colours at Player+0x1C4/+0x1C8
// against +0x124/+0x128.
struct BfmeRallyPointGlobalData
{
	unsigned char m_unreconstructed_000[ 0x17c ];
	Real m_downwindAngle;					///< retail this+0x17C
	unsigned char m_unreconstructed_180[ 0x218 - 0x180 ];
	TimeOfDay m_timeOfDay;					///< retail this+0x218
};

struct BfmeRallyPointPlayer
{
	unsigned char m_unreconstructed_000[ 0x1c4 ];
	Color m_playerColor;					///< retail this+0x1C4
	Color m_playerNightColor;				///< retail this+0x1C8
};

struct BfmeRallyPointControlBar
{
	unsigned char m_unreconstructed_000[ 0x64 ];
	DrawableID m_rallyPointDrawableID;			///< retail this+0x64
};

struct BfmeRallyPointDrawable
{
	unsigned char m_unreconstructed_000[ 0x110 ];
	UnsignedInt m_status;					///< retail this+0x110
};

// findTemplate is an inline forwarding to findTemplateInternal(name, check) in
// the vendored header, so the shared spelling pushes the default TRUE as well;
// retail calls a one-argument lookup.  newDrawable takes a third argument retail
// passes -1 for, which is the spelling BFMEThingFactory_newDrawable.cpp already
// carries.
class BFMEThingFactory
{
public:
	const ThingTemplate *findTemplate( const AsciiString &name );
	Drawable *newDrawable( const ThingTemplate *tmplate, DrawableStatus statusBits, Int unknown );
};

// ------------------------------------------------------------------------------------------------
/** Show a rally point marker at the world location specified.  If no location is specified
	* any marker that we might have visible is hidden */
// ------------------------------------------------------------------------------------------------
// ?setControlBarSchemeByPlayer@ControlBar@@ exact retail body is emitted by
// ControlBarSetControlBarSchemeByPlayerThunk.cpp.

// byte-exact reconstruction: game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_setControlBarSchemeByPlayerTemplate_Thunk.cpp
// ?setControlBarSchemeByPlayerTemplate@ControlBar@@ present-unmatched

// ?setControlBarSchemeByName@ControlBar@@QAEXABVAsciiString@@@Z
// Body in game/masm_dumps/ControlBar_setControlBarSchemeByName.asm (exact 68B @ 0x4A0090).
// Retail: if manager, setControlBarScheme(by-value name); if not playback, setDefaultControlBarConfig.
// (Not switchControlBarStage — inlined recorder check. C++ blocked on AsciiString by-value shape.)


// byte-exact reconstruction: game/GameEngine/Source/GameClient/ControlBarPreloadAssets.cpp
// ?preloadAssets@ControlBar@@QAEXW4TimeOfDay@@@Z present-unmatched
// preloadAssets cannot come home, and the blocker is the ledger row rather than
// the body. Its row carries object-symbol=?bfme_preloadAssets_wrapper@ControlBar@@QAEXXZ,
// a member name that exists only inside the donor's own private ControlBar. The
// retail body takes NO argument -- it ends c3 and tail-jumps -- while the row is
// named for the reference's preloadAssets(TimeOfDay). This TU compiles the real
// ControlBar, which declares the one-argument form, so it cannot emit a
// no-argument function and cannot satisfy that object-symbol without a header
// change. The override is the correct mechanism here, not a wart.

// ?updateBuildQueueDisabledImages@ControlBar@@ present-unmatched

// ?updateBuildUpClockColor@ControlBar@@QAEXH@Z present-unmatched



// ?updateCommanBarBorderColors@ControlBar@@QAEXHHHH@Z present-unmatched

// ---------------------------------------------------------------------------------------
// hides the communicator button

// ---------------------------------------------------------------------------------------
// Outside hook so when the genera's head is pushed, we can switch to the purchase science
// context
// ?updatePurchaseScience@ControlBar@@QAEXXZ present-unmatched

// byte-exact reconstruction: game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_showPurchaseScience.cpp
// ?showPurchaseScience@ControlBar@@QAEXXZ present-unmatched

// The BFME purchase-science path uses these singleton slots directly.  The
// ZH declarations describe a different window and Shell layout, so the
// retail offsets stay local to this recovered body.
struct BfmePurchaseScienceWindowView
{
	char m_pad000[0x254];
	unsigned char m_hidden;
};

extern int g_Va012F4C38;
class Shell;
extern Shell *TheShell;

struct BfmeShellStateView
{
	char m_pad000[0x50];
	unsigned char m_isShellActive;
};

class BfmeGlobal_012f19e8
{
public:
	void bfmeCall_000290d2();
};
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

// byte-exact reconstruction: game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_togglePurchaseScience.cpp
// ?togglePurchaseScience@ControlBar@@QAEXXZ present-unmatched

// Functions for repositioning/resizing the control bar

// The default bar position is at ControlBar+0x18, the stage at +0x20 and the
// context parents from +0x34 with the master first.
struct BfmeControlBarLowConfig
{
	char m_slice_pad[ 0x18 ];				///< retail this+0x00..+0x17, untouched
	ICoord2D m_defaultControlBarPosition;			///< retail this+0x18
	Int m_currentControlBarStage;				///< retail this+0x20
	char m_slice_padB[ 0x34 - 0x24 ];
	GameWindow *m_contextParent[ NUM_CONTEXT_PARENTS ];	///< retail this+0x34
};

// ?setLowControlBarConfig@ControlBar@@IAEXXZ
// removed from multiplayer test
//void ControlBar::showCommandMarkers( void )
//{
//	for(Int i =0; i < MAX_COMMANDS_PER_SET; ++i)
//	{
//		if(m_commandWindows[i]->winIsHidden())
//			m_commandMarkers[i]->winHide(FALSE);
//		else
//			m_commandMarkers[i]->winHide(TRUE);
//	}
//}
//
// byte-exact reconstruction: game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarUpdateSlotExitImageThunk.cpp
// ?updateSlotExitImage@ControlBar@@QAEXPBVImage@@@Z present-unmatched

// Retail places the final two image fields at +0x2c0/+0x2c4.  The shared ZH
// ControlBar declaration places them at +0x300/+0x304, so keep this BFME
// layout correction local to the recovered method.
struct BfmeControlBarUpdateImageTail
{
	unsigned char prefix[0x2c0];
	const Image *generalButtonEnable;
	const Image *generalButtonHighlight;
};

// ?getForegroundMarkerPos@ControlBar@@QAEXPAH0@Z present-unmatched
// ?getBackgroundMarkerPos@ControlBar@@QAEXPAH0@Z present-unmatched

// ?drawTransitionHandler@ControlBar@@QAEXXZ present-unmatched
enum{
	RADAR_ATTACK_GLOW_FRAMES = 150,
	RADAR_ATTACK_GLOW_NUM_TIMES = 15  ///< number of times we'll flash
};

#pragma pack(push, 1)
struct BFMEControlBarRadarGlowLayout
{
	unsigned char pad0[0x2E0];
	unsigned char glowOn;
	unsigned char pad1[3];
	Int remainingFrames;
	GameWindow *glowWindow;
};
#pragma pack(pop)

__declspec(noinline) void ControlBar::triggerRadarAttackGlow( void )
{
	BFMEControlBarRadarGlowLayout *retail = reinterpret_cast<BFMEControlBarRadarGlowLayout *>(this);
	if(!retail->glowWindow)
		return;
	retail->glowOn = TRUE;
	retail->remainingFrames = RADAR_ATTACK_GLOW_FRAMES;
	if(BitTest(retail->glowWindow->winGetStatus(),WIN_STATUS_ENABLED) == TRUE)
		retail->glowWindow->winEnable(FALSE);
}

// The three radar-glow fields sit 0x40 earlier in BFME than the vendored
// ControlBar puts them: the on flag at +0x2e0, the remaining frame count at
// +0x2e4 and the window at +0x2e8.
struct BfmeControlBarRadarGlow
{
	unsigned char m_unreconstructed_00[ 0x2e0 ];
	unsigned char m_radarAttackGlowOn;			///< retail this+0x2e0
	unsigned char m_unreconstructed_2e1[ 3 ];
	Int m_remainingRadarAttackGlowFrames;			///< retail this+0x2e4
	GameWindow *m_radarAttackGlowWindow;			///< retail this+0x2e8
};

// ?updateRadarAttackGlow@ControlBar@@IAEXXZ
// ?initSpecialPowershortcutBar@ControlBar@@QAEXPAVPlayer@@@Z
// Body in game/masm_dumps/_str3__initSpecialPowershortcutBar_ControlBar_QAEXPAVPlayer_Z_49F1C0.asm (exact 766B retail @ 0x0049F1C0).
// byte-exact reconstruction: game/GameEngine/Source/Common/ControlBar_populateSpecialPowerShortcutMethodThunk.cpp
// ?populateSpecialPowerShortcut@ControlBar@@IAEXPAVPlayer@@@Z present-unmatched

//-------------------------------------------------------------------------------------------------
// ?hasAnyShortcutSelection@ControlBar@@QBE_NXZ present-unmatched

//-------------------------------------------------------------------------------------------------
// ControlBar::updateSpecialPowerShortcut is byte-verified in ControlBar_updateSpecialPowerShortcut.cpp.

//-------------------------------------------------------------------------------------------------
// ?drawSpecialPowerShortcutMultiplierText@ControlBar@@QAEXXZ present-unmatched

// The animation manager is at ControlBar+0x10, the shortcut button array at
// +0xcc, the used-button count at +0xf4 and the shortcut parent at +0xfc.  reset
// is the virtual at vtable+0x10 while the other two are direct calls.
class BfmeAnimateWindowManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void reset(void);				///< vtable +0x10

	void registerGameWindow(GameWindow *win, Int animType, Bool needsToFinish,
			Int ms, Int delayMs);				///< ILT 0x00045322
	void reverseAnimateWindow(void);			///< ILT 0x00027B65
};

struct BfmeControlBarShortcutFields
{
	unsigned char m_unreconstructed_00[ 0x10 ];
	BfmeAnimateWindowManager *m_animateWindowManagerForGenShortcuts;	///< retail this+0x10
	unsigned char m_unreconstructed_14[ 0xcc - 0x14 ];
	GameWindow *m_specialPowerShortcutButtons[ 10 ];	///< retail this+0xcc
	Int m_currentlyUsedSpecialPowersButtons;		///< retail this+0xf4
	unsigned char m_unreconstructed_f8[ 4 ];
	GameWindow *m_specialPowerShortcutParent;		///< retail this+0xfc
};

// ?animateSpecialPowerShortcut@ControlBar@@QAEX_N@Z

// BFME's final guard asks ONE question where the reference asks two: retail
// checks only whether the local player has a shortcut special power, and has no
// hasAnyShortcutSelection() term at all. With the extra term the shortcut bar
// stayed hidden whenever the player had no shortcut power, even if a selection
// would have shown it.
//
// isGameEnding does not survive as a call -- it inlines to a signed test of the
// field at TheScriptEngine+0x17080 -- and the array null check is kept even
// though it cannot fail: retail takes the address of the member array with lea
// and tests that, which is what testing an array member compiles to.
struct BfmeShowScriptEngine
{
	unsigned char m_unreconstructed_00[ 0x17080 ];
	Int m_endGameTimer;					///< retail this+0x17080

	Bool isGameEnding() const { return m_endGameTimer >= 0; }
};

class BfmeShortcutPlayer
{
public:
	// Returns a 32-bit value: retail tests eax, not al.
	Int hasAnyShortcutSpecialPower(void);			///< ILT 0x0002331C
};

struct BfmeShortcutPlayerList
{
	unsigned char m_unreconstructed_00[ 0x0c ];
	BfmeShortcutPlayer *m_localPlayer;			///< retail this+0x0c

	BfmeShortcutPlayer *getLocalPlayer() { return m_localPlayer; }
};

// ?showSpecialPowerShortcut@ControlBar@@QAEXXZ

// ControlBar::hideSpecialPowerShortcut moved to ControlBarFields.cpp: it
// needs the reconstructed-offset shim (inputs/reference/shims/controlbar), which
// this TU does not use (see ControlBarFields.cpp for why).
