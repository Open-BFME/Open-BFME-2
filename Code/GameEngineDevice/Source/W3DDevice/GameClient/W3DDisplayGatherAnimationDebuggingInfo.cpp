// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// W3DDisplay::gatherAnimationDebuggingInfo, retail 0x0004B31C..0x0004BEF2 (3030 bytes).
// The WorldBuilder twin (W3DDisplay.cpp, assert line 2603) names it and gives
// the statement order; everything else is read from retail: twenty-five
// animation debug display strings at +0x1D0, the language data's debug font
// (as in gatherNetworkStats), the locked/selected/moused-over object pick, the
// draw module's animation interface, the current weapon line (under the FP-mode
// logic guard outside multiplayer) and a history of 0x5C-byte animation
// records diffed by the GlobalData animation debug mode at +0x9CC.
//
// The history vector is retail's function-local static; its storage and the
// construction guard word after it are the ledger's g_Va00DE1CAC datum, its
// atexit destructor the rowed thunk rva007B6AC8. Every view below names the
// rowed callee it reaches. The FP-mode guard's constructor 0x0004224C lives
// here (not in its own unit): this body's frame layout only matches when the
// compiler can see that it does not keep `this`.
#include "ascii_string.h"
#include "unicode_string.h"
#include <stdlib.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

// Retail calls the game format-and-append helper at 0x002CEC42.
// Its target owns a vector of lines; it is not a CRT FILE stream.
struct FprintfTarget;
extern "C" void __cdecl fprintf(FprintfTarget *target, const char *format, ...);
extern "C" void *theLogicRandomLogFile;

class GameFont;
class Object;
class Drawable;

#include "../../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"
enum WeaponSlotType { PRIMARY_WEAPON = 0 };
enum WeaponStatus { READY_TO_FIRE = 0 };

#define V4(a) virtual void a##0(); virtual void a##1(); virtual void a##2(); virtual void a##3();
#define V16(a) V4(a##0) V4(a##1) V4(a##2) V4(a##3)

#include "../../../../GameEngine/Include/GameClient/DisplayString.h"

#include "../../../../GameEngine/Include/GameClient/DisplayStringManager.h"
extern DisplayStringManager *TheDisplayStringManager;

#include "../../../../GameEngine/Include/GameClient/FontLibrary.h"
extern FontLibrary *TheFontLibrary;

// The native debug display font description of the language data.
#include "../../../../GameEngine/Include/Common/GlobalLanguageClass.h"
extern GlobalLanguage *TheGlobalLanguageData;

// The writable global data as this body reads it.
#include "../../../../GameEngine/Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
// The indexed debug strings below own the complete null-terminated retail
// tables at DB3BB4 (four pointers) and DBC7AC (eight pointers). The existing
// gather body establishes their roles; data_rows verifies each literal and
// pointer independently. These spellings retain its existing declarations.
const char *TheAnimDebugModeNames[] = {
	"ANIMATION_FILE", "MODEL_CONDITION_STATES", "MODEL_ANIM_STATE", 0
};
extern const char *TheWeaponSlotTypeNames[];
const char *TheWeaponStatusNames[] = {
	"READY_TO_FIRE", "OUT_OF_AMMO", "BETWEEN_FIRING_SHOTS", "RELOADING_CLIP",
	"PRE_ATTACK", "FIRING", "IN_FOLLOW_THRU", 0
};

#include "../../../../GameEngine/Include/GameClient/KeyboardClass.h"
extern Keyboard *TheKeyboard;

#include "../../../../GameEngine/Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;

#include "../../../../GameEngine/Include/GameClient/GameClientClass.h"
extern GameClient *TheGameClient;

extern GameLogic *TheGameLogic;
// GameLogic +0x1B4: the FP-mode guard nesting depth the guard below decrements.
struct GameLogicDepthView { char m_unreconstructed_000[0x1B4]; Int m_logicDepth; };

class Rva000421FD
{
public:
	void rva000421FD();
};

// The FP-mode logic guard: 0x0004224C enters, the out-of-line destructor
// 0x00042262 leaves.
class Rva0004224C
{
public:
	__declspec(noinline) Rva0004224C *rva0004224C();
	__declspec(noinline) Rva0004224C()
	{
		if (TheGameLogic)
			((Rva000421FD *)TheGameLogic)->rva000421FD();
	}
	~Rva0004224C()
	{
		if (TheGameLogic)
			--((GameLogicDepthView *)TheGameLogic)->m_logicDepth;
	}
};

