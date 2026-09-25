// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// PeerResponse::operator= at 0x0038B383 (340B), called once from
// GameSpyPeerMessageQueue::getResponse (site 0x0038E000) with a pushed
// source and this in ecx. Layout follows the Zero Hour PeerThread.h
// response with BFME2 additions: one extra string ahead of the 8-name array
// (+0x7C), a vector<AsciiString> after commandOptions (+0x100, assigned
// through the rowed operator= at 0x000BDB46) and a larger trailing payload
// union (+0x10C, 572B, object size 0x348 proven by the BfmeResponseDeque840
// view in PeerThread.cpp). Narrow strings assign
// through basic_string::assign (0x00120C0), wide strings through operator=
// (0x0019DE0). The payload union alternatives are assigned one by one in
// increasing size order, which reproduces retail's overlapping same-base
// copies.

#include <string>
#include <vector>

class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

class PeerResponse
{
public:
	enum
	{
		PEERRESPONSE_LOGIN,
		PEERRESPONSE_DISCONNECT,
		PEERRESPONSE_MESSAGE,
		PEERRESPONSE_GROUPROOM,
		PEERRESPONSE_STAGINGROOM,
		PEERRESPONSE_STAGINGROOMLISTCOMPLETE,
		PEERRESPONSE_STAGINGROOMPLAYERINFO,
		PEERRESPONSE_JOINGROUPROOM,
		PEERRESPONSE_CREATESTAGINGROOM,
		PEERRESPONSE_JOINSTAGINGROOM,
		PEERRESPONSE_PLAYERJOIN,
		PEERRESPONSE_PLAYERLEFT,
		PEERRESPONSE_PLAYERCHANGEDNICK,
		PEERRESPONSE_PLAYERINFO,
		PEERRESPONSE_PLAYERCHANGEDFLAGS,
		PEERRESPONSE_ROOMUTM,
		PEERRESPONSE_PLAYERUTM,
		PEERRESPONSE_QUICKMATCHSTATUS,
		PEERRESPONSE_GAMESTART,
		PEERRESPONSE_FAILEDTOHOST,
		PEERRESPONSE_MAX
	} peerResponseType;

	_STL::string groupRoomName;
	_STL::string nick;
	_STL::string oldNick;
	_STL::wstring text;
	_STL::string locale;
	_STL::string stagingServerGameOptions;
	_STL::wstring stagingServerName;
	_STL::string stagingServerPingString;
	_STL::string stagingServerLadderIP;
	_STL::string stagingRoomMapName;
	_STL::string extraRoomString;
	_STL::string stagingRoomPlayerNames[8];
	_STL::string command;
	_STL::string commandOptions;
	_STL::vector<AsciiString> stringList;

	union Payload
	{
		int value00;
		int value01;
		struct { int words[8]; } words02;
		struct { int first; int second; } words03;
		int value04;
		struct { int words[3]; } words05;
		struct { int first; int second; } words06;
		struct { int words[143]; } words07;
		struct { int words[79]; } words08;
		struct { int words[48]; } words09;
	};

	Payload payload;

	PeerResponse &operator=(const PeerResponse &that);
};

PeerResponse &PeerResponse::operator=(const PeerResponse &that)
{
	peerResponseType = that.peerResponseType;
	groupRoomName.assign(that.groupRoomName);
	nick.assign(that.nick);
	oldNick.assign(that.oldNick);
	text = that.text;
	locale.assign(that.locale);
	stagingServerGameOptions.assign(that.stagingServerGameOptions);
	stagingServerName = that.stagingServerName;
	stagingServerPingString.assign(that.stagingServerPingString);
	stagingServerLadderIP.assign(that.stagingServerLadderIP);
	stagingRoomMapName.assign(that.stagingRoomMapName);
	extraRoomString.assign(that.extraRoomString);
	for (int i = 0; i < 8; i++)
		stagingRoomPlayerNames[i].assign(that.stagingRoomPlayerNames[i]);
	command.assign(that.command);
	commandOptions.assign(that.commandOptions);
	stringList = that.stringList;
	payload.value00 = that.payload.value00;
	payload.value01 = that.payload.value01;
	payload.words02 = that.payload.words02;
	payload.words03 = that.payload.words03;
	payload.value04 = that.payload.value04;
	payload.words05 = that.payload.words05;
	payload.words06 = that.payload.words06;
	payload.words07 = that.payload.words07;
	payload.words08 = that.payload.words08;
	payload.words09 = that.payload.words09;
	return *this;
}
