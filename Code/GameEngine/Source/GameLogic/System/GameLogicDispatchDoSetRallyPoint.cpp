// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// ?Rva0037711ADoSetRallyPoint@@YA_NPAVObject@@PBUCoord3D@@_N0@Z
// Retail 0x0037711A..0x0037747C (866 bytes).
//
// BFME 2's rally-point setter, Zero Hour GameLogicDispatch.cpp's
// doSetRallyPoint (every literal is that function's: "HumanLocomotor",
// "GUI:RallyPointNoPath", "GUI:RallyPointSet"; the audio names come from the
// audio settings here). Callers 0x00377497 (object, pos, 0, 0) and
// 0x00377E93 (..., 1, object): the third argument switches the feedback,
// the fourth replaces the position with that object's. The four-argument
// shape and the Bool result are not the twin's, so the name keeps the
// address token (as the Open-BFME-1 partial 0x00396D40 does).
// BFME 2 deltas: ships (template byte +0x11F bit 0x10) path with
// "LargeShipLocomotor" from the exit interface's natural rally point (slot 9),
// others with "HumanLocomotor" from its exit position (slot 10); the path
// test is QuickDoesPathExist (pin 0x002F477E) with the bridge fallback
// rva002E9442; the locomotor set is the rowed 0x001E7087 class; the static
// audio events are built from TheAudio's settings (slot 0x138, +0xDC / +0xD8);
// the display name comes from the drawable (0x002765D4) or the object
// (0x0028F2F8); a selected drawable marks the control bar dirty.
// Donor: reference/open-bfme-1/targets/game/reverse/attempts/0x00396d40.cpp.
// Shape notes: the coordinate initialisations copy member by member (retail
// movss) while the later assignments are whole-struct (movsd); the success
// path nests under the exit-interface test with the final `return false` last
// (retail places the shared epilogue after the no-path return).
#include "unicode_string.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

// The bridge-path query is pinned with WWMath's Vector3 for its points.
class Vector3
{
public:
	Real X, Y, Z;
};

// Zero Hour's Coord3D::set-style copy: member by member.
static inline void copyCoord(Coord3D *dst, const Coord3D *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

enum NameKeyType { NAMEKEY_NONE = 0 };

class NameKeyGenerator { public: NameKeyType nameToKey(const char *name); };
extern NameKeyGenerator *TheNameKeyGenerator;

class LocomotorTemplate;
class LocomotorStore { public: LocomotorTemplate *findLocomotorTemplate(Int key); };
extern LocomotorStore *TheLocomotorStore;

class Object;
class Drawable
{
public:
	Bool rva002765D4(UnicodeString *name);	// the display name, when it has one
	unsigned char m_pad000[0x43C];
	Bool m_selected;			// +0x43C
};

class Player { public: unsigned char m_pad00[0x54]; Int m_playerIndex; };

class ThingTemplate { public: unsigned char m_pad000[0x11F]; unsigned char m_kindOf11F; };

class ExitInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06();
	virtual void setRallyPoint(const Coord3D *pos);				// +0x1C
	virtual void v08();
	virtual void getNaturalRallyPoint(Coord3D *pos, Bool offset);		// +0x24
	virtual Bool getExitPosition(Coord3D *pos, Real *orientation);		// +0x28
};

class Object
{
public:
	Bool isLocallyControlled() const;
	ExitInterface *getObjectExitInterface() const;
	Player *getControllingPlayer() const;
	Drawable *getDrawable() const;
	void *getDisplayName();
	const Coord3D *getPosition() const { return &m_position; }
	void *m_vtable;
	ThingTemplate *m_template;	// +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position;		// +0x38
};

class Pathfinder
{
public:
	Bool QuickDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, Int locomotorSet);
	Bool rva002E9442(const Vector3 &from, const Vector3 &to, Vector3 *result);
};
class AI { public: Pathfinder *pathfinder() const { return m_pathfinder; } unsigned char m_pad00[0x10]; Pathfinder *m_pathfinder; };
extern AI *TheAI;

Bool Rva0037711ADoSetRallyPoint(Object *object, const Coord3D *position, Bool showFeedback, Object *positionSource);

// The locomotor set (rowed ctor 0x001E7087 / dtor 0x001E86D0 under this
// address name; addLocomotor is LocomotorSet's).
class Rva001E7087
{
	friend Bool Rva0037711ADoSetRallyPoint(Object *, const Coord3D *, Bool, Object *);
public:
	Rva001E7087();
protected:
	virtual ~Rva001E7087();
private:
	unsigned char m_pad04[0x24 - 4];
};
class LocomotorSet { public: void addLocomotor(const LocomotorTemplate *lt, Bool optional); };

