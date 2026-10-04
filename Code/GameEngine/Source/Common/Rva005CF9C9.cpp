// cl: /O1 /MD /EHsc
// ?rva005CF9C9@Rva005CF9C9@@QAEXH@Z @0x005CF9C9 54B
// Emits GameMessage type 0x6a7 via MessageStreamSubsystem slot 0x48 then appends arg and [this+4]+0x14+0x30.
// Evidence: unlock lane; callees rowed 0x0030F936 appendIntegerArgument; global MessageStreamSubsystem at VA 0x00A00950; callers 0x005D0DBB 0x005D0E10 pass this-8 and one int (ret 4).
class GameMessage
{
public:
	void appendIntegerArgument(int arg);
};

class MessageStream
{
public:
	virtual ~MessageStream();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual GameMessage *CreateMessage(int type);
};

extern MessageStream *MessageStreamSubsystem;

struct Rva005CF9C9Inner
{
	char _00[0x30];
	int m_30;
};

struct Rva005CF9C9Mid
{
	char _00[0x14];
	Rva005CF9C9Inner *m_14;
};

class Rva005CF9C9
{
public:
	void rva005CF9C9(int arg);
private:
	char _00[4];
	Rva005CF9C9Mid *m_04;
};

void Rva005CF9C9::rva005CF9C9(int arg)
{
	GameMessage *msg = MessageStreamSubsystem->CreateMessage(0x6a7);
	msg->appendIntegerArgument(arg);
	msg->appendIntegerArgument(m_04->m_14->m_30);
}
