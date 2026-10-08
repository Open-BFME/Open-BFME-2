// cl: /MD /EHsc
// ?rva005E712A@Rva005E7C19@@QAEXH@Z @0x005E712A 53B
// Virtual slot 1 (offset 0x4) of vtable 0x00877F14 (class of ??1Rva005E7C19@@UAE@XZ).
// Emits GameMessage 0x6AE via MessageStreamSubsystem slot 0x48 then two integer args:
// chain this+4 -> +0x18 -> +0x18 int, plus this+8 int. Single int param unused (ret 4).
// Evidence: packet disasm with rowed appendIntegerArgument 0x0030F936 and global
// MessageStreamSubsystem VA 0x00A00950; vtable from Rva005E7C19Dtor.cpp; /O1 flags from donor TU.
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
extern class MessageStream *TheMessageStream;
struct ChainB005E712A
{
	char m_pad[0x18];
	int m_18;
};
struct ChainA005E712A
{
	char m_pad[0x18];
	ChainB005E712A *m_18;
};
class Rva005E7C19
{
public:
	void rva005E712A(int unused);
private:
	void *m_00;
	ChainA005E712A *m_04;
	int m_08;
};
void Rva005E7C19::rva005E712A(int unused)
{
	(void)unused;
	GameMessage *msg = TheMessageStream->appendType(0x6AE);
	msg->appendIntegerArgument(m_04->m_18->m_18);
	msg->appendIntegerArgument(m_08);
}
