// ?reset@NetCommandList@@QAEXXZ
// cl: /O1 /G6 /DNDEBUG /MD
//
// NetCommandList::reset, retail 0x0058B283, 67 bytes. Zero Hour's loop: unlink
// and destroy the head node until the list is empty, then clear the counters.
// Each node's +4/+8 links are cleared before it is detached and deleted.

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef int Int;
enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1
};
Int DoesCommandRequireACommandID(NetCommandType type);

class NetCommandMsg
{
public:
	virtual ~NetCommandMsg();
	void detach();

public:
	UnsignedInt m_timestamp; // +4 (vtable at +0)
	UnsignedInt m_executionFrame; // +8
	UnsignedInt m_playerID; // +0xC
	UnsignedShort m_id; // +0x10
	NetCommandType m_commandType; // +0x14
};

class NetCommandNode
{
public:
	void detach();

	NetCommandMsg *m_msg; ///< retail this+0x00, released by detach
	NetCommandNode *m_next; ///< retail this+0x04, cleared by reset
	NetCommandNode *m_prev; ///< retail this+0x08, cleared by reset
};

// BFME2's message handle shares the node layout (command at +0, next at
// +4, prev at +8) under its own name, which is what removeMessage's
// mangling carries.
class NetCommandRef
{
public:
	NetCommandMsg *getCommand() { return m_command; }
	NetCommandRef *getNext() { return m_next; }
	UnsignedByte getRelay() const { return m_relay; }
	void setRelay(UnsignedByte relay) { m_relay = relay; }

	NetCommandMsg *m_command;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay; ///< retail this+0x0C, copied by appendList
};

class NetCommandList
{
	void *m_unreconstructed_00;
	NetCommandNode *m_first;
	NetCommandNode *m_last;
	NetCommandNode *m_lastMessageInserted;

public:
	void reset();
	void appendList(NetCommandList *list);
	NetCommandRef *addMessage(NetCommandMsg *cmdMsg);
	NetCommandRef *getFirstMessage() { return (NetCommandRef *)m_first; }
	void removeMessage(NetCommandRef *msg);
	NetCommandRef *findMessage(UnsignedShort id, UnsignedByte player, UnsignedInt frame);
	NetCommandRef *findMessage(NetCommandMsg *msg);
	bool isEqualCommandMsg(NetCommandMsg *msg1, NetCommandMsg *msg2);
};

void NetCommandList::reset()
{
	while (m_first != 0)
	{
		NetCommandNode *temp = m_first->m_next;
		m_first->m_next = 0;
		m_first->m_prev = 0;
		NetCommandNode *node = m_first;
		if (node != 0)
		{
			node->detach();
			delete node;
		}
		m_first = temp;
	}
	m_last = 0;
	m_lastMessageInserted = 0;
}

// ?detach@NetCommandNode@@QAEXXZ
void NetCommandNode::detach()
{
	if (m_msg)
		m_msg->detach();
}

// ?removeMessage@NetCommandList@@QAEXPAVNetCommandRef@@@Z
void NetCommandList::removeMessage(NetCommandRef *msg)
{
	NetCommandNode *ref = (NetCommandNode *)msg;
	if (m_lastMessageInserted == ref) {
		m_lastMessageInserted = ref->m_next;
	}
	if (ref->m_prev != 0) {
		ref->m_prev->m_next = ref->m_next;
	}
	if (ref->m_next != 0) {
		ref->m_next->m_prev = ref->m_prev;
	}
	if (ref == m_first) {
		m_first = ref->m_next;
	}
	if (ref == m_last) {
		m_last = ref->m_prev;
	}
	ref->m_next = 0;
	ref->m_prev = 0;
}

// ?findMessage@NetCommandList@@QAEPAVNetCommandRef@@GEI@Z, retail 0x0058B0D7, 74 bytes.
// 3-arg findMessage (id, player, frame) used by processAck-style callers to retire
// acknowledged commands: walks m_first via +4 links, checks the command at +0 for
// timestamp at +4 == frame first, then DoesCommandRequireACommandID(type at +0x14),
// then ID word at +0x10 == id and player dword at +0xC == zero-extended player byte.
// Returns the wrapping node (edi) on match, else NULL. Donor is BFME1 NetCommandList.cpp
// 2-arg findMessage plus the frame check from native_connection_timing's 3-arg decl.
// Caller at 0x004D087E passes (commandID word, playerID byte, timestamp dword) and
// removes+deletes the result.
NetCommandRef *NetCommandList::findMessage(UnsignedShort id, UnsignedByte player, UnsignedInt frame)
{
	NetCommandNode *retval = m_first;
	while (retval != 0)
	{
		NetCommandMsg *msg = retval->m_msg;
		if (msg != 0 && msg->m_timestamp == frame &&
			(UnsignedByte)DoesCommandRequireACommandID(msg->m_commandType) &&
			msg->m_id == id && msg->m_playerID == player)
		{
			return (NetCommandRef *)retval;
		}
		retval = retval->m_next;
	}
	return 0;
}

// ?findMessage@NetCommandList@@QAEPAVNetCommandRef@@PAVNetCommandMsg@@@Z
// retail 0x0058B4E2, 45 bytes: Zero Hour's NetCommandList::findMessage
// (NetCommandMsg *), the first node whose command isEqualCommandMsg
// (0x0058B174) says matches; BFME 2 returns from inside the loop.
NetCommandRef *NetCommandList::findMessage(NetCommandMsg *msg)
{
	NetCommandRef *retval = (NetCommandRef *)m_first;
	while (retval != 0) {
		if (isEqualCommandMsg(retval->getCommand(), msg)) {
			return retval;
		}
		retval = retval->m_next;
	}
	return 0;
}

// ?appendList@NetCommandList@@QAEXPAV1@@Z, retail 0x0058B531, 54 bytes.
// Zero Hour's NetCommandList::appendList as the Open-BFME-1 donor
// game/GameEngine/Source/GameNetwork/NetCommandList.cpp (1281192f68) carries
// it; compiled /O1 the donor body places uniquely on unclaimed .text. Each
// message is re-added through addMessage (pinned at 0x0058B2C6, read from the
// retail call) and the relay byte at +0xC is copied onto the new reference.
void NetCommandList::appendList(NetCommandList *list)
{
	if (list == 0) {
		return;
	}

	// Need to do it this way because of the reference counting that needs to happen in appendMessage.
	NetCommandRef *msg = list->getFirstMessage();
	NetCommandRef *next = 0;
	while (msg != 0) {
		next = msg->getNext();
		NetCommandRef *temp = addMessage(msg->getCommand());
		if (temp != 0) {
			temp->setRelay(msg->getRelay());
		}

		msg = next;
	}
}
