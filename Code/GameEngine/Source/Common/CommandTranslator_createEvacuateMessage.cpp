// cl: /MD
// ?createEvacuateMessage@CommandTranslator@@QAEHPAVDrawable@@H@Z @0x00429093. BFME1's
// CommandTranslator::createEvacuateMessage (0x005ADA90) has the same callees in order, and
// its message type 0x41F is this body's 0x420 (BFME2's enum is shifted by one
// here, as for the two sibling create*Message bodies); Zero Hour's body shape.
// 127B
// Evidence: caller 0x0042A398 plus TheInGameUI slot73 plus PickAndPlayInfo ctor 0x004D92FE plus pickAndPlayUnitVoiceResponse pin plus MessageStreamSubsystem slot 0x48 with 0x420 plus appendObjectIDArgument 0x0030F979
// 0x420 is spelled as a cast: MessageStream.h still numbers MSG_EVACUATE 0x41E
// (Zero Hour), one short of this body's value.
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/IRegion2D.h"
union GameMessageArgumentType { int integer; unsigned drawableID; ICoord2D pixel; IRegion2D pixelRegion; Coord3D location; };
#include "GameLogicObjectLookupView.h"
#include "../../Include/Common/MessageStream.h"

class PickAndPlayInfo { public:
 PickAndPlayInfo();
 bool field00; char pad01[3]; Drawable* m_drawTarget; void* m_weaponSlot;
 void* field0c; int m_specialPowerType; Coord3D m_position; void* field1c;
};
class Object {
public:
 virtual void slot00();
 void* m_template; char pad08[0x30]; Coord3D m_position; char pad44[0x30]; ObjectID m_id;
 ObjectID getID() const { return m_id; }
};
class Drawable { public: char pad00[0xfc]; Object* m_object; Object* getObject() const { return m_object; } const Coord3D* getPosition() const; };
class DrawableList;
class InGameUI {
public:
 virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
 virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
 virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
 virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
 virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
 virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
 virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
 virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual void slot1F();
 virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
 virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
 virtual void slot28(); virtual void slot29(); virtual void slot2A(); virtual void slot2B();
 virtual void slot2C(); virtual void slot2D(); virtual void slot2E(); virtual void slot2F();
 virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
 virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
 virtual void slot38(); virtual void slot39(); virtual void slot3A(); virtual void slot3B();
 virtual void slot3C(); virtual void slot3D(); virtual void slot3E(); virtual void slot3F();
 virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
 virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
 virtual void slot48();
 virtual const DrawableList* getAllSelectedDrawables() const; // vtable +0x124
};
extern InGameUI* TheInGameUI;
extern MessageStream* TheMessageStream;
bool pickAndPlayUnitVoiceResponse(const DrawableList*,GameMessage::Type,PickAndPlayInfo* = 0);
class CommandTranslator {
public:
 virtual ~CommandTranslator();
private:
 int opaque04; bool m_teamExists;
public:
 int createEvacuateMessage(Drawable*,int);
};

int CommandTranslator::createEvacuateMessage(Drawable *draw, int commandType)
{
	if (commandType == 2)
		return (GameMessage::Type)0x420;
	GameMessage::Type msgType = (GameMessage::Type)0x420;
	if (draw != 0 && draw->getObject() != 0)
	{
		if (m_teamExists)
		{
			PickAndPlayInfo info;
			info.m_drawTarget = draw;
			pickAndPlayUnitVoiceResponse((const DrawableList*)TheInGameUI->getAllSelectedDrawables(), msgType, &info);
			GameMessage *msg = TheMessageStream->appendMessage(msgType);
			msg->appendObjectIDArgument(draw->getObject()->getID());
		}
		return msgType;
	}
	return 0;
}
