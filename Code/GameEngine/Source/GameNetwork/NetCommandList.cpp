// ?reset@NetCommandList@@QAEXXZ
// cl: /DNDEBUG /MD
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
	NETCOMMANDTYPE_UNKNOWN = -1,
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1,
	NETCOMMANDTYPE_ACKSTAGE2
};
// Callers test only al, so BFME 2's version returns bool; the call resolves
// through the _N pin at 0x005811B5.
bool DoesCommandRequireACommandID(NetCommandType type);

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

	UnsignedInt GetTimestamp() { return m_timestamp; }
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedShort getID() { return m_id; }
	NetCommandType getNetCommandType() { return m_commandType; }
};

// The ack getters are out of line in BFME 2; retail folds the three
// classes' identical bodies onto 0x004543C6 (byte at +0x1E) and 0x004D5767
// (word at +0x1C), and isEqualCommandMsg calls them there.
class NetAckBothCommandMsg : public NetCommandMsg
{
public:
	UnsignedShort getCommandID();
	UnsignedByte getOriginalPlayerID();
};

class NetAckStage1CommandMsg : public NetCommandMsg
{
public:
	UnsignedShort getCommandID();
	UnsignedByte getOriginalPlayerID();
};

class NetAckStage2CommandMsg : public NetCommandMsg
{
public:
	UnsignedShort getCommandID();
	UnsignedByte getOriginalPlayerID();
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
	NetCommandRef *findMessage(UnsignedShort id, UnsignedByte frame, NetCommandType type, UnsignedInt timestamp);
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
			DoesCommandRequireACommandID(msg->m_commandType) &&
			msg->m_id == id && msg->m_playerID == player)
		{
			return (NetCommandRef *)retval;
		}
		retval = retval->m_next;
	}
	return 0;
}

// ?findMessage@NetCommandList@@QAEPAVNetCommandRef@@GEII@Z, retail 0x0058B121, 83 bytes.
// Four-argument match for command type/ID/player/frame; target compares the
// per-message frame at +8 last and returns the wrapping list node.
NetCommandRef *NetCommandList::findMessage(UnsignedShort id, UnsignedByte frame, NetCommandType type, UnsignedInt timestamp)
{
	NetCommandRef *retval = (NetCommandRef *)m_first;
	while (retval != 0)
	{
		struct TargetMessage
		{
			void *vtable;
			NetCommandType m_type;
			UnsignedInt m_timestamp;
			UnsignedInt m_player;
			UnsignedShort m_id;
			UnsignedShort m_pad;
			NetCommandType m_idType;
		};
		TargetMessage *msg = (TargetMessage *)retval->getCommand();
		if (msg != 0 && msg->m_type == type &&
			DoesCommandRequireACommandID(msg->m_idType) &&
			msg->m_id == id && msg->m_player == frame &&
			msg->m_timestamp == timestamp)
			return retval;
		retval = retval->getNext();
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

// ?isEqualCommandMsg@NetCommandList@@QAE_NPAVNetCommandMsg@@0@Z, retail
// 0x0058B174, 271 bytes. Zero Hour's NetCommandList::isEqualCommandMsg with
// a leading timestamp comparison (the field the 3-arg findMessage matches
// against its frame argument).
bool NetCommandList::isEqualCommandMsg(NetCommandMsg *msg1, NetCommandMsg *msg2)
{
	if (msg1->GetTimestamp() != msg2->GetTimestamp()) {
		return false;
	}

	if (DoesCommandRequireACommandID(msg1->getNetCommandType()) != DoesCommandRequireACommandID(msg2->getNetCommandType())) {
		return false;
	}

	// At this point we know that the commands both do or do not require a command id.
	// Do or do not, there is no try.
	if (DoesCommandRequireACommandID(msg1->getNetCommandType())) {
		// Are the commands from the same player?
		if (msg1->getPlayerID() != msg2->getPlayerID()) {
			return false;
		}

		// Do they have the same command ID?
		if (msg1->getID() != msg2->getID()) {
			return false;
		}
		return true;
	}

	// Are they the same type?
	if (msg1->getNetCommandType() != msg2->getNetCommandType()) {
		return false;
	}

	// Are they from the same player?
	if (msg1->getPlayerID() != msg2->getPlayerID()) {
		return false;
	}

	if (msg1->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE1) {
		NetAckStage1CommandMsg *ack1 = (NetAckStage1CommandMsg *)msg1;
		NetAckStage1CommandMsg *ack2 = (NetAckStage1CommandMsg *)msg2;

		if (ack1->getOriginalPlayerID() != ack2->getOriginalPlayerID()) {
			return false;
		}

		if (ack1->getCommandID() != ack2->getCommandID()) {
			return false;
		}
		return true;
	}

	if (msg1->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE2) {
		NetAckStage2CommandMsg *ack1 = (NetAckStage2CommandMsg *)msg1;
		NetAckStage2CommandMsg *ack2 = (NetAckStage2CommandMsg *)msg2;

		if (ack1->getOriginalPlayerID() != ack2->getOriginalPlayerID()) {
			return false;
		}

		if (ack1->getCommandID() != ack2->getCommandID()) {
			return false;
		}
		return true;
	}

	if (msg1->getNetCommandType() == NETCOMMANDTYPE_ACKBOTH) {
		NetAckBothCommandMsg *ack1 = (NetAckBothCommandMsg *)msg1;
		NetAckBothCommandMsg *ack2 = (NetAckBothCommandMsg *)msg2;

		if (ack1->getOriginalPlayerID() != ack2->getOriginalPlayerID()) {
			return false;
		}

		if (ack1->getCommandID() != ack2->getCommandID()) {
			return false;
		}
		return true;
	}

	return false;
}
