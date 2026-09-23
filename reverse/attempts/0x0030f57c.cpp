// ??1GameMessageList@@UAE@XZ
// partial score=0.93 date=2026-09-23
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
	int m_pad08; // +0x08
	void *m_list; // +0x0C
};

void operator delete(void *ptr);

class GameMessageList : public SubsystemInterface
{
public:
	GameMessageList();
	virtual ~GameMessageList();

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
