// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0GameMessageList@@QAE@XZ, retail 0x0030F562 (26 bytes).
// ??1GameMessageList@@UAE@XZ, retail 0x0030F57C (86 bytes).
// ??0CommandList@@QAE@XZ, retail 0x0030F842 (18 bytes).
// ?destroyAllMessages@CommandList@@QAEXXZ, retail 0x0030F854 (44 bytes).
// ??1CommandList@@UAE@XZ, retail 0x0031105A (56 bytes).
// Message-list file-unit (the GameMessage append methods live rowed in
// MessageStream.cpp, which keeps its own decls; this shard declares the
// construction view). ZH MessageStream.cpp donor proves every semantic:
// GameMessageList holds first/last message at +0xC/+0x10 over the
// SubsystemInterface base (base ctor/dtor resolve via the existing
// 0x001B4E63/0x001B4E74 pins, zero new pins), CommandList derives it with
// an empty ctor, destroyAllMessages walks and deletes, and both dtors
// tear down (CommandList via destroyAllMessages plus the base dtor).
// Vtables install automatically (dtors defined here) with DIR32-masked
// immediates (no ??_7 pin at either table; delete helpers force the
// vtable and scalar-deleting dtor emission; operator delete resolves
// via the rowed ??3).

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	unsigned char m_pad[0xC - 4]; // +0x04..+0x0B
};

class GameMessage
{
public:
	virtual void *deleteInstance(int flags);

	void *m_next; // +0x04
	void *m_prev; // +0x08
	void *m_list; // +0x0C
};

void operator delete(void *ptr);

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

class GameMessageList : public SubsystemInterface
{
public:
	GameMessageList();
	virtual ~GameMessageList();
	virtual void appendMessage(class GameMessage *msg);
	virtual void insertMessage(class GameMessage *msg, class GameMessage *messageToInsertAfter);

	GameMessage *m_firstMessage; // +0x0C
	GameMessage *m_lastMessage; // +0x10
};

class CommandList : public GameMessageList
{
public:
	CommandList();
	virtual ~CommandList();
	void destroyAllMessages();
};

static int s_messageStreamVtable;

class __declspec(novtable) MessageStream : public GameMessageList
{
public:
	MessageStream();
	virtual ~MessageStream();

	struct TranslatorData
	{
		TranslatorData() : m_next(0), m_prev(0), m_id(0), m_translator(0), m_priority(0) {}
		TranslatorData *m_next; // +0x00
		TranslatorData *m_prev; // +0x04
		unsigned int m_id; // +0x08
		class GameMessageTranslator *m_translator; // +0x0C
		unsigned int m_priority; // +0x10
		~TranslatorData();
	};

	class GameMessageTranslator *findTranslator(unsigned int id);
	void removeTranslator(unsigned int id);
	unsigned int rva0030F738(class GameMessageTranslator *translator, unsigned int priority);

private:
	void *m_firstTranslator; // +0x14
	void *m_lastTranslator; // +0x18
	int m_nextTranslatorID; // +0x1C
};

class GameMessageTranslator
{
public:
	virtual int translate();
	virtual void *deleteInstance(int flags);
};

// ??0GameMessageList@@QAE@XZ @0x0030F562
GameMessageList::GameMessageList() :
	SubsystemInterface()
{
	m_firstMessage = 0;
	m_lastMessage = 0;
}

// ??1GameMessageList@@UAE@XZ @0x0030F57C
GameMessageList::~GameMessageList()
{
	GameMessage *msg, *nextMsg;
	for (msg = m_firstMessage; msg; msg = nextMsg)
	{
		msg->m_list = 0;
		_ReadWriteBarrier();
		nextMsg = (GameMessage *)msg->m_next;
		::operator delete(msg->deleteInstance(0));
	}
}

// ??0CommandList@@QAE@XZ @0x0030F842
CommandList::CommandList() :
	GameMessageList()
{
}

void deleteGameMessageList(GameMessageList *p)
{
	delete p;
}

void deleteCommandList(CommandList *p)
{
	delete p;
}

// ?destroyAllMessages@CommandList@@QAEXXZ @0x0030F854
void CommandList::destroyAllMessages()
{
	GameMessage *msg, *nextMsg;
	for (msg = m_firstMessage; msg; msg = nextMsg)
	{
		nextMsg = (GameMessage *)msg->m_next;
		::operator delete(msg->deleteInstance(0));
	}
	m_firstMessage = 0;
	m_lastMessage = 0;
}

// ??1CommandList@@UAE@XZ @0x0031105A
CommandList::~CommandList()
{
	destroyAllMessages();
}

// ??0MessageStream@@QAE@XZ @0x0030F697
MessageStream::MessageStream() :
	GameMessageList(),
	m_firstTranslator(0),
	m_lastTranslator(0)
{
	*(unsigned int *)this = (unsigned int)&s_messageStreamVtable;
	m_nextTranslatorID = 1;
}

// ??1TranslatorData@MessageStream@@QAE@XZ @0x0030F463
inline MessageStream::TranslatorData::~TranslatorData()
{
	GameMessageTranslator *trans = m_translator;
	::operator delete(trans ? trans->deleteInstance(0) : 0);
}

void deleteTranslatorData(MessageStream::TranslatorData *p)
{
	delete p;
}

