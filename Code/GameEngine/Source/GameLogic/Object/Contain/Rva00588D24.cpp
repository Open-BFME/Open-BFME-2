// cl: /DNDEBUG /MD
// ?rva00588D24@Rva0047A040Base9E0@@QAE_NPAXPAVObject@@@Z @0x00588D24 117B
// Evidence: unlock lane, caller 0x00479ADA lea ecx [esi+0x9E0] (HordeGarrisonContain second base),
// pin rva00588BF3 member of Rva0047A040Base9E0, slots 0x20/0xF4/0x100,
// globals TheGameLogic and g_bfmeWorldRV, callers 0x00477315 and 0x00479AE8.
class Object;

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

class ContainEntry
{
public:
	SLOT08(e00,e01,e02,e03,e04,e05,e06,e07)
	virtual void slot20(Object *obj);
	SLOT08(e09,e10,e11,e12,e13,e14,e15,e16)
	SLOT08(e17,e18,e19,e20,e21,e22,e23,e24)
	SLOT08(e25,e26,e27,e28,e29,e30,e31,e32)
	SLOT08(e33,e34,e35,e36,e37,e38,e39,e40)
	SLOT08(e41,e42,e43,e44,e45,e46,e47,e48)
	SLOT08(e49,e50,e51,e52,e53,e54,e55,e56)
	virtual void e57(); virtual void e58(); virtual void e59(); virtual void e60();
	virtual bool slotF4();
	virtual void e62(); virtual void e63();
	virtual void slot100(unsigned int frame);
};

#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

struct BfmeWorldRV
{
	char _00[0x28];
	unsigned char m_28;
};
extern class ControlBar *TheControlBar;

class Rva00588E44Contain;
#include "../../../../Include/GameLogic/Module/Rva0047A040Base9E0.h"

bool Rva0047A040Base9E0::rva00588D24(void *a, Object *object)
{
	ContainEntry *containEntry = (ContainEntry *)rva00588BF3(a, object);
	if (containEntry == 0)
		return false;
	if (!containEntry->slotF4()) {
		containEntry->slot20(object);
		containEntry->slot100(TheGameLogic->getFrame());
		if (containEntry->slotF4()) {
			(*(BfmeWorldRV **)&TheControlBar)->m_28 = 1;
			containEntry->slot100(0);
		}
		return true;
	}
	containEntry->slot100(0);
	return false;
}

// ?rva00588D99@Rva0047A040Base9E0@@QAEXPAVObject@@@Z @0x00588D99 135B
// Leaf lane, pin gives name. Callers HordeTransportContain 0x004770A6 and
// HordeGarrisonContain 0x00479B7F forward Object* to helper at +0x11D/+0x9E0.
// Drawable gate at +0x43c, local-player gate via ThePlayerList+0x10 and
// getControllingPlayer, message 0x3ED with ObjectID at +0x74 via
// MessageStreamSubsystem slot 0x48 and TheInGameUI slot 0x10c, then
// setStatus(3,true); second arm checks +0x454 then testStatus(0x5E) then
// pinned rva0028BAC0. Layouts follow DrawableRva00276B95, radius-cursor
// PlayerList, Rva0042F9DAEmit MessageStream/InGameUI and Rva0042FB8F ObjectID.
enum ObjectStatusTypes
{
	OBJECT_STATUS_DUMMY = 0
};
#include "../../../../Include/GameClient/Drawable.h"
#include "../../../Common/Thing/thing.h"
class Player;
#include "../../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;
#include "../../../../Include/Common/MessageStream.h"
extern class MessageStream *TheMessageStream;
#include "../../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;
#include "../object.h"
struct ObjectLayout
{
	char _00[0x74];
	ObjectID m_id;
	char _78[0x454 - 0x78];
	unsigned char m_454;
};
void Rva0047A040Base9E0::rva00588D99(Object *obj)
{
	Drawable *drawable = ((Thing *)obj)->getDrawable();
	if (drawable != 0 && drawable->m_selected) {
		Player *local = ThePlayerList->m_local;
		Player *ctrl = obj->getControllingPlayer();
		if (ctrl == local) {
			GameMessage *msg = TheMessageStream->appendMessage(GameMessage::MSG_REMOVE_FROM_SELECTED_GROUP);
			ObjectLayout *objectLayout = (ObjectLayout *)obj;
			msg->appendObjectIDArgument(objectLayout->m_id);
			TheInGameUI->deselectDrawable(drawable);
		}
		obj->setStatus((ObjectStatusTypes)3, true);
	}
	ObjectLayout *o2 = (ObjectLayout *)obj;
	if (o2->m_454 != 0) {
		if (!obj->testStatus((ObjectStatusTypes)0x5E))
			obj->rva0028BAC0();
	}
}

// ?rva00588E20@Rva0047A040Base9E0@@QAEXPAVObject@@@Z @0x00588E20 36B
// Unlock lane, abuts 0x00588D99 in same TU. +0x454 gate to pinned
// rva0028DCC4 then setStatus(3,false). Callers 0x00477101 and 0x00479BBC.
void Rva0047A040Base9E0::rva00588E20(Object *obj)
{
	ObjectLayout *objectLayout = (ObjectLayout *)obj;
	if (objectLayout->m_454 == 0)
		obj->rva0028DCC4();
	obj->setStatus((ObjectStatusTypes)3, false);
}
