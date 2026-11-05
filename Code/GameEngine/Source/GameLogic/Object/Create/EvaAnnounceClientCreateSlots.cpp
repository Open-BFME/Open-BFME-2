// cl: /DNDEBUG /MD /ICode/Libraries/Include
//
// ?rva004C9A51@EvaAnnounceClientCreate@@UAEXXZ, retail 0x004C9A51, 49 bytes:
// slot 1 of the vtable EvaAnnounceClientCreate's ctor 0x004C99D4 installs at
// +0x0C (0x00C5ED48; slot 0 is the shared no-op). Once (the +0x14 flag), sets
// the frame at +0x10 to TheGameLogic's frame (+0x40) plus the module data's
// +0x14 delay, at least 2, and never earlier than frame 7 (the at-least-2
// written as a running maximum is what gives retail's cmova under
// /arch:SSE). Compiled with the +0x0C subobject this. Names by address.
#include "Lib/Coord3D.h"

typedef unsigned int UnsignedInt;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Object;

#include "../../../../Include/Common/Player.h"

#include "../object.h"

#include "../../../../Include/Common/PlayerList.h"

extern PlayerList *ThePlayerList;

enum EvaEventID { EVA_EVENT_NONE = 0 };
#include "../../../../Include/GameClient/Eva.h"

extern Eva *TheEva;

// The drawable test is rowed at 0x00270260 under its own address-named class.
class Rva00270260
{
public:
	bool rva00270260();
};

#include "../../../../Include/GameClient/Drawable.h"

#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

struct EvaAnnounceClientCreateModuleData
{
	unsigned char m_pad00[0x08];
	int m_announcementEventEnemy; // +0x08
	int m_announcementEventAlly; // +0x0C
	int m_10; // +0x10
	UnsignedInt m_delay; // +0x14
	bool m_onlyIfVisible; // +0x18
	bool m_countAsFirstSightedAnnoucement; // +0x19
	bool m_useObjectsPosition; // +0x1A
};

class ClientCreateModule
{
public:
	virtual ~ClientCreateModule();
	virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4();
	virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8();
	virtual void slot9(); virtual void slot10(); virtual void slot11();
	virtual void clientUpdate() = 0;
protected:
	const EvaAnnounceClientCreateModuleData *m_moduleData; // +0x04
	Drawable *m_drawable; // +0x08
};

class CreateModuleInterface
{
public:
	virtual void slot0();
	virtual void rva004C9A51() = 0;
};

class EvaAnnounceClientCreate : public ClientCreateModule, public CreateModuleInterface
{
public:
	virtual void rva004C9A51();
	virtual void clientUpdate();
private:
	UnsignedInt m_10; // +0x10
	bool m_14; // +0x14
};

void EvaAnnounceClientCreate::rva004C9A51()
{
	if (m_14)
		return;
	m_14 = true;
	UnsignedInt delay = 2;
	if (m_moduleData->m_delay > delay)
		delay = m_moduleData->m_delay;
	m_10 = delay + TheGameLogic->getFrame();
	if (m_10 < 7)
		m_10 = 7;
}

// WorldBuilder EvaAnnounceClientCreate::clientUpdate, WB VA 0x0126E7D0 (lead score 3; no args, ret).
void EvaAnnounceClientCreate::clientUpdate()
{
	if (m_10 == 0 || m_10 > TheGameLogic->getFrame())
		return;
	Drawable *draw = m_drawable;
	const EvaAnnounceClientCreateModuleData *evaAnnounceClientCreateModuleData = m_moduleData;
	m_10 = 0;
	if (evaAnnounceClientCreateModuleData->m_onlyIfVisible && (draw->field_440 || ((Rva00270260 *)draw)->rva00270260()))
		return;
	Object *obj = draw->getObject();
	if (obj == 0)
		return;
	if (evaAnnounceClientCreateModuleData->m_countAsFirstSightedAnnoucement)
		draw->m_status = (DrawableStatus)(draw->m_status | 0x80);
	int event;
	Player *ctl = obj->getControllingPlayer();
	if (ctl == ThePlayerList->getLocalPlayer())
		event = evaAnnounceClientCreateModuleData->m_10;
	else
	{
		switch (ThePlayerList->getLocalPlayer()->getRelationship(obj))
		{
		case ENEMIES:
		case NEUTRAL:
			event = evaAnnounceClientCreateModuleData->m_announcementEventEnemy;
			break;
		case ALLIES:
			event = evaAnnounceClientCreateModuleData->m_announcementEventAlly;
			break;
		default:
			event = -1;
			break;
		}
	}
	if (event == -1)
		return;
	const Coord3D *pos = 0;
	if (evaAnnounceClientCreateModuleData->m_useObjectsPosition)
		pos = draw->getPosition();
	TheEva->reportEvaEvent((EvaEventID)event, pos, draw->getPosition());
}
