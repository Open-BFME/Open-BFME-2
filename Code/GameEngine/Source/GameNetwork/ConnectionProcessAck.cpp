// cl: /DNDEBUG /MD
// platformsdk
//
// Connection::processAck(NetCommandMsg *), retail 0x0058BD7B (37 bytes),
// ported from Zero Hour's GameEngine/Source/GameNetwork/Connection.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference):
// stage-1 and both-stage acks go to processAck for their type. Retail folds
// the two typed overloads (processAck(NetAckStage1CommandMsg *) and
// processAck(NetAckBothCommandMsg *)) into the one rowed body 0x0058BD4F
// (ConnectionRva0058BD4F.cpp), so both branches call it. The command type
// is NetCommandMsg +0x14 (target evidence).

#include <windows.h>

class NetCommandRef;
enum NetCommandType
{
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1 = 1
};
class NetCommandMsg
{
public:
	NetCommandType getNetCommandType() const { return m_commandType; }
private:
	unsigned char m_pad00[0x14];
	NetCommandType m_commandType; // +0x14
};
class NetAckBothCommandMsg : public NetCommandMsg
{
};
class Connection
{
public:
	NetCommandRef *processAck(NetCommandMsg *msg);
	NetCommandRef *rva0058BD4F(void *msg);
	NetCommandRef *processAck(NetAckBothCommandMsg *msg);
};

NetCommandRef * Connection::processAck(NetCommandMsg *msg) {
	if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKSTAGE1) {
		return rva0058BD4F(msg);
	}

	if (msg->getNetCommandType() == NETCOMMANDTYPE_ACKBOTH) {
		NetAckBothCommandMsg *ackmsg = (NetAckBothCommandMsg *)msg;
		return processAck(ackmsg);
	}

	return NULL;
}

// Both branches reach the existing owner below. Keep the second overload
// distinct here: using rva0058BD4F in both branches coalesces their call sites,
// whereas retail preserves the two calls to the folded overloads.
//   0x0058BD4F reads ?rva0058BD4F@Connection@@QAEPAVNetCommandRef@@PAX@Z
#pragma comment(linker, "/alternatename:?processAck@Connection@@QAEPAVNetCommandRef@@PAVNetAckBothCommandMsg@@@Z=?rva0058BD4F@Connection@@QAEPAVNetCommandRef@@PAX@Z")