class GameTextInterface
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11) V(12) V(13) V(14)
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);		// +0x3C
	V(16)
	virtual const UnicodeString &fetchRef(const char *label, Bool *exists = 0);	// +0x44
#undef V
};
extern GameTextInterface *TheGameText;

class InGameUI
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11) V(12) V(13) V(14) V(15)
#undef V
	virtual void message(UnicodeString message, ...);	// +0x40
};
extern InGameUI *TheInGameUI;

struct AudioSettings
{
	unsigned char m_pad000[0xD8];
	OpaqueRefElement4 m_rallyPointSet;	// +0xD8
	OpaqueRefElement4 m_unableToSetRallyPoint;	// +0xDC
};
class AudioManager
{
public:
#define V(n) virtual void v##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24)
	virtual void addAudioEvent(BfmeAudioEventPrefix136 *event);	// +0x64
	V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(50) V(51) V(52) V(53)
	V(54) V(55) V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67)
	V(68) V(69) V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77)
#undef V
	virtual AudioSettings *getAudioSettings();	// +0x138
};
extern AudioManager *TheAudio;

class Rva002D9508 { public: void rva002D9508(const void *position); };		// setPosition
class Rva0033F15DDwordSlot { public: void set(int value); };			// setPlayerIndex

class ControlBar { public: unsigned char m_pad00[0x28]; Bool m_uiDirty; };
extern ControlBar *TheControlBar;

Bool Rva0037711ADoSetRallyPoint(Object *object, const Coord3D *position, Bool showFeedback, Object *positionSource)
{
	Bool isLocal = object->isLocallyControlled();
	Coord3D rallyPosition;
	copyCoord(&rallyPosition, position);
	ExitInterface *exitInterface = object->getObjectExitInterface();
	Rva001E7087 locomotorSet;
	Coord3D start;
	copyCoord(&start, object->getPosition());

	NameKeyType key;
	if (object->m_template->m_kindOf11F & 0x10)
	{
		key = TheNameKeyGenerator->nameToKey("LargeShipLocomotor");
		if (exitInterface)
			exitInterface->getNaturalRallyPoint(&start, true);
	}
	else
	{
		if (exitInterface)
		{
			Real orientation = 0.0f;
			Coord3D exitPos;
			if (exitInterface->getExitPosition(&exitPos, &orientation))
				start = exitPos;
		}
		key = TheNameKeyGenerator->nameToKey("HumanLocomotor");
	}
	((LocomotorSet *)&locomotorSet)->addLocomotor(TheLocomotorStore->findLocomotorTemplate(key), false);

	if (!positionSource)
	{
		if (!TheAI->pathfinder()->QuickDoesPathExist(object, &start, &rallyPosition, (Int)&locomotorSet) &&
			!TheAI->pathfinder()->rva002E9442(*(const Vector3 *)object->getPosition(), (const Vector3 &)rallyPosition, (Vector3 *)&rallyPosition))
		{
			if (isLocal && showFeedback)
			{
				TheInGameUI->message(TheGameText->fetch("GUI:RallyPointNoPath"));

				static BfmeAudioEventPrefix136 rallyNotSet(TheAudio->getAudioSettings()->m_unableToSetRallyPoint, 0);
				((Rva002D9508 *)&rallyNotSet)->rva002D9508(&rallyPosition);
				((Rva0033F15DDwordSlot *)&rallyNotSet)->set(object->getControllingPlayer()->m_playerIndex);
				TheAudio->addAudioEvent(&rallyNotSet);
			}
			return false;
		}
	}
	else
	{
		rallyPosition = *positionSource->getPosition();
	}

	if (exitInterface)
	{
	exitInterface->setRallyPoint(&rallyPosition);

	if (isLocal && showFeedback)
	{
		UnicodeString message;
		UnicodeString name;
		Drawable *drawable = object->getDrawable();
		const void *text;
		if (drawable && drawable->rva002765D4(&name))
			text = *(void *const *)&name;
		else
			text = *(void *const *)object->getDisplayName();
		const unsigned short *substitute = text ? (const unsigned short *)((const char *)text + 8) : L"";
		message.format(&TheGameText->fetchRef("GUI:RallyPointSet"), substitute);
		TheInGameUI->message(message);

		static BfmeAudioEventPrefix136 rallyPointSet(TheAudio->getAudioSettings()->m_rallyPointSet, 0);
		((Rva002D9508 *)&rallyPointSet)->rva002D9508(&rallyPosition);
		((Rva0033F15DDwordSlot *)&rallyPointSet)->set(object->getControllingPlayer()->m_playerIndex);
		TheAudio->addAudioEvent(&rallyPointSet);

		if (drawable && drawable->m_selected)
			TheControlBar->m_uiDirty = true;
	}
	return true;
	}
	return false;
}
