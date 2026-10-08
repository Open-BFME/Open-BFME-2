// cl: /O1 /DNDEBUG /MD
//
// ?rva002D2F32@Rva002D2F32Owner@@QAEXXZ @0x002D2F32 109B: frameless message
// post (thiscall, no args, void). Returns early when TheGameLogic+0x110
// is 3 or own +0x128 byte is clear; when ThePlayerList mid is present
// with +0x750 == 2, appends message 0x469 with int args 0 and 2 through
// MessageStream slot 0x48, else appends it with only arg 2. Callee is
// the landed GameMessage::appendIntegerArgument; slot order mirrors the
// landed KeyboardInitUpdate MessageStream view. Views minimal for
// resolution; exact identities unproven.
class GameLogic
{
public:
	char m_pad[0x110];
	int m_110;
};
extern GameLogic *TheGameLogic;

struct Rva002D2F32Mid
{
	char m_pad[0x750];
	int m_750;
};

class PlayerList
{
public:
	char m_pad[0x10];
	Rva002D2F32Mid *m_mid;
};
extern PlayerList *ThePlayerList;

class GameMessage
{
public:
	enum Type
	{
		MSG_RVA469 = 0x469
	};

	void appendIntegerArgument(int arg);
};

class MessageStream
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(GameMessage::Type type);
};
extern class MessageStream *TheMessageStream;

class Rva002D2F32Owner
{
public:
	void rva002D2F32();

private:
	char m_pad[0x128];
	unsigned char m_128;
};

// ?rva002D2F32@Rva002D2F32Owner@@QAEXXZ
void Rva002D2F32Owner::rva002D2F32()
{
	if (TheGameLogic->m_110 == 3)
		return;
	if (m_128 == 0)
		return;
	Rva002D2F32Mid *mid = ThePlayerList->m_mid;
	if (mid != 0 && mid->m_750 == 2) {
		GameMessage *m = TheMessageStream->appendMessage(GameMessage::MSG_RVA469);
		m->appendIntegerArgument(0);
		m->appendIntegerArgument(2);
		return;
	}
	GameMessage *m2 = TheMessageStream->appendMessage(GameMessage::MSG_RVA469);
	m2->appendIntegerArgument(2);
}
