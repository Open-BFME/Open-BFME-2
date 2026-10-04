// ?addMessage@NetCommandList@@QAEPAVNetCommandRef@@PAVNetCommandMsg@@@Z
// partial score=0.95 date=2026-10-04
// ?addMessage@NetCommandList@@QAEPAVNetCommandRef@@PAVNetCommandMsg@@@Z
// cl: /O1 /G6 /DNDEBUG /MD /EHsc
//
// NetCommandList::addMessage, retail 0x0058B2C6, 540 bytes. Sorted insert by
// timestamp (+4), type (+0x14), player (+0xC) and sort-number virtual (+4).
// Donors: BFME1 game/GameEngine/Source/GameNetwork/NetCommandList_addMessage.cpp
// (OR traversal, fast path, tail/head, duplicate via delete) and ZH
// GeneralsMD/Code/GameEngine/Source/GameNetwork/NetCommandList.cpp. BFME2 adds
// timestamp as first key (equality in fast path, > in inner OR, lexicographic
// timestamp-then-type for tail/head). Evidence: callers at 0x0058B54C,
// 0x005DA5D7 (FrameData::addCommand), rowed ctor 0x0058B88A, pinned
// isEqual 0x0058B174, detach/delete duplicate path.

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *block) throw();

class NetCommandMsg
{
public:
	virtual ~NetCommandMsg();
	virtual int getSortNumber();
	unsigned int getTimestamp() { return m_timestamp; }
	unsigned int getPlayerID() { return m_playerID; }
	unsigned short getID() { return m_id; }
	int getNetCommandType() { return m_commandType; }

public:
	unsigned int m_timestamp;
	unsigned int m_executionFrame;
	unsigned int m_playerID;
	unsigned short m_id;
	int m_commandType;
	int m_referenceCount;
};

class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);
	~NetCommandRef();
	NetCommandMsg *getCommand() { return m_msg; }
	NetCommandRef *getNext() { return m_next; }
	NetCommandRef *getPrev() { return m_prev; }
	void setNext(NetCommandRef *next) { m_next = next; }
	void setPrev(NetCommandRef *prev) { m_prev = prev; }

private:
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	unsigned char m_relay;
	unsigned int m_timeLastSent;
};

class NetCommandList
{
public:
	NetCommandRef *addMessage(NetCommandMsg *cmdMsg);
	bool isEqualCommandMsg(NetCommandMsg *msg1, NetCommandMsg *msg2);

private:
	void *m_vtable;
	NetCommandRef *m_first;
	NetCommandRef *m_last;
	NetCommandRef *m_lastMessageInserted;
};

