// cl: /O1 /DNDEBUG /MD /EHsc
//
// Keyboard::init (retail 0x0023260F, 17B) and Keyboard::update (0x00232BC7,
// 22B), slots 1 and 10 of vtable 0x00BE81F0. That table is Keyboard's: its
// slots 14 and 16 are pure (Zero Hour's getCapsState and getKey), the
// DirectInputKeyboard table 0x00BC8688 fills them (0x00098BC8 is
// GetKeyState(VK_CAPITAL) & 1), and its own init (0x00098CAC) calls this
// init before openKeyboard (0x00098BD4). The ledger currently labels the two
// tables ??_7AIPlayer@@6B@ and ??_7AISkirmishPlayer@@6B@.
//
// Zero Hour's bodies (GameClient/Input/Keyboard.cpp): init names the keys
// (0x002306B8, Zero Hour's initKeyNames) and zeroes the input frame (+0xE1C);
// update bumps the input frame and refreshes the key data, which BFME2 does in
// two steps over its key vector (0x00232B7B, already pinned, then 0x00232A42)
// where Zero Hour calls updateKeys.
//
// Keyboard::createStreamMessages (0x002326FB, 104B, slot 15) is Zero Hour's
// loop over the key records, run over BFME2's key vector (+0x10 begin, +0x14
// end) instead of up to a KEY_NONE terminator, and skipping and then marking
// records whose status is KeyboardIO::STATUS_USED. MSG_RAW_KEY_DOWN and
// MSG_RAW_KEY_UP are 0x15 and 0x16 here; appendMessage is MessageStream's
// slot 18 (+0x48).

typedef int Int;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;

enum
{
	KEY_STATE_UP = 0x0001,
	KEY_STATE_DOWN = 0x0002
};

// upstream layout: GeneralsMD/Code/GameEngine/Include/GameClient/Keyboard.h
struct KeyboardIO
{
	enum StatusType
	{
		STATUS_UNUSED = 0x00,
		STATUS_USED = 0x01
	};

	void setUsed() { status = STATUS_USED; }

	UnsignedByte key;
	UnsignedByte status;
	UnsignedShort state;
	UnsignedInt keyDownTimeMsec;
};

class GameMessage
{
public:
	enum Type
	{
		MSG_RAW_KEY_DOWN = 0x15,
		MSG_RAW_KEY_UP = 0x16
	};

	void appendIntegerArgument(Int arg);		///< matched 0x0030F936
};

class MessageStream
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(GameMessage::Type type);	// slot 18 (+0x48)
};

// Ledger name of the stream global at VA 0x00E00950 (Zero Hour's
// TheMessageStream).
extern MessageStream *MessageStreamSubsystem;

class Keyboard
{
public:
	virtual void init();
	virtual void update();
	virtual void createStreamMessages();

protected:
	void initKeyNames();						///< pinned 0x002306B8 (ZH name)

private:
	void rva00232B7B();							///< pinned 0x00232B7B
	void rva00232A42();

	unsigned char m_unmodelled_04[0x10 - 0x04];
	KeyboardIO *m_keysBegin;					// +0x10, the key vector
	KeyboardIO *m_keysEnd;						// +0x14
	unsigned char m_unmodelled_18[0xE1C - 0x18];
	Int m_inputFrame;							// +0xE1C (ZH name)
};

void Keyboard::init()
{
	initKeyNames();
	m_inputFrame = 0;
}

void Keyboard::update()
{
	m_inputFrame++;
	rva00232B7B();
	rva00232A42();
}

void Keyboard::createStreamMessages()
{
	// santiy
	if (MessageStreamSubsystem == 0)
		return;

	KeyboardIO *end = m_keysEnd;
	GameMessage *msg = 0;
	for (KeyboardIO *key = m_keysBegin; key != end; key++)
	{
		if (key->status == KeyboardIO::STATUS_USED)
			continue;

		// add message to stream
		if (key->state & KEY_STATE_DOWN)
			msg = MessageStreamSubsystem->appendMessage(GameMessage::MSG_RAW_KEY_DOWN);
		else if (key->state & KEY_STATE_UP)
			msg = MessageStreamSubsystem->appendMessage(GameMessage::MSG_RAW_KEY_UP);

		// fill out message arguments
		if (msg)
		{
			msg->appendIntegerArgument(key->key);
			msg->appendIntegerArgument(key->state);
		}

		key->setUsed();
	}
}
