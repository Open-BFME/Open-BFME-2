// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?DoesCommandRequireACommandID@@YAHW4NetCommandType@@@Z, retail 0x005811B5, 116 bytes.
// BFME2's DoesCommandRequireACommandID: takes NetCommandType by value (mov eax,[esp+4]),
// returns Int (xor eax,eax / inc eax, whole register, not Bool). Identity proven by
// 30+ callers (0x004CF890, 0x004CFDE1, 0x004D0445 and 27 unblocked) that push
// [esi+0x14] (NetCommandMsg m_commandType) and test al, then call GenerateNextCommandID
// at 0x005811A8 and store ax into [esi+0x10] (m_id) -- the ZH/BFME1
// if (DoesCommandRequireACommandID(type)) setID(GenerateNextCommandID()) pattern.
// Donor is BFME1 Code/GameEngine/Source/GameNetwork/NetworkUtil.cpp
// (DoesCommandRequireACommandID, same Int return); BFME2's list has 21 types in
// retail order read off the chain: 4,5,6,3,10,8,9,7,11,14,27,16,17,18,20,19,21,22,26,28,30
// (FILEANNOUNCE before FILE, DISCONNECTFRAME early, 22 unnamed and 30 MAX added,
// DISCONNECTPLAYER 25 dropped vs BFME1's 20).
typedef int Int;
enum NetCommandType
{
	NETCOMMANDTYPE_FRAMEINFO = 3,
	NETCOMMANDTYPE_GAMECOMMAND = 4,
	NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY = 5,
	NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY = 6,
	NETCOMMANDTYPE_REQUESTPLAYERLEAVE = 7,
	NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME = 8,
	NETCOMMANDTYPE_REQUESTFRAMEDATA = 9,
	NETCOMMANDTYPE_PLAYERLEAVE = 10,
	NETCOMMANDTYPE_DESTROYPLAYER = 11,
	NETCOMMANDTYPE_CHAT = 14,
	NETCOMMANDTYPE_LOADCOMPLETE = 16,
	NETCOMMANDTYPE_TIMEOUTSTART = 17,
	NETCOMMANDTYPE_WRAPPER = 18,
	NETCOMMANDTYPE_FILE = 19,
	NETCOMMANDTYPE_FILEANNOUNCE = 20,
	NETCOMMANDTYPE_FILEPROGRESS = 21,
	NETCOMMANDTYPE_DISCONNECTVOTE = 26,
	NETCOMMANDTYPE_DISCONNECTFRAME = 27,
	NETCOMMANDTYPE_DISCONNECTSCREENOFF = 28
};
Int DoesCommandRequireACommandID(NetCommandType type)
{
	if ((type == NETCOMMANDTYPE_GAMECOMMAND) ||
		(type == NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY) ||
		(type == NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY) ||
		(type == NETCOMMANDTYPE_FRAMEINFO) ||
		(type == NETCOMMANDTYPE_PLAYERLEAVE) ||
		(type == NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME) ||
		(type == NETCOMMANDTYPE_REQUESTFRAMEDATA) ||
		(type == NETCOMMANDTYPE_REQUESTPLAYERLEAVE) ||
		(type == NETCOMMANDTYPE_DESTROYPLAYER) ||
		(type == NETCOMMANDTYPE_CHAT) ||
		(type == NETCOMMANDTYPE_DISCONNECTFRAME) ||
		(type == NETCOMMANDTYPE_LOADCOMPLETE) ||
		(type == NETCOMMANDTYPE_TIMEOUTSTART) ||
		(type == NETCOMMANDTYPE_WRAPPER) ||
		(type == NETCOMMANDTYPE_FILEANNOUNCE) ||
		(type == NETCOMMANDTYPE_FILE) ||
		(type == NETCOMMANDTYPE_FILEPROGRESS) ||
		(type == (NetCommandType)22) ||
		(type == NETCOMMANDTYPE_DISCONNECTVOTE) ||
		(type == NETCOMMANDTYPE_DISCONNECTSCREENOFF) ||
		(type == (NetCommandType)30))
	{
		return 1;
	}
	return 0;
}

// ?IsCommandSynchronized@@YAHW4NetCommandType@@@Z, retail 0x005812A0, 36 bytes.
// BFME2's IsCommandSynchronized: same Int whole-register shape (xor eax,eax / inc eax)
// as DoesCommandRequireACommandID above. Identity from 2 callers (0x004CF5F5,
// 0x004CF733) pushing [esi+0x14] (m_commandType) and testing al, matching ZH
// ConnectionManager::sendLocalCommand's if (IsCommandSynchronized(type)) use.
// Donor BFME1 NetworkUtil_CommandRequiresAck.cpp has 4 types in this order;
// BFME2 adds (NetCommandType)30 at the end, read off the chain: 4,3,10,11,30.
Int IsCommandSynchronized(NetCommandType type)
{
	if ((type == NETCOMMANDTYPE_GAMECOMMAND) ||
		(type == NETCOMMANDTYPE_FRAMEINFO) ||
		(type == NETCOMMANDTYPE_PLAYERLEAVE) ||
		(type == NETCOMMANDTYPE_DESTROYPLAYER) ||
		(type == (NetCommandType)30))
	{
		return 1;
	}
	return 0;
}

