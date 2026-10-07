// ?getCommandList@NetPacket@@QAEPAVNetCommandList@@XZ
// partial score=0.9 date=2026-10-07
// Banked partial: NetPacket::getCommandList 0x00593F15 (1351 B), continue-shape form, 387 masked byte diffs.
// Apply to Code/GameEngine/Source/GameNetwork/NetPacket.cpp; declaration additions vs the committed file:
// 	void setTiming(UnsignedInt timestamp, UnsignedInt frame) { m_timestamp = timestamp; m_executionFrame = frame; }
// 	void setPlayerID(UnsignedInt playerID) { m_playerID = playerID; }
// 	void setID(UnsignedShort id) { m_id = id; }
// 	void setNetCommandType(Int type) { m_commandType = type; }
// 	void detach();
// class NetCommandList
// {
// public:
// 	NetCommandList();
// 	void reset();
// 	NetCommandRef *addMessage(NetCommandMsg *msg);
// private:
// 	char m_pad[0x10];
// };
// 
// enum NetCommandType;
// Bool DoesCommandRequireACommandID(NetCommandType type);
// 
// // The +0x1E byte getter getCommandList's ack repeats read.
// class Rva004543C6ByteField
// {
// public:
// 	UnsignedByte get() const;
// };
// 
// // Readers rowed as free functions under their address names.
// class Rva004D64F5;
// class Rva004D65DC;
// class Rva004D6208;
// class Rva004D62A9;
// Rva004D64F5 *Rva00592496Read(Int data, UnsignedInt *readOffset);
// Rva004D65DC *Rva00592520Read(Int data, UnsignedInt *readOffset);
// Rva004D6208 *Rva005922FBRead(Int data, UnsignedInt *readOffset);
// Rva004D62A9 *Rva005923C5Read(Int data, UnsignedInt *readOffset);
// 
// 	NetCommandList *getCommandList();
// 	// ICF twin: type 17's reader keeps its own call block to the type-16 body.
// 	static NetCommandMsg *rva0058E0B0TimeOutStart(UnsignedByte *data, Int &readOffset);
// 	static NetCommandMsg *readWrapperMessage(UnsignedByte *data, Int &i);
// 	void rva004D59ACSetCommandID(UnsignedShort commandID);
// 	void rva004D576CSetOriginalPlayerID(UnsignedByte playerID);
// 	UnsignedShort getCommandID();
// 	UnsignedByte getOriginalPlayerID();
// 	UnsignedShort getCommandID();
// 	UnsignedByte getOriginalPlayerID();
// 	// ICF twins of the 0x004D59AC/0x004D576C slot setters; getCommandList's
// 	// per-class repeat arms keep their own call sites.
// 	void rva004D59ACSetCommandID(UnsignedShort commandID);
// 	void rva004D576CSetOriginalPlayerID(UnsignedByte playerID);
// 
// // ?getCommandList@NetPacket@@QAEPAVNetCommandList@@XZ, retail 0x00593F15, 1351 bytes
// // (its jump table follows at 0x0059445C): the BFME1 donor's getCommandList
// // (NetPacket.cpp) with BFME's changes read off the image. An S field carries
// // the timestamp; the command ID is a dword that a C field sets for the next
// // command only, otherwise it advances before use; a message that does not
// // read, an unknown type or a Z repeat with nothing to repeat ends the parse;
// // Z repeats only acks and copies their +0x20/+0x24 values; an unrecognised
// // entry dumps the packet (rva0058E57B). Reader arms follow retail's order.