// Keep the separately rowed entry emitted; the constructor above has the
// same complete native body instead of introducing a forwarding wrapper.
Rva0004224C *Rva0004224C::rva0004224C()
{
	if (TheGameLogic)
		((Rva000421FD *)TheGameLogic)->rva000421FD();
	return this;
}

// Model condition flags: describe 0x000467B2, delta 0x00049BE8, equality 0x00045473.
class Rva000467B2
{
public:
	void rva000467B2(AsciiString *out, Int perLine);
};

Bool Rva00045473Equal(const void *a, const void *b);

class Rva00049BE8
{
public:
	UnsignedInt m_bits[19];
	void buildDescription(AsciiString *out, const Rva00049BE8 &other, Bool includeSame, Int perLine) const;
	void describe(AsciiString *out, Int perLine) { ((Rva000467B2 *)this)->rva000467B2(out, perLine); }
};
typedef Rva00049BE8 ModelConditionFlags;
inline Bool flagsEqual(const ModelConditionFlags *modelConditionFlags, const ModelConditionFlags *b) { return Rva00045473Equal(modelConditionFlags, b); }

// One history record: constructed by 0x0004708A, destroyed by 0x000470A0.
class Rva0004708A
{
public:
	Rva0004708A() throw();
	AsciiString m_animationName;		// +0x00
	AsciiString m_animationDetails;		// +0x04
	ModelConditionFlags m_flags;		// +0x08
	Int m_firstFrame;			// +0x54
	Int m_lastFrame;			// +0x58
};

struct BfmeContainerRecord00048139 : public Rva0004708A
{
	~BfmeContainerRecord00048139();
};
typedef BfmeContainerRecord00048139 AnimRecord;

struct BfmePod92 { char m_bytes[0x5C]; };

