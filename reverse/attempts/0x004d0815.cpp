// ?processAckCommand@BFMEConnectionManager@@QAEXPAX@Z
// partial score=0.9 date=2026-10-07
// BFME1 native_connection_timing donor, recompiled /Os for BFME2.
// BFME2 evidence-backed overlay adjustments: lists +0x12124/+0x12128,
// ack execution frame +0x24, timestamp +0x04, 3-arg first lookup and
// 4-arg relay lookup. This version is 308B vs retail 311B; codegen still
// differs in saved-register timing and local slots starting at +0x1A.
void BFMEConnectionManager::processAckCommand(void *command)
{
	NetCommandMsg *msg = static_cast<NetCommandMsg *>(command);
	UnsignedShort commandID;
	unsigned char originalPlayerID;
	unsigned int originalExecutionFrame;
	if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE2)
	{
		NetAckStage2CommandMsg *ack = static_cast<NetAckStage2CommandMsg *>(msg);
		commandID = ack->getCommandID();
		originalPlayerID = ack->getOriginalPlayerID();
		originalExecutionFrame = ack->getOriginalExecutionFrame();
	}
	else if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKBOTH)
	{
		NetAckBothCommandMsg *ack = static_cast<NetAckBothCommandMsg *>(msg);
		commandID = ack->getCommandID();
		originalPlayerID = ack->getOriginalPlayerID();
		originalExecutionFrame = ack->getOriginalExecutionFrame();
	}
	else
		return;

	unsigned int commandTimestamp = msg->getTimestamp();

	if (m_pendingCommands != 0)
	{
		NetCommandRef *ref = m_pendingCommands->findMessage(commandID, originalPlayerID, commandTimestamp);
		if (ref != 0)
		{
			m_pendingCommands->removeMessage(ref);
			delete ref;
		}
	}
	if (m_pendingRelays != 0)
	{
		NetCommandRef *ref = m_pendingRelays->findMessage(commandID, originalPlayerID, (NetCommandType)commandTimestamp, originalExecutionFrame);
		if (ref != 0)
		{
			unsigned char relay = ref->getRelay() & ~(1 << msg->getPlayerID());
			if (relay == 0)
			{
				m_pendingRelays->removeMessage(ref);
				NetAckStage2CommandMsg *ack = new NetAckStage2CommandMsg(ref->msg);
				reinterpret_cast<ConnectionManager *>(this)->sendLocalCommand(ack, (unsigned char)1 << ack->getOriginalPlayerID());
				delete ref;
				ack->detach();
			}
			else
				ref->relay = relay;
		}
	}
}
