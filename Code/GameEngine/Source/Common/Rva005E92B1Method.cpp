// cl: /O1 /MD /EHsc
// ?rva005E92B1@Rva005E92B1@@QAEXXZ @0x005E92B1 70B: message emit of type 0x6AA
// with three integer arguments. Identity: ref table slot 0x00878014 reaches it;
// neighbours are ?rva005E0D94. MessageStream slot 0x48 (appendType) and GameMessage
// appendIntegerArgument row at 0x0030F936 per Rva0042F9DAEmit precedent.

class GameMessage
{
public:
	void appendIntegerArgument(int arg);
};

class MessageStream
{
public:
	virtual void v00();
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
	virtual GameMessage *appendType(int type);
};

extern MessageStream *MessageStreamSubsystem;

struct Rva005E92B1Inner
{
	char m_pad[0x12C];
	int m_first;
};

struct Rva005E92B1Mid
{
	char m_pad[0x18];
	int m_second;
	Rva005E92B1Inner *m_inner;
};

struct Rva005E92B1Other
{
	char m_pad[0x4];
	int m_third;
};

class Rva005E92B1
{
public:
	void rva005E92B1();
private:
	char m_pad[0x18];
	Rva005E92B1Mid *m_mid;
	Rva005E92B1Other *m_other;
};

// ?rva005E92B1@Rva005E92B1@@QAEXXZ
void Rva005E92B1::rva005E92B1()
{
	GameMessage *msg = MessageStreamSubsystem->appendType(0x6AA);
	msg->appendIntegerArgument(m_mid->m_inner->m_first);
	msg->appendIntegerArgument(m_mid->m_second);
	msg->appendIntegerArgument(m_other->m_third);
}
