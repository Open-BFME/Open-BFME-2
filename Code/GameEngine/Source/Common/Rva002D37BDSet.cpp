// cl: /O1 /DNDEBUG /MD
//
// ?rva002D37BD@Rva002D37BDOwner@@QAEXE@Z @0x002D37BD 96B: byte-field setter
// with zero-side effect (thiscall, 1 byte arg, void). No-op when the new
// value equals m_10+0x128; when clearing to zero with ThePlayerList mid
// present and +0x750 == 2, posts message 0x469 with int args (0, 2)
// through the MessageStream slot used by landed 0x002D2F32; then stores
// the value. Callee is landed GameMessage::appendIntegerArgument.
// Views mirror the landed message TU; exact identities unproven.
struct Rva002D37BDMid
{
	char m_pad[0x750];
	int m_750;
};

class PlayerList
{
public:
	char m_pad[0x10];
	Rva002D37BDMid *m_mid;
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

struct Rva002D37BDMid10
{
	char m_pad[0x128];
	unsigned char m_128;
};

class Rva002D37BDOwner
{
public:
	void rva002D37BD(unsigned char v);

private:
	char m_pad[0x10];
	Rva002D37BDMid10 *m_10;
};

// ?rva002D37BD@Rva002D37BDOwner@@QAEXE@Z
void Rva002D37BDOwner::rva002D37BD(unsigned char v)
{
	if (v == m_10->m_128)
		return;
	if (v == 0) {
		Rva002D37BDMid *mid = ThePlayerList->m_mid;
		if (mid != 0 && mid->m_750 == 2) {
			GameMessage *m = TheMessageStream->appendMessage(GameMessage::MSG_RVA469);
			m->appendIntegerArgument(0);
			m->appendIntegerArgument(2);
		}
	}
	m_10->m_128 = v;
}
