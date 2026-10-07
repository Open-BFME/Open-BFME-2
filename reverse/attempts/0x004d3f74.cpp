// ?processDisconnectVote@DisconnectManager@@IAEXPAVNetCommandMsg@@PAVConnectionManager@@@Z
// partial score=0.96 date=2026-10-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

class ConnectionManager
{
public:
	UnsignedInt getLocalPlayerID();
};

class NetCommandMsg
{
private:
	UnsignedByte m_unreconstructed_00[0x0C];
	Int m_playerID;

public:
	Int getPlayerID() const { return m_playerID; }
};

// The two target call sites use existing byte-identical accessors at these
// offsets. In this BFME2 command layout they read the vote slot (+0x1C) and
// vote frame (+0x20), respectively; the donor's NetDisconnectVoteCommandMsg
// names remain semantic guidance, not target class facts.
class NetProgressCommandMsg
{
public:
	UnsignedByte getPercentage();
};

class NetWrapperCommandMsg
{
public:
	UnsignedInt getDataLength();
};

Int Rva004D39DEGet(Int slot, Int localSlot);

class DisconnectManager
{
protected:
	bool isPlayerInGame(Int slot, ConnectionManager *conMgr);
	void applyDisconnectVote(Int slot, UnsignedInt frame, Int castingSlot,
		ConnectionManager *conMgr);
	void processDisconnectVote(NetCommandMsg *msg, ConnectionManager *conMgr);
};

// Target evidence: Ghidra boundary 0x004D3F74..0x004D3FCB (87 bytes). The
// call sequence translates msg+0x0C through 0x004D39DE using the local player
// ID, gates on 0x004D3F1B, then reads the vote slot and frame through the
// accessors at 0x004C54EC and 0x0030D377 before calling 0x004D3CD8.
// Structural/donor evidence: this is the same translated-sender check and
// apply-vote flow as Open-BFME-1 DisconnectManager::processDisconnectVote
// (checkout revision 6583b3c1ff21db4a561285717028fdafc780b7db). Target field
// meanings at +0x1C and +0x20 are inferred from the accessor bodies and call
// order; the donor type layout is not asserted as a BFME2 fact.
// ?processDisconnectVote@DisconnectManager@@IAEXPAVNetCommandMsg@@PAVConnectionManager@@@Z present-unmatched
void DisconnectManager::processDisconnectVote(NetCommandMsg *msg,
	ConnectionManager *conMgr)
{
	Int translatedSlot = Rva004D39DEGet(msg->getPlayerID(),
		conMgr->getLocalPlayerID());
	if (!isPlayerInGame(translatedSlot, conMgr))
		return;

	applyDisconnectVote(((NetProgressCommandMsg *)msg)->getPercentage(),
		((NetWrapperCommandMsg *)msg)->getDataLength(), msg->getPlayerID(), conMgr);
}