// ?Rva00581229Get@@YAHPAURva00581229Msg@@@Z, retail 0x00581229, 119 bytes.
// Predicate over NetCommandMsg m_commandType at +0x14, same Int xor/inc shape
// as siblings above. Retail order read off the chain: 4,5,6,3,10,8,9,7,11,14,
// 27,26,16,17,18,20,19,21,22,28,30 (26 early vs DoesCommandRequireACommandID).
// Callers at 0x004D31C3 0x0058BC59 0x005DA634; honest-address free function.
struct Rva00581229Msg
{
	char m_pad[0x14];
	NetCommandType m_type;
};

Int Rva00581229Get(Rva00581229Msg *msg)
{
	NetCommandType type = msg->m_type;
	if ((type == NETCOMMANDTYPE_GAMECOMMAND) ||
		(type == NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY) ||
		(type == NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY) ||
		(type == NETCOMMANDTYPE_FRAMEINFO) ||
		(type == NETCOMMANDTYPE_PLAYERLEAVE) ||
		(type == NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME) ||
		(type == NETCOMMANDTYPE_REQUESTFRAMEDATA) ||
		(type == NETCOMMANDTYPE_REQUESTPLAYERLEAVE) ||
		(type == NETCOMMANDTYPE_DESTROYPLAYER) ||
		(type == NETCOMMANDTYPE_CHAT) ||
		(type == NETCOMMANDTYPE_DISCONNECTFRAME) ||
		(type == NETCOMMANDTYPE_DISCONNECTVOTE) ||
		(type == NETCOMMANDTYPE_LOADCOMPLETE) ||
		(type == NETCOMMANDTYPE_TIMEOUTSTART) ||
		(type == NETCOMMANDTYPE_WRAPPER) ||
		(type == NETCOMMANDTYPE_FILEANNOUNCE) ||
		(type == NETCOMMANDTYPE_FILE) ||
		(type == NETCOMMANDTYPE_FILEPROGRESS) ||
		(type == (NetCommandType)22) ||
		(type == NETCOMMANDTYPE_DISCONNECTSCREENOFF) ||
		(type == (NetCommandType)30))
	{
		return 1;
	}
	return 0;
}

// ?CommandRequiresDirectSend@@YA_NPAVNetCommandMsg@@@Z, retail 0x005812C4, 84 bytes.
// Zero Hour's CommandRequiresDirectSend (NetworkUtil.cpp): the same test over
// NetCommandMsg m_commandType at +0x14, called at ConnectionManager::ackCommand's
// direct-send test (0x004CF4A8) and at sendLocalCommand's (0x004CFF2D), Zero
// Hour's two call sites. Both callers test al: the return is Bool, and returning
// the || chain (not TRUE/FALSE) gives the whole-register xor/inc tail. Retail
// order read off the chain: 27,26,16,17,20,19,21,22,28,5,6,8,9,7 -- Zero Hour's
// DISCONNECTVOTE, DISCONNECTPLAYER, LOADCOMPLETE, TIMEOUTSTART, FILE...,
// DISCONNECTFRAME order with BFME 2's renumbered types, hero data (20) and the
// GameSpy-key, leave-frame, frame-data and player-leave requests added.
// Rowed before as the address-named ?Rva005812C4Get@@YAHPAURva005812C4Msg@@@Z.
class NetCommandMsg
{
public:
	NetCommandType getNetCommandType() const { return m_commandType; }

private:
	char m_pad[0x14];
	NetCommandType m_commandType;
};

bool CommandRequiresDirectSend(NetCommandMsg *msg)
{
	return ((msg->getNetCommandType() == NETCOMMANDTYPE_DISCONNECTFRAME) ||
		(msg->getNetCommandType() == NETCOMMANDTYPE_DISCONNECTVOTE) ||
		(msg->getNetCommandType() == NETCOMMANDTYPE_LOADCOMPLETE) ||
		(msg->getNetCommandType() == NETCOMMANDTYPE_TIMEOUTSTART) ||
		(msg->getNetCommandType() == NETCOMMANDTYPE_FILEANNOUNCE) ||
		(msg->getNetCommandType() == NETCOMMANDTYPE_FILE) ||
		(msg->getNetCommandType() == NETCOMMANDTYPE_FILEPROGRESS) ||
		(msg->getNetCommandType() == (NetCommandType)22) ||
		(msg->getNetCommandType() == NETCOMMANDTYPE_DISCONNECTSCREENOFF) ||
		(msg->getNetCommandType() == NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY) ||
		(msg->getNetCommandType() == NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY) ||
		(msg->getNetCommandType() == NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME) ||
		(msg->getNetCommandType() == NETCOMMANDTYPE_REQUESTFRAMEDATA) ||
		(msg->getNetCommandType() == NETCOMMANDTYPE_REQUESTPLAYERLEAVE));
}

// ?Rva00581318Get@@YAHPAURva00581318Msg@@@Z, retail 0x00581318, 33 bytes.
// Predicate over NetCommandMsg m_commandType at +0x14, same Int xor/inc shape
// as siblings above. Retail order read off the chain: 7,0,1,2. Caller at
// 0x004D31E5; honest-address free function.
struct Rva00581318Msg
{
	char m_pad[0x14];
	NetCommandType m_type;
};

Int Rva00581318Get(Rva00581318Msg *msg)
{
	NetCommandType type = msg->m_type;
	if ((type == NETCOMMANDTYPE_REQUESTPLAYERLEAVE) ||
		(type == (NetCommandType)0) ||
		(type == (NetCommandType)1) ||
		(type == (NetCommandType)2))
	{
		return 1;
	}
	return 0;
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?CommandRequiresAck@@YAHPAVNetCommandMsg@@@Z=?Rva00581229Get@@YAHPAURva00581229Msg@@@Z")