NetCommandList *NetPacket::getCommandList()
{
	NetCommandList *retval = new NetCommandList();
	retval->reset();

	UnsignedByte commandType = 0;
	UnsignedInt frame = 0;
	UnsignedInt timestamp = 0;
	UnsignedByte playerID = 0;
	UnsignedByte relay = 0;
	UnsignedInt commandID = 0;
	NetCommandRef *lastCommand = 0;
	Bool commandIDSet = false;
	Int offset;

	Int i = 0;
	while (i < m_packetLen) {
		if (m_packet[i] == 'T') {
			++i;
			memcpy(&commandType, m_packet + i, sizeof(UnsignedByte));
			i += sizeof(UnsignedByte);
			continue;
		} else if (m_packet[i] == 'S') {
			++i;
			memcpy(&timestamp, m_packet + i, sizeof(UnsignedInt));
			i += sizeof(UnsignedInt);
			continue;
		} else if (m_packet[i] == 'F') {
			++i;
			memcpy(&frame, m_packet + i, sizeof(UnsignedInt));
			i += sizeof(UnsignedInt);
			continue;
		} else if (m_packet[i] == 'P') {
			++i;
			memcpy(&playerID, m_packet + i, sizeof(UnsignedByte));
			i += sizeof(UnsignedByte);
			continue;
		} else if (m_packet[i] == 'R') {
			++i;
			memcpy(&relay, m_packet + i, sizeof(UnsignedByte));
			i += sizeof(UnsignedByte);
			continue;
		} else if (m_packet[i] == 'C') {
			++i;
			memcpy(&commandID, m_packet + i, sizeof(UnsignedShort));
			i += sizeof(UnsignedShort);
			commandIDSet = true;
			continue;
		} else if (m_packet[i] == 'D') {
			++i;
			offset = i;

			NetCommandMsg *msg = 0;
			switch (commandType) {
			case 4:
				msg = rva00591EA6(m_packet, offset);
				break;
			case 0:
				msg = rva0058DA7E(m_packet, offset);
				break;
			case 1:
				msg = rva0058DB4D(m_packet, offset);
				break;
			case 2:
				msg = rva0058DC1C(m_packet, offset);
				break;
			case 3:
				msg = rva0058DCEB(m_packet, offset);
				break;
			case 23:
				msg = rva0058DD89(m_packet, offset);
				break;
			case 10:
				msg = rva0058DDF2(m_packet, offset);
				break;
			case 11:
				msg = rva0058DE5B(m_packet, offset);
				break;
			case 12:
				msg = rva0058DEC5(m_packet, offset);
				break;
			case 25:
				msg = rva0058DEF7(m_packet, offset);
				break;
			case 26:
				msg = rva0058DF29(m_packet, offset);
				break;
			case 13:
				msg = rva0059205C(m_packet, offset);
				break;
			case 27:
				msg = rva0058DFB8(m_packet, offset);
				break;
			case 14:
				msg = rva00592123(m_packet, offset);
				break;
			case 15:
				msg = rva0058E047(m_packet, offset);
				break;
			case 16:
				msg = rva0058E0B0(m_packet, offset);
				break;
			case 17:
				msg = rva0058E0B0TimeOutStart(m_packet, offset);
				break;
			case 18:
				msg = readWrapperMessage(m_packet, offset);
				break;
			case 20:
				msg = rva0058E20D(m_packet, offset);
				break;
			case 19:
				msg = (NetCommandMsg *)Rva005922FBRead((Int)m_packet, (UnsignedInt *)&offset);
				break;
			case 21:
				msg = (NetCommandMsg *)Rva005923C5Read((Int)m_packet, (UnsignedInt *)&offset);
				break;
			case 22:
				msg = rva0058E2D7(m_packet, offset);
				break;
			case 8:
				msg = rva0058E367(m_packet, offset);
				break;
			case 7:
				msg = rva0058E3F4(m_packet, offset);
				break;
			case 9:
				msg = rva0058E481(m_packet, offset);
				break;
			case 28:
				msg = rva0058E511(m_packet, offset);
				break;
			case 5:
				msg = (NetCommandMsg *)Rva00592496Read((Int)m_packet, (UnsignedInt *)&offset);
				break;
			case 6:
				msg = (NetCommandMsg *)Rva00592520Read((Int)m_packet, (UnsignedInt *)&offset);
				break;
			case 30:
				msg = rva00592208(m_packet, offset);
				break;
			}

			if (msg == 0) {
				break;
			}

			msg->setTiming(timestamp, frame);
			msg->setPlayerID(playerID);
			msg->setNetCommandType(commandType);
			if (DoesCommandRequireACommandID((NetCommandType)commandType)) {
				if (!commandIDSet) {
					++commandID;
				}
				msg->setID((UnsignedShort)commandID);
			}
			commandIDSet = false;

			NetCommandRef *ref = retval->addMessage(msg);
			if (ref != 0) {
				ref->setRelay(relay);
			}

			if (lastCommand != 0) {
				delete lastCommand;
			}
			lastCommand = new NetCommandRef(msg);

			msg->detach();
		} else if (m_packet[i] == 'Z') {
			++i;
			offset = i;
			if (lastCommand == 0) {
				break;
			}
			NetCommandMsg *msg = 0;
			if (commandType == 1) {
				msg = (NetCommandMsg *)new NetAckStage1CommandMsg();
				NetAckStage1CommandMsg *last = (NetAckStage1CommandMsg *)lastCommand->getCommand();
				((Rva004D59ACWordSlot *)msg)->set(last->getCommandID() + 1);
				((Rva004D576CByteSlot *)msg)->set(last->getOriginalPlayerID());
				((NetAckStage1CommandMsg *)msg)->m_20 = last->m_20;
				((NetAckStage1CommandMsg *)msg)->m_24 = last->m_24;
			} else if (commandType == 2) {
				msg = (NetCommandMsg *)new NetAckStage2CommandMsg();
				NetAckStage2CommandMsg *last = (NetAckStage2CommandMsg *)lastCommand->getCommand();
				((NetAckStage2CommandMsg *)msg)->rva004D59ACSetCommandID(last->getCommandID() + 1);
				((NetAckStage2CommandMsg *)msg)->rva004D576CSetOriginalPlayerID(last->getOriginalPlayerID());
				((NetAckStage2CommandMsg *)msg)->m_20 = last->m_20;
				((NetAckStage2CommandMsg *)msg)->m_24 = last->m_24;
			} else if (commandType == 0) {
				msg = (NetCommandMsg *)new NetAckBothCommandMsg();
				NetAckBothCommandMsg *last = (NetAckBothCommandMsg *)lastCommand->getCommand();
				((NetAckBothCommandMsg *)msg)->rva004D59ACSetCommandID(last->getCommandID() + 1);
				((NetAckBothCommandMsg *)msg)->rva004D576CSetOriginalPlayerID(last->getOriginalPlayerID());
				((NetAckBothCommandMsg *)msg)->m_20 = last->m_20;
				((NetAckBothCommandMsg *)msg)->m_24 = last->m_24;
			} else {
				break;
			}

			msg->setTiming(timestamp, frame);
			msg->setPlayerID(playerID);
			msg->setNetCommandType(commandType);
			if (DoesCommandRequireACommandID((NetCommandType)commandType)) {
				if (!commandIDSet) {
					++commandID;
				}
				msg->setID((UnsignedShort)commandID);
			}
			commandIDSet = false;

			NetCommandRef *ref = retval->addMessage(msg);
			if (ref != 0) {
				ref->setRelay(relay);
			}

			delete lastCommand;
			lastCommand = new NetCommandRef(msg);

			msg->detach();
		} else {
			rva0058E57B();
			++i;
			continue;
		}
		i = offset;
	}

	if (lastCommand != 0) {
		delete lastCommand;
	}
	return retval;
}
