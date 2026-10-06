// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1MessageStream@@UAE@XZ, retail 0x00310FA1 (84 bytes).
// MessageStream dtor shard (regular virtual, not novtable, so the compiler
// emits the vtable store plus EH prolog in retail order). ZH MessageStream.cpp
// donor proves the semantics: walk the translator list deleting each entry
// then tear down the GameMessageList base. TranslatorData dtor plus operator
// delete resolve via the rowed bodies; the GameMessageList base dtor resolves
// via the existing 0x0030F57C pin until that dtor lands.

class GameMessage
{
public:
	enum Type
	{
		DUMMY_TYPE
	};
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void postProcessLoad();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw();

private:
	unsigned char m_pad[0xC - 4]; // +0x04..+0x0B
};

void operator delete(void *ptr);

class GameMessageList : public SubsystemInterface
{
public:
	GameMessageList();
	virtual ~GameMessageList();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void appendMessage(GameMessage *msg);
	virtual void insertMessage(GameMessage *msg, GameMessage *messageToInsertAfter);
	virtual void removeMessage(GameMessage *msg);
	virtual bool containsMessageOfType(GameMessage::Type type);

	void *m_firstMessage; // +0x0C
	void *m_lastMessage; // +0x10
};

class GameMessageTranslator
{
public:
	virtual int translate();
	virtual void *deleteInstance(int flags);
};

class MessageStream : public GameMessageList
{
public:
	MessageStream();
	virtual ~MessageStream();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual GameMessage *appendMessage(GameMessage::Type type);
	virtual GameMessage *insertMessage(GameMessage::Type type, GameMessage *messageToInsertAfter);

	struct TranslatorData
	{
		TranslatorData *m_next; // +0x00
		TranslatorData *m_prev; // +0x04
		unsigned int m_id; // +0x08
		GameMessageTranslator *m_translator; // +0x0C
		unsigned int m_priority; // +0x10
		~TranslatorData();
	};

private:
	TranslatorData *m_firstTranslator; // +0x14
	TranslatorData *m_lastTranslator; // +0x18
	int m_nextTranslatorID; // +0x1C
};

void deleteMessageStream(MessageStream *p)
{
	delete p;
}

// ??1MessageStream@@UAE@XZ @0x00310FA1
MessageStream::~MessageStream()
{
	TranslatorData *trans, *nextTrans;
	for (trans = m_firstTranslator; trans; trans = nextTrans)
	{
		nextTrans = trans->m_next;
		delete trans;
	}
}
