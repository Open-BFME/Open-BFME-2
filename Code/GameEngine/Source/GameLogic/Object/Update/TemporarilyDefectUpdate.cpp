// cl: /O1 /DNDEBUG /MD /EHsc

// BFME1 donor: ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/GameLogic/Object/Update/TemporarilyDefectUpdate_update.cpp.
// Target identity: module factory/constructor at 0x004CC6AF names
// TemporarilyDefectUpdate; its +0x10 update-interface vtable 0x0085F594
// has this body in slot 0. WorldBuilder 0x012759A0 is the matching update.
// Target boundary: native 0x004CC882..0x004CC96D, 235 bytes, ending RET;
// the WB matcher incorrectly includes the following 27-byte module parser.
// This TU uses the update-interface view: incoming this is complete-object
// +0x10, Object is at this-8, and trailing state at +0x10/+0x14/+0x1C.
// Independent target deltas: PlayerList local player +0x10, message slot
// +0x48/type 0x3ED, InGameUI deselect slot +0x10C, completion state +0x274,
// and the existing 0x004CC829 predicate replaces BFME1's inline test.

enum ObjectID { INVALID_ID = 0 };

typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_10 = 10,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class Drawable;
class Player;
class GameMessage;

class Object
{
public:
    Player *getControllingPlayer() const;
    void rva0029A12B();
    unsigned char m_pad000[0x74];
    unsigned int m_id;
    unsigned char m_pad078[0x274-0x78];
    unsigned int m_completionState;
};
class Thing
{
public:
    Drawable *getDrawable() const;
};
class Rva004CC829
{
public:
    bool rva004CC829();
};

class PlayerList
{
public:
	unsigned char m_pad000[0x10];
	Player *m_localPlayer;
};

class GameMessage
{
public:
	enum Type
	{
		MSG_REMOVE_FROM_SELECTED_GROUP = 0x3ED
	};

	void appendObjectIDArgument(ObjectID id);
};

class MessageStream
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual GameMessage *appendMessage(GameMessage::Type type) = 0;
};

class InGameUI
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8C() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9C() = 0;
	virtual void slotA0() = 0;
	virtual void slotA4() = 0;
	virtual void slotA8() = 0;
	virtual void slotAC() = 0;
	virtual void slotB0() = 0;
	virtual void slotB4() = 0;
	virtual void slotB8() = 0;
	virtual void slotBC() = 0;
	virtual void slotC0() = 0;
	virtual void slotC4() = 0;
	virtual void slotC8() = 0;
	virtual void slotCC() = 0;
	virtual void slotD0() = 0;
	virtual void slotD4() = 0;
	virtual void slotD8() = 0;
	virtual void slotDC() = 0;
	virtual void slotE0() = 0;
	virtual void slotE4() = 0;
	virtual void slotE8() = 0;
	virtual void slotEC() = 0;
	virtual void slotF0() = 0;
	virtual void slotF4() = 0;
	virtual void slotF8() = 0;
	virtual void slotFC() = 0;
	virtual void slot100() = 0;
	virtual void slot104() = 0;
	virtual void slot108() = 0;
	virtual void deselectDrawable(Drawable *draw) = 0;
};

extern PlayerList *ThePlayerList;
extern MessageStream *TheMessageStream;
extern InGameUI *TheInGameUI;

class TemporarilyDefectUpdate
{
public:
	virtual UpdateSleepTime update();

private:
	unsigned char m_pad004[0x0C];
	UnsignedInt m_endFrame;
	UnsignedInt m_startFrame;
	UnsignedInt m_defectorID;
	unsigned char m_fxFired;
};

// ?update@TemporarilyDefectUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime TemporarilyDefectUpdate::update()
{
	Object *object = *(Object **)((char *)this - 8);
	Drawable *drawable = ((Thing *)object)->getDrawable();
	UnsignedInt zero = 0;

	if (m_fxFired != 0)
	{
		m_startFrame = zero;
		m_endFrame = zero;
		m_fxFired = (unsigned char)zero;
		if (drawable != 0 && object != 0)
		{
			Player *localPlayer = ThePlayerList->m_localPlayer;
			if (object->getControllingPlayer() == localPlayer)
			{
				GameMessage *message = TheMessageStream->appendMessage(
					GameMessage::MSG_REMOVE_FROM_SELECTED_GROUP);
				message->appendObjectIDArgument((ObjectID)object->m_id);
				TheInGameUI->deselectDrawable(drawable);
			}
		}
		return UPDATE_SLEEP_FOREVER;
	}

	if (((Rva004CC829 *)((char *)this - 0x10))->rva004CC829())
	{
		m_startFrame = zero;
		m_endFrame = zero;
		m_fxFired = (unsigned char)zero;
		if (drawable != 0 && object != 0)
		{
			Player *localPlayer = ThePlayerList->m_localPlayer;
			if (object->getControllingPlayer() == localPlayer)
			{
				GameMessage *message = TheMessageStream->appendMessage(
					GameMessage::MSG_REMOVE_FROM_SELECTED_GROUP);
				message->appendObjectIDArgument((ObjectID)object->m_id);
				TheInGameUI->deselectDrawable(drawable);
			}
		}

		if (object->m_completionState == zero)
			object->rva0029A12B();
		return UPDATE_SLEEP_FOREVER;
	}
	return UPDATE_SLEEP_10;
}
