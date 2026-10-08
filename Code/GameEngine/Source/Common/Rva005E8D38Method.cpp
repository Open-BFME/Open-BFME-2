// cl: /O1 /MD /EHsc
// ?rva005E8D38@Rva005E8D38@@QAEXXZ @0x005E8D38 57B: message emit of type 0x6AB
// with two integer arguments. Identity: ref table slot 0x00877F6C reaches it;
// neighbours are FUN_009e89dd and ?rva005E0D94. Same layout and appendIntegerArgument
// row (0x0030F936) as ?rva005E92B1 (0x005E92B1); MessageStream slot 0x48 appendType.

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

extern MessageStream *TheMessageStream;

struct Rva005E8D38Inner
{
	char m_pad[0x12C];
	int m_first;
};

struct Rva005E8D38Mid
{
	char m_pad[0x18];
	int m_second;
	Rva005E8D38Inner *m_inner;
};

struct Rva005E8D38Other
{
	char m_pad[0x4];
	int m_third;
};

class Rva005E8D38
{
public:
	void rva005E8D38();
private:
	char m_pad[0x18];
	Rva005E8D38Mid *m_mid;
	Rva005E8D38Other *m_other;
};

// ?rva005E8D38@Rva005E8D38@@QAEXXZ
void Rva005E8D38::rva005E8D38()
{
	GameMessage *msg = TheMessageStream->appendType(0x6AB);
	msg->appendIntegerArgument(m_mid->m_inner->m_first);
	msg->appendIntegerArgument(m_mid->m_second);
}