// ?findTranslator@MessageStream@@QAEPAVGameMessageTranslator@@I@Z @0x0030F7D7
// MessageStream::findTranslator from ZH MessageStream.cpp donor: walks
// m_firstTranslator at +0x14 via m_next at +0x00 matching m_id at +0x08
// returning m_translator at +0x0C. Retail 28B loop with xor-first /O1 shape.
GameMessageTranslator *MessageStream::findTranslator(unsigned int id)
{
	TranslatorData *translatorData;

	for (translatorData = (TranslatorData *)m_firstTranslator; translatorData; translatorData = translatorData->m_next)
	{
		if (translatorData->m_id == id)
			return translatorData->m_translator;
	}

	return 0;
}

// ?removeTranslator@MessageStream@@QAEXI@Z @0x0030F7F3 79B
// MessageStream::removeTranslator from ZH MessageStream.cpp donor: finds the
// m_id (+0x08) match along m_next, unlinks it from first/last (+0x14/+0x18)
// and deletes it through the out-of-line ~TranslatorData 0x0030F463.
// Target caller: ~GameClient 0x0023AE08 per translator it attached.
void MessageStream::removeTranslator(unsigned int id)
{
	TranslatorData *translatorData;

	for (translatorData = (TranslatorData *)m_firstTranslator; translatorData; translatorData = translatorData->m_next)
	{
		if (translatorData->m_id == id)
		{
			if (translatorData->m_prev)
				translatorData->m_prev->m_next = translatorData->m_next;
			else
				m_firstTranslator = translatorData->m_next;

			if (translatorData->m_next)
				translatorData->m_next->m_prev = translatorData->m_prev;
			else
				m_lastTranslator = translatorData->m_prev;

			delete translatorData;
			break;
		}
	}
}

// ?rva0030F738@MessageStream@@QAEIPAVGameMessageTranslator@@I@Z @0x0030F738 159B
// MessageStream translator attach sorted by priority from ZH donor (MessageStream.cpp attachTranslator).
// Evidence: packet disasm with rowed operator new 0x0002FDA0; prev/next in this TU; TranslatorData 0x14 plus first/last/nextID at +0x14/+0x18/+0x1C; 14 callers in 0x0023A1BB.
unsigned int MessageStream::rva0030F738(GameMessageTranslator *translator, unsigned int priority)
{
	TranslatorData *newSS = new TranslatorData;
	TranslatorData *ss;

	newSS->m_translator = translator;
	newSS->m_priority = priority;
	newSS->m_id = m_nextTranslatorID++;

	if (m_firstTranslator == 0)
	{
		newSS->m_prev = 0;
		newSS->m_next = 0;
		m_firstTranslator = newSS;
		m_lastTranslator = newSS;
		return newSS->m_id;
	}

	for (ss = (TranslatorData *)m_firstTranslator; ss; ss = ss->m_next)
		if (ss->m_priority > newSS->m_priority)
			break;

	if (ss)
	{
		if (ss->m_prev)
		{
			ss->m_prev->m_next = newSS;
			newSS->m_prev = ss->m_prev;
			newSS->m_next = ss;
			ss->m_prev = newSS;
		}
		else
		{
			newSS->m_prev = 0;
			newSS->m_next = (TranslatorData *)m_firstTranslator;
			((TranslatorData *)m_firstTranslator)->m_prev = newSS;
			m_firstTranslator = newSS;
		}
	}
	else
	{
		((TranslatorData *)m_lastTranslator)->m_next = newSS;
		newSS->m_prev = (TranslatorData *)m_lastTranslator;
		newSS->m_next = 0;
		m_lastTranslator = newSS;
	}

	return newSS->m_id;
}

// ?appendMessage@GameMessageList@@UAEXPAVGameMessage@@@Z @0x0030F5D2 50B vslot 14
// GameMessageList append to end from ZH donor appendMessage. Evidence: vtable slot 14 of
// GameMessageList/MessageStream/CommandList plus prev/next in this TU plus first/last at +0x0C/+0x10.
void GameMessageList::appendMessage(GameMessage *msg)
{
	if (!msg)
		return;
	msg->m_next = 0;
	if (m_lastMessage)
	{
		m_lastMessage->m_next = msg;
		msg->m_prev = m_lastMessage;
		m_lastMessage = msg;
	}
	else
	{
		m_firstMessage = msg;
		m_lastMessage = msg;
		msg->m_prev = 0;
	}
	msg->m_list = this;
}

// ?insertMessage@GameMessageList@@UAEXPAVGameMessage@@0@Z @0x0030F604 62B vslot 15
// GameMessageList insert after from ZH donor insertMessage plus null head insert.
// Evidence: vtable slot 15 of GameMessageList/MessageStream/CommandList plus prev/next in this TU.
void GameMessageList::insertMessage(GameMessage *msg, GameMessage *messageToInsertAfter)
{
	if (messageToInsertAfter)
	{
		msg->m_next = messageToInsertAfter->m_next;
		msg->m_prev = messageToInsertAfter;
		messageToInsertAfter->m_next = msg;
	}
	else
	{
		msg->m_next = m_firstMessage;
		msg->m_prev = 0;
		m_firstMessage = msg;
	}
	if (msg->m_next)
		((GameMessage *)msg->m_next)->m_prev = msg;
	else
		m_lastMessage = msg;
	msg->m_list = this;
}

// ??1TranslatorData is a header inline elsewhere: another unit emits a
// select-any copy, so a strong definition here was a duplicate symbol in
// the linked build. This anchor only makes this unit emit its copy for the
// ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitMessageStreamListCtors@@YAXPAUTranslatorData@MessageStream@@@Z present-unmatched
void bfmeEmitMessageStreamListCtors(MessageStream::TranslatorData *p)
{
	p->MessageStream::TranslatorData::~TranslatorData();
}
#pragma inline_depth()
