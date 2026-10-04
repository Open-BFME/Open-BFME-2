// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O1
//
// ?getReadyCommands@NetCommandWrapperList@@QAEPAVNetCommandList@@XZ retail
// 0x0058C2AD (169 bytes) and the removeFromList it calls, 0x0058C1A5 (78
// bytes). Ported from the Open-BFME-1 donor game/GameEngine/Source/
// GameNetwork/NetCommandWrapperList_getReadyCommands.cpp (1281192f68; donor
// flags plus BFME 2's /O1). Compiled that way getReadyCommands places
// uniquely on unclaimed .text by masked whole-.text search
// (tools/donor_sweep.py) and its removeFromList call reads 0x0058C1A5.
// BFME 2 keeps removeFromList out of line (its only caller is
// getReadyCommands); NetCommandWrapperList.cpp's Zero Hour copies of both,
// written against the pooled NetCommandRef layout, are retired in its favour.
//
// readable body of ?getReadyCommands@NetCommandWrapperList@@QAEPAVNetCommandList@@XZ: game/GameEngine/Source/GameNetwork/NetCommandWrapperList.cpp

// NetCommandWrapperList::getReadyCommands, 0x00676890, 256 bytes.
//
// Split out of NetCommandWrapperList.cpp because it needs BFME's de-pooled
// NetCommandRef -- the command at +0x00 and the relay at +0x0C rather than the
// reference's +0x04 and +0x10 -- and because the reference's deleteInstance()
// is a virtual call where retail emits a destructor plus operator delete.
//
// Two BFME differences from the reference: the fresh list is reset() rather
// than init()ed, and removeFromList is inlined rather than called, so its body
// appears here as well as at 0x006766D0.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#define NULL 0

void __cdecl operator delete(void *block) throw();

class NetCommandMsg;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	~NetCommandRef();

	NetCommandMsg *getCommand() { return m_msg; }
	UnsignedByte getRelay() { return m_relay; }
	void setRelay(UnsignedByte relay) { m_relay = relay; }

	NetCommandMsg *m_msg;							// this+0x00
	NetCommandRef *m_next;							// this+0x04
	NetCommandRef *m_prev;							// this+0x08
	UnsignedByte m_relay;							// this+0x0C
	UnsignedInt m_timeLastSent;						// this+0x10
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandList.h
class NetCommandList
{
public:
	NetCommandList();
	void reset();
	NetCommandRef *addMessage(NetCommandMsg *msg);

	void *m_vptr;
	NetCommandRef *m_first;							// this+0x04
	NetCommandRef *m_last;							// this+0x08
	NetCommandRef *m_lastMessageInserted;			// this+0x0C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
public:
	static NetCommandRef *ConstructNetCommandMsgFromRawData(UnsignedByte *data, UnsignedShort dataLength);
};

class NetWrapperCommandMsg;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandWrapperList.h
class NetCommandWrapperListNode
{
public:
	virtual ~NetCommandWrapperListNode();

	Bool isComplete() { return m_numChunksPresent == m_numChunks; }
	UnsignedShort getCommandID() { return m_commandID; }
	UnsignedInt getRawDataLength() { return m_dataLength; }
	UnsignedByte *getRawData() { return m_data; }

	NetCommandWrapperListNode *m_next;				// this+0x04
	UnsignedShort m_commandID;						// this+0x08
	UnsignedByte *m_data;							// this+0x0C
	UnsignedInt m_dataLength;						// this+0x10
	Bool *m_chunksPresent;							// this+0x14
	UnsignedInt m_numChunks;						// this+0x18
	UnsignedInt m_numChunksPresent;					// this+0x1C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandWrapperList.h
class NetCommandWrapperList
{
public:
	NetCommandList *getReadyCommands();

protected:
	void removeFromList(NetCommandWrapperListNode *node);

	void *m_vptr;
	NetCommandWrapperListNode *m_list;				// this+0x04
};

// BFME 2 keeps this out of line at 0x0058C1A5. It frees the node with a
// global delete: the virtual destructor is called with flag 0 and the
// pointer it returns goes to ::operator delete (0x0002FD60).
void NetCommandWrapperList::removeFromList(NetCommandWrapperListNode *node) {
	if (node == NULL) {
		return;
	}

	NetCommandWrapperListNode *temp = m_list;
	NetCommandWrapperListNode *prev = NULL;

	while ((temp != NULL) && (temp->getCommandID() != node->getCommandID())) {
		prev = temp;
		temp = temp->m_next;
	}

	if (temp == NULL) {
		return;
	}

	if (prev == NULL) {
		m_list = temp->m_next;
		::delete temp;
		temp = NULL;
	} else {
		prev->m_next = temp->m_next;
		::delete temp;
		temp = NULL;
	}
}

NetCommandList *NetCommandWrapperList::getReadyCommands()
{
	NetCommandList *retlist = new NetCommandList;
	retlist->reset();

	NetCommandWrapperListNode *temp = m_list;
	NetCommandWrapperListNode *next = NULL;

	while (temp != NULL) {
		next = temp->m_next;
		if (temp->isComplete()) {
			NetCommandRef *msg = NetPacket::ConstructNetCommandMsgFromRawData(temp->getRawData(), temp->getRawDataLength());
			if (msg != NULL) {
				NetCommandRef *ret = retlist->addMessage(msg->getCommand());
				ret->setRelay(msg->getRelay());

				delete msg;
				msg = NULL;
			}

			removeFromList(temp);
			temp = NULL;
		}
		temp = next;
	}

	return retlist;
}