namespace _STL {
template <class T> class allocator { public: allocator() {} };
template <class T, class A> class _Vector_base
{
public:
	_Vector_base(const A &a) throw();
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
template <class T, class A = allocator<T> > class vector : public _Vector_base<T, A>
{
public:
	void push_back(const T &x);
};
}

class Rva0004B1D2
{
public:
	BfmeContainerRecord00048139 *rva0004B1D2(BfmeContainerRecord00048139 *first, const char *last);
};

// The history vector: retail folds its constructor into _Vector_base<int>'s
// (0x00211E58), push_back into vector<BfmePod92>'s (0x0004B2E5) and erase into
// the record range assign 0x0004B1D2.
class AnimHistory : public _STL::_Vector_base<Int, _STL::allocator<Int> >
{
public:
	AnimHistory(const _STL::allocator<Int> &a = _STL::allocator<Int>()) throw() : _STL::_Vector_base<Int, _STL::allocator<Int> >(a) {}
	AnimRecord *begin() { return (AnimRecord *)_M_start; }
	AnimRecord *end() { return (AnimRecord *)_M_finish; }
	Int size() const { return (AnimRecord *)_M_finish - (AnimRecord *)_M_start; }
	AnimRecord &operator[](Int i) { return ((AnimRecord *)_M_start)[i]; }
	void push_back(const AnimRecord &animRecord) { ((_STL::vector<BfmePod92> *)this)->push_back(*(const BfmePod92 *)&animRecord); }
	AnimRecord *erase(AnimRecord *first, AnimRecord *last) { return ((Rva0004B1D2 *)this)->rva0004B1D2(first, (const char *)last); }
};

extern UnsignedInt g_Va00DE1CAC;	// VA 0x00DE1CAC: the history vector, guard word at +0xC
void __cdecl rva007B6AC8();		// its atexit destructor thunk
static inline AnimHistory &animHistory() { return *(AnimHistory *)&g_Va00DE1CAC; }

class DrawInterface
{
public:
	V4(a) V4(b) virtual void c0();
	virtual Int getAnimationCount();				// +0x24
	virtual AsciiString getAnimationName(Int i);			// +0x28
	virtual void c1();
	virtual void getAnimationDescription(Int i, AsciiString *desc, AsciiString *details);	// +0x30
	virtual const char *getModelName();				// +0x34
};

class DrawModule
{
public:
	V16(a) V16(b) V4(c0) V4(c1) virtual void d0();
	virtual DrawInterface *getDrawInterface();			// +0xA4
	V4(e0) V4(e1) V4(e2) virtual void f0(); virtual void f1();
	virtual void buildSubObjectDescription(AsciiString *out, Int perLine);	// +0xE0
};

struct ThingTemplate
{
	char m_unreconstructed_000[0x64];
	char *m_nameData;		// +0x64
	const char *getNameText() const { return m_nameData ? m_nameData + 8 : ""; }
};

class Drawable
{
public:
	// Call the retail +0x14C getter; a forwarding definition emits a
	// competing COMDAT instead of the getter's verified body.
	DrawModule **getDrawModules();
	void *m_vtable;
	ThingTemplate *m_template;	// +0x04
	char m_unreconstructed_008[0xFC - 8];
	Object *m_object;		// +0xFC
	char m_unreconstructed_100[0x258 - 0x100];
	ModelConditionFlags m_conditionFlags;	// +0x258
};

class ContainModule
{
public:
	V16(a) V16(b) V16(c) V16(d) V4(e)
	virtual Object *getContainedObject();	// +0x110
};

#include "../../../../GameEngine/Include/GameLogic/WeaponTemplate.h"
// The +0x08 name string's text, read through the header's opaque slot.
static __forceinline const char *weaponTemplateNameText(const WeaponTemplate *wt)
{
	const char *data = (const char *)wt->m_field08;
	return data ? data + 8 : "";
}

class Weapon
{
public:
	Real getPercentReadyToFire() const;
	WeaponStatus computeStatus(Bool *out) const;
	WeaponStatus getStatus() const;
	void *m_vtable;
	WeaponTemplate *m_template;	// +0x04
	char m_unreconstructed_008[0x18 - 8];
	UnsignedInt m_nextShot;		// +0x18
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object : public Thing
{
public:
	void *rva0028C197() const;
	ContainModule *getContain() const { return (ContainModule *)rva0028C197(); }
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	const Weapon *getCurrentWeapon(Int *slot) const { return getCurrentWeapon((WeaponSlotType *)slot); }
	char m_unreconstructed_000[0x74];
	Int m_id;			// +0x74
	Int getID() const { return m_id; }
};

enum { ANIM_DEBUG_LINES = 25 };

class W3DDisplay
{
protected:
	void gatherAnimationDebuggingInfo();
private:
	char m_unreconstructed_000[0x1D0];
	DisplayString *m_animDebugStrings[ANIM_DEBUG_LINES];	// +0x1D0
};

void W3DDisplay::gatherAnimationDebuggingInfo()
{
	static int s_mode;
	static int s_prevID;
	static int s_lockedID;
	if (!((&g_Va00DE1CAC)[3] & 1)) {
		(&g_Va00DE1CAC)[3] |= 1;
		animHistory().AnimHistory::AnimHistory();
		atexit(rva007B6AC8);
	}
	UnicodeString text;
	AsciiString description;
	AnimRecord current;
	int slot;

	if (!m_animDebugStrings[0]) {
		GameFont *font;
		if (TheGlobalLanguageData && !TheGlobalLanguageData->m_nativeDebugDisplay.name.isEmpty())
			font = TheFontLibrary->getFont(&TheGlobalLanguageData->m_nativeDebugDisplay.name,
				(float)TheGlobalLanguageData->m_nativeDebugDisplay.size, TheGlobalLanguageData->m_nativeDebugDisplay.bold);
		else {
			AsciiString fixedSys("FixedSys");
			font = TheFontLibrary->getFont(&fixedSys, 8.0f, false);
		}
		for (int i = 0; i < ANIM_DEBUG_LINES; ++i) {
			if (!m_animDebugStrings[i]) {
				m_animDebugStrings[i] = TheDisplayStringManager->newDisplayString();
				m_animDebugStrings[i]->setFont(font);
			}
		}
	}

	text.format(L"ANIMATION STATE DEBUGGER: History based on %S changes. (shift+w toggles)",
		TheAnimDebugModeNames[TheWritableGlobalData->field09CC]);
	m_animDebugStrings[0]->setText(text);

	Object *object = 0;
	Drawable *drawable = 0;
	int lockedID;
	if (TheKeyboard->isCtrl() || TheKeyboard->isShift()) {
		drawable = TheGameClient->findDrawableByID((DrawableID)TheInGameUI->getMousedOverDrawableID());
		if (drawable) {
			object = drawable->m_object;
			s_lockedID = 0;
			if (!object)
				goto selection;
			if (TheKeyboard->isCtrl())
			{
				lockedID = object->getID();
				s_lockedID = lockedID;
			}
			else
				lockedID = s_lockedID;
		} else
			lockedID = s_lockedID;
	} else
		lockedID = s_lockedID;
	if (lockedID && TheGameLogic->findObjectByID((ObjectID)lockedID)) {
		object = TheGameLogic->findObjectByID((ObjectID)lockedID);
		if (object)
			drawable = object->getDrawable();
	} else {
selection:
		s_lockedID = 0;
		if (TheInGameUI->getSelectCount() != 1) {
			drawable = TheGameClient->findDrawableByID((DrawableID)TheInGameUI->getMousedOverDrawableID());
			if (drawable)
				object = drawable->m_object;
		} else {
			drawable = TheInGameUI->getFirstSelectedDrawable();
			object = drawable->m_object;
			if (object) {
				ContainModule *contain = object->getContain();
				if (contain) {
					object = contain->getContainedObject();
					if (object)
						drawable = object->getDrawable();
				}
			}
		}
	}
	if (!object || !drawable)
		goto noObject;

	if (TheGameLogic->findObjectByID((ObjectID)s_prevID) != object || s_mode != TheWritableGlobalData->field09CC) {
		s_prevID = object->m_id;
		animHistory().erase(animHistory().begin(), animHistory().end());
		s_mode = TheWritableGlobalData->field09CC;
	}

	{
		DrawModule **module = 0;
		DrawInterface *drawInterface = 0;
		DrawModule **modules = drawable->getDrawModules();
		DrawInterface *fallback = 0;
		if (modules) {
			for (module = modules; *module; ++module) {
				drawInterface = (*module)->getDrawInterface();
				if (drawInterface) {
					if (drawInterface->getAnimationCount() > 0)
						break;
					fallback = drawInterface;
				}
			}
		}
		if (!drawInterface)
			drawInterface = fallback;
		const char *modelName = 0;
		if (drawInterface)
			modelName = drawInterface->getModelName();
		text.format(L"LOCKED Object: %S (ID:%d) %S", drawable->m_template->getNameText(), object->getID(), modelName ? modelName : "n/a");
		if (s_lockedID)
			text.concat(L" -- release by Shift+mousing over any object");
		m_animDebugStrings[1]->setText(text);

		const Weapon *weapon = object->getCurrentWeapon(&slot);
		if (weapon) {
			unsigned int nextShot = weapon->m_nextShot;
			int percent = (int)(weapon->getPercentReadyToFire() * 100.0f);
			int status;
			if (TheGameLogic->isInMultiplayerGame()) {
				status = weapon->computeStatus(0);
			} else {
				Rva0004224C guard;
				if (theLogicRandomLogFile)
					fprintf((FprintfTarget *)theLogicRandomLogFile, "POTENTIAL DESYNC: Forced into EnterLogic State. (W3DDisplay::gatherAnimationDebuggingInfo)");
				status = weapon->getStatus();
				if (theLogicRandomLogFile)
					fprintf((FprintfTarget *)theLogicRandomLogFile, "LeaveLogic() called.");
			}
			text.format(L"Weapon: %S(%S), NextShot:%d(%d%%), Status:%S", weaponTemplateNameText(weapon->m_template),
				TheWeaponSlotTypeNames[slot], nextShot, percent, TheWeaponStatusNames[status]);
			m_animDebugStrings[2]->setText(text);
		} else {
			text.format(L"Weapon: n/a", drawable->m_template->getNameText(), object->getID());
			m_animDebugStrings[2]->setText(text);
		}

		current.m_firstFrame = current.m_lastFrame = TheGameLogic->getFrame();
		text.format(L"CURRENT Frame: %d", current.m_firstFrame);
		m_animDebugStrings[3]->setText(text);

		if (drawInterface && *module) {
			(*module)->buildSubObjectDescription(&description, 4);
			text.format(L"SubObject Statii: (%S)", description.str());
			m_animDebugStrings[4]->setText(text);
			int count = drawInterface->getAnimationCount();
			if (count >= 1) {
				current.m_animationName = drawInterface->getAnimationName(0);
				drawInterface->getAnimationDescription(0, &description, &current.m_animationDetails);
				if (count >= 2)
					text.format(L"Blending From: %S", description.str());
				else
					text.format(L"CURRENT Animation: %S", description.str());
				m_animDebugStrings[6]->setText(text);
				text.format(L"%S", current.m_animationDetails.str());
				m_animDebugStrings[5]->setText(text);
			} else {
				text.format(L"CURRENT Animation: Doesn't have one!");
				m_animDebugStrings[6]->setText(text);
			}
			if (count >= 2) {
				current.m_animationName = drawInterface->getAnimationName(1);
				drawInterface->getAnimationDescription(1, &description, &current.m_animationDetails);
				text.format(L"Blending To: %S", description.str());
				m_animDebugStrings[7]->setText(text);
				text.format(L"%S", current.m_animationDetails.str());
				m_animDebugStrings[5]->setText(text);
			} else {
				text.format(L"No blend in progress");
				m_animDebugStrings[7]->setText(text);
			}
		}
	}

	current.m_flags = drawable->m_conditionFlags;
	current.m_flags.describe(&description, 4);
	text.format(L"CURRENT ModelConditionFlags: (%S)", description.str());
	m_animDebugStrings[8]->setText(text);

	if (animHistory().size() == 0) {
		animHistory().push_back(current);
	} else {
		switch (TheWritableGlobalData->field09CC) {
		case 0: {
			AnimRecord &last = animHistory()[animHistory().size() - 1];
			if (last.m_animationName.compare(current.m_animationName) == 0)
				last.m_lastFrame = current.m_lastFrame;
			else
				animHistory().push_back(current);
			break;
		}
		case 1: {
			AnimRecord &last = animHistory()[animHistory().size() - 1];
			if (flagsEqual(&last.m_flags, &current.m_flags))
				last.m_lastFrame = current.m_lastFrame;
			else
				animHistory().push_back(current);
			break;
		}
		case 2: {
			AnimRecord &last = animHistory()[animHistory().size() - 1];
			if (last.m_animationDetails.compare(current.m_animationDetails) == 0)
				last.m_lastFrame = current.m_lastFrame;
			else
				animHistory().push_back(current);
			break;
		}
		}
	}

	{
		int size = animHistory().size();
		if (size > 1) {
			AnimRecord *cur = &animHistory()[size - 1];
			AnimRecord *prev = &animHistory()[size - 2];
			cur->m_flags.buildDescription(&description, prev->m_flags, false, 4);
			text.format(L"CURRENT Delta ConditionFlags: %S\n", description.str());
			m_animDebugStrings[9]->setText(text);
			for (int i = 0; i < 5; ++i) {
				int index = size - i - 2;
				int previous = size - i - 3;
				if (previous < 0) {
					text.format(L"");
					m_animDebugStrings[10 + 3 * i]->setText(text);
					m_animDebugStrings[11 + 3 * i]->setText(text);
					m_animDebugStrings[12 + 3 * i]->setText(text);
				} else {
					if (i == 4) {
						cur = &animHistory()[index];
						text.format(L"OLDEST Frame %d-%d: %S", cur->m_firstFrame, cur->m_lastFrame, cur->m_animationDetails.str());
						m_animDebugStrings[22]->setText(text);
						text.format(L"OLDEST Animation: %S", cur->m_animationName.str());
						m_animDebugStrings[23]->setText(text);
						cur->m_flags.describe(&description, 4);
						text.format(L"OLDEST ModelConditionFlags: (%S)\n", description.str());
						m_animDebugStrings[24]->setText(text);
					} else {
						cur = &animHistory()[index];
						text.format(L"OLD Frame %d-%d: %S", cur->m_firstFrame, cur->m_lastFrame, cur->m_animationDetails.str());
						m_animDebugStrings[10 + 3 * i]->setText(text);
						text.format(L"OLD Animation: %S", cur->m_animationName.str());
						m_animDebugStrings[11 + 3 * i]->setText(text);
						prev = &animHistory()[previous];
						cur->m_flags.buildDescription(&description, prev->m_flags, false, 4);
						text.format(L"OLD Delta ConditionFlags: (%S)\n", description.str());
						m_animDebugStrings[12 + 3 * i]->setText(text);
					}
				}
			}
		} else {
			text.format(L"Delta ModelConditions: n/a");
			m_animDebugStrings[9]->setText(text);
		}
	}
	return;

noObject:
	text.format(L"");
	for (int i = 1; i < ANIM_DEBUG_LINES; ++i)
		m_animDebugStrings[i]->setText(text);
	s_prevID = 0;
	animHistory().erase(animHistory().begin(), animHistory().end());
	s_mode = TheWritableGlobalData->field09CC;
}