// ?addMessage@NetCommandList@@QAEPAVNetCommandRef@@PAVNetCommandMsg@@@Z present-unmatched
NetCommandRef *NetCommandList::addMessage(NetCommandMsg *cmdMsg)
{
	NetCommandRef *msg = 0;
	if (cmdMsg == 0) {
		return 0;
	}

	msg = new NetCommandRef(cmdMsg);

	if (m_first == 0) {
		m_first = msg;
		m_last = msg;
		m_lastMessageInserted = msg;
		return msg;
	}

	if (m_lastMessageInserted != 0) {
		NetCommandRef *theNext = m_lastMessageInserted->getNext();
		if ((m_lastMessageInserted->getCommand()->getTimestamp() == cmdMsg->getTimestamp()) &&
			(m_lastMessageInserted->getCommand()->getNetCommandType() == cmdMsg->getNetCommandType()) &&
			(m_lastMessageInserted->getCommand()->getPlayerID() == cmdMsg->getPlayerID()) &&
			(m_lastMessageInserted->getCommand()->getID() < cmdMsg->getID()) &&
			((theNext == 0) || ((theNext->getCommand()->getTimestamp() > cmdMsg->getTimestamp()) ||
			 (theNext->getCommand()->getNetCommandType() > cmdMsg->getNetCommandType()) ||
			 (theNext->getCommand()->getPlayerID() > cmdMsg->getPlayerID()) ||
			 (theNext->getCommand()->getID() > cmdMsg->getID())))) {
			if (isEqualCommandMsg(m_lastMessageInserted->getCommand(), cmdMsg)) {
				delete msg;
				msg = 0;
				return 0;
			}

			if (theNext == 0) {
				msg->setNext(m_lastMessageInserted->getNext());
				msg->setPrev(m_lastMessageInserted);
				m_lastMessageInserted->setNext(msg);
				m_lastMessageInserted = msg;
				m_last = msg;
			} else {
				msg->setNext(m_lastMessageInserted->getNext());
				msg->setPrev(m_lastMessageInserted);
				m_lastMessageInserted->setNext(msg);
				msg->getNext()->setPrev(msg);
				m_lastMessageInserted = msg;
			}
			return msg;
		}
	}

	if ((cmdMsg->getTimestamp() > m_last->getCommand()->getTimestamp()) ||
		((cmdMsg->getTimestamp() == m_last->getCommand()->getTimestamp()) &&
		 (cmdMsg->getNetCommandType() > m_last->getCommand()->getNetCommandType()))) {
		if (isEqualCommandMsg(m_last->getCommand(), cmdMsg)) {
			delete msg;
			msg = 0;
			return 0;
		}

		msg->setPrev(m_last);
		msg->setNext(0);
		m_last->setNext(msg);
		m_last = msg;
		m_lastMessageInserted = msg;
		return msg;
	}

	if ((cmdMsg->getTimestamp() < m_first->getCommand()->getTimestamp()) ||
		((cmdMsg->getTimestamp() == m_last->getCommand()->getTimestamp()) &&
		 (cmdMsg->getNetCommandType() < m_first->getCommand()->getNetCommandType()))) {
		if (isEqualCommandMsg(m_first->getCommand(), cmdMsg)) {
			delete msg;
			msg = 0;
			return 0;
		}

		msg->setNext(m_first);
		msg->setPrev(0);
		m_first->setPrev(msg);
		m_first = msg;
		m_lastMessageInserted = msg;
		return msg;
	}

	NetCommandRef *tempmsg = m_first;
	while ((tempmsg != 0) &&
		((cmdMsg->getTimestamp() > tempmsg->getCommand()->getTimestamp()) ||
		 (cmdMsg->getNetCommandType() > tempmsg->getCommand()->getNetCommandType()) ||
		 (cmdMsg->getPlayerID() > tempmsg->getCommand()->getPlayerID()) ||
		 ((__int64)tempmsg->getCommand()->getSortNumber() < (__int64)cmdMsg->getSortNumber()))) {
		tempmsg = tempmsg->getNext();
	}

	if (tempmsg == 0) {
		if (isEqualCommandMsg(m_last->getCommand(), cmdMsg)) {
			delete msg;
			msg = 0;
			return 0;
		}

		msg->setPrev(m_last);
		msg->setNext(0);
		m_last->setNext(msg);
		m_last = msg;
		m_lastMessageInserted = msg;
		return msg;
	}

	if (tempmsg == m_first) {
		if (isEqualCommandMsg(m_first->getCommand(), cmdMsg)) {
			delete msg;
			return 0;
		}

		msg->setNext(m_first);
		msg->setPrev(0);
		m_first->setPrev(msg);
		m_first = msg;
		m_lastMessageInserted = msg;
		return msg;
	}

	if (isEqualCommandMsg(tempmsg->getCommand(), cmdMsg)) {
		delete msg;
		msg = 0;
		return 0;
	}

	msg->setNext(tempmsg);
	msg->setPrev(tempmsg->getPrev());
	msg->getPrev()->setNext(msg);
	tempmsg->setPrev(msg);
	m_lastMessageInserted = msg;

	return msg;
}
