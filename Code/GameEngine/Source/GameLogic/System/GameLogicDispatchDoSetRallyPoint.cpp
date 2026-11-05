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
// audio events are built from TheAudio's getMiscAudio (slot 78, +0x138): +0xDC / +0xD8;
// the display name comes from the drawable (0x002765D4) or the object
// (0x0028F2F8); a selected drawable marks the control bar dirty.
// Donor: reference/open-bfme-1/targets/game/reverse/attempts/0x00396d40.cpp.
// Shape notes: the coordinate initialisations copy member by member (retail
// movss) while the later assignments are whole-struct (movsd); the success
// path nests under the exit-interface test with the final `return false` last
// (retail places the shared epilogue after the no-path return).
#include "unicode_string.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "Common/GameAudio.h"
#include "Common/MiscAudioClass.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

// The bridge-path query is pinned with WWMath's Vector3 for its points.
#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

// Zero Hour's Coord3D::set-style copy: member by member.
static inline void copyCoord(Coord3D *dst, const Coord3D *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

enum NameKeyType { NAMEKEY_NONE = 0 };

#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

class LocomotorTemplate;
class LocomotorStore { public: LocomotorTemplate *findLocomotorTemplate(Int key); };
extern LocomotorStore *TheLocomotorStore;

class Object;
#include "../../../Include/GameClient/Drawable.h"

#include "../../../Include/Common/Player.h"

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

#include "../../../Include/GameLogic/AIPathfind.h"
#include "../../../Include/GameLogic/AI.h"
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
#include "../../../Include/GameLogic/LocomotorSet.h"

#include "../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

#include "../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;

extern AudioManager *TheAudio;

class Rva002D9508 { public: void rva002D9508(const void *position); };		// setPosition
class Rva0033F15DDwordSlot { public: void set(int value); };			// setPlayerIndex

#include "../../../Include/GameClient/ControlBar.h"
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
				TheInGameUI->rva0029E846(TheGameText->fetch("GUI:RallyPointNoPath"));

				static BfmeAudioEventPrefix136 rallyNotSet(TheAudio->getMiscAudio()->m_DC, 0);
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
		message.format(TheGameText->fetchPtr("GUI:RallyPointSet"), substitute);
		TheInGameUI->rva0029E846(message);

		static BfmeAudioEventPrefix136 rallyPointSet(TheAudio->getMiscAudio()->m_D8, 0);
		((Rva002D9508 *)&rallyPointSet)->rva002D9508(&rallyPosition);
		((Rva0033F15DDwordSlot *)&rallyPointSet)->set(object->getControllingPlayer()->m_playerIndex);
		TheAudio->addAudioEvent(&rallyPointSet);

		if (drawable && drawable->m_selected)
			TheControlBar->field28 = true;
	}
	return true;
	}
	return false;
}

// Native 0x0037747C..0x003774AB and WB 0x00F4BD10 prove an integer
// iterateObjects callback: apply the global point to AUTO_RALLYPOINT objects
// and count successful changes. KindOfGetNameFromSingleBit names bit 69;
// the native template mask byte is +0x110 bit 0x20. The original helper
// identifier is unavailable, so the name retains its address qualifier.
struct GlobalRallyPointData
{
	Coord3D position;
	int changed;
};

int Rva0037747CSetGlobalRallyPoint(Object *object, void *userData)
{
	GlobalRallyPointData *data = (GlobalRallyPointData *)userData;
	if ((object->m_template->m_pad000[0x110] & 0x20) &&
		Rva0037711ADoSetRallyPoint(object, &data->position, false, 0))
		++data->changed;
	return 1;
}

// Native 0x003774AB..0x003775F7 and WB F4BB40 establish the helper's
// complete behavior and two-argument cdecl ABI. The callback/coordinate
// record is shared with the integer Player::iterateObjects provider.
void Rva003774ABSetGlobalRallyPoint(Object *object, const Coord3D *position)
{
	Bool isLocal = object->isLocallyControlled();
	GlobalRallyPointData data;
	copyCoord(&data.position, position);
	data.changed = 0;
	object->getControllingPlayer()->iterateObjects(Rva0037747CSetGlobalRallyPoint, &data);
	if (isLocal && data.changed > 0)
	{
		UnicodeString message;
		message.format(TheGameText->fetchPtr("GUI:GlobalRallyPointSet"));
		TheInGameUI->message(message);
		static BfmeAudioEventPrefix136 globalRallyPointSet(TheAudio->getMiscAudio()->m_D8, 0);
		((Rva002D9508 *)&globalRallyPointSet)->rva002D9508(position);
		((Rva0033F15DDwordSlot *)&globalRallyPointSet)->set(object->getControllingPlayer()->m_playerIndex);
		TheAudio->addAudioEvent(&globalRallyPointSet);
		Drawable *drawable = object->getDrawable();
		if (drawable && drawable->m_selected)
			TheControlBar->field28 = true;
	}
}
