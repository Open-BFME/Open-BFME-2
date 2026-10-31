#pragma once
// BFME2 consumed LAN interface; native C3E588/C3E680, ctor449AB8, allocator50CF54.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
class LANGameInfo;
class LANPlayer;
class LivingWorldBattle;
class Transport;
struct LANMessage;
struct BfmeNetAddress {
 bool Rva00248CBF(const BfmeNetAddress *) const;
 unsigned int ip;
 unsigned short port;
};
// The canonical SubsystemInterface exposes its data/lifetime surface only.
// This consumed interface spells out the native virtual prefix as declarations;
// it neither copies that base nor claims a new SubsystemInterface provider.
class LANAPIInterface : public SubsystemInterface {
public:
	enum ChatType
	{
		LANCHAT_NORMAL = 0,
		LANCHAT_TYPE1,
		LANCHAT_EMOTE,
		LANCHAT_SYSTEM
	};
	enum ReturnType
	{
		RET_OK = 0,
		RET_TIMEOUT,
		RET_GAME_FULL,
		RET_DUPLICATE_NAME,
		RET_CRC_MISMATCH,
		RET_SERIAL_DUPE,
		RET_GAME_STARTED,
		RET_GAME_EXISTS,
		RET_GAME_GONE,
		RET_BUSY
	};
 virtual ~LANAPIInterface();
 virtual void init() = 0; //1
 virtual bool loadIniFilesFromLegend(); //2
 virtual void postProcessLoad(); //3
 virtual bool vslot04(int); //4
 virtual bool vslot05(); //5
 virtual int vslot06(); //6
 virtual void vslot07(int); //7
 virtual void vslot08(); //8
 virtual void reset() = 0; //9
 virtual void update() = 0; //10
 virtual bool vslot11(int); //11
 virtual void vslot12(); //12
 virtual void vslot13(int); //13
	virtual void setIsActive(bool isActive) = 0;						// 14 0x00449A29
	virtual void RequestLocations(void) = 0;							// 15
	virtual void RequestGameJoin(LANGameInfo *game, const BfmeNetAddress &address) = 0;
	virtual void RequestGameJoinDirectConnect(void *data) = 0;							// 17
	virtual void RequestGameLeave(void) = 0;
	virtual void RequestAccept(bool accept) = 0;
	virtual void RequestHasMap(void) = 0;								// 20
	virtual void RequestChat(UnicodeString message, ChatType format, int target) = 0;
	virtual void RequestEnableMPSetupUI(bool enable) = 0;
	virtual void RequestGameStart(bool force) = 0;
	virtual void RequestGameStartTimer(unsigned int seconds) = 0;
	virtual void RequestGameOptions(AsciiString gameOptions, int isPublic, unsigned int ip) = 0;	// 25
	virtual void RequestGameOptionsPacked(bool isPublic, BfmeNetAddress *address) = 0;
	virtual void RequestGameCreate(UnicodeString gameName, bool isDirectConnect) = 0;
	virtual void RequestGameAnnounce(void) = 0;
	virtual void RequestSetName(UnicodeString newName) = 0;
	virtual void RequestLobbyLeave(bool forced) = 0;					// 30
	virtual void ResetGameStartTimer(void) = 0;
	virtual void OnGameList(LANGameInfo *gameList) = 0;
	virtual void rva00248E87(void) = 0;
	virtual void OnGameJoin(ReturnType ret, LANGameInfo *theGame, LANMessage *message) = 0;
	virtual void OnPlayerJoin(int slot, UnicodeString playerName) = 0;	// 35
	virtual void OnHostLeave(void) = 0;
	virtual void OnPlayerLeave(UnicodeString player) = 0;
	virtual void OnAccept(const BfmeNetAddress *address, bool status) = 0;
	virtual void OnHasMap(const BfmeNetAddress *address, bool status) = 0;
	virtual void OnChat(const UnicodeString &player, const BfmeNetAddress *address,
		const UnicodeString &message, ChatType format) = 0;			// 40
	virtual void rva00249B08(LivingWorldBattle *battle) = 0;
	virtual void OnGameStart(void) = 0;
	virtual void OnWOTRGameStart(void) = 0;
	virtual void OnGameStartTimer(int seconds) = 0;
	virtual void OnGameOptions(const BfmeNetAddress &sender, int playerSlot, AsciiString options) = 0;	// 45
	virtual bool OnGameOptionsPacked(const BfmeNetAddress &sender, int playerSlot, const void *data, int length) = 0;
	virtual void OnGameCreate(ReturnType ret) = 0;
	virtual void OnNameChange(unsigned int ip, UnicodeString newName) = 0;
	virtual LANGameInfo *LookupGame(UnicodeString gameName) = 0;
	virtual LANGameInfo *LookupGameByListOffset(int offset) = 0;		// 50
	virtual LANGameInfo *GetGameList(void)  = 0;		// 51 (folded +0x10 getter 0x001DB09D)
	virtual bool SetLocalIP(unsigned int localIP) = 0;					// 53 (overloads land in reverse order)
	virtual void SetLocalIP(AsciiString localIP) = 0;					// 52
	virtual int AmIHost(void) = 0;
	virtual UnicodeString GetMyName(void) = 0;							// 55
	virtual LANGameInfo *GetMyGame(void)  = 0;	// 56 (folded +0x44 getter 0x005C4AF9)
	virtual void fillInLANMessage(LANMessage *message) = 0;			// 57

private:
 // Native positions58/59 lack recovered callable identities.
 virtual void _bfme_lan58() = 0;
 virtual void _bfme_lan59() = 0;
public:
 virtual bool rva00449B79() = 0; //60
};

class LANAPI : public LANAPIInterface
{
public:
	LANAPI(void);
	virtual ~LANAPI(void);
	virtual void init(void);										// 1  0x00449BAA
	virtual void reset(void);										// 9  0x0044B49B
	virtual void update(void);										// 10 0x0044AAED
	virtual void setIsActive(bool isActive);						// 14 0x00449A29
	virtual void RequestLocations(void);							// 15
	virtual void RequestGameJoin(LANGameInfo *game, const BfmeNetAddress &address);
	virtual void RequestGameJoinDirectConnect(void *data);							// 17
	virtual void RequestGameLeave(void);
	virtual void RequestAccept(bool accept);
	virtual void RequestHasMap(void);								// 20
	virtual void RequestChat(UnicodeString message, ChatType format, int target);
	virtual void RequestEnableMPSetupUI(bool enable);
	virtual void RequestGameStart(bool force);
	virtual void RequestGameStartTimer(unsigned int seconds);
	virtual void RequestGameOptions(AsciiString gameOptions, int isPublic, unsigned int ip);	// 25
	virtual void RequestGameOptionsPacked(bool isPublic, BfmeNetAddress *address);
	virtual void RequestGameCreate(UnicodeString gameName, bool isDirectConnect);
	virtual void RequestGameAnnounce(void);
	virtual void RequestSetName(UnicodeString newName);
	virtual void RequestLobbyLeave(bool forced);					// 30
	virtual void ResetGameStartTimer(void);
	virtual void OnGameList(LANGameInfo *gameList);
	virtual void rva00248E87(void);
	virtual void OnGameJoin(ReturnType ret, LANGameInfo *theGame, LANMessage *message);
	virtual void OnPlayerJoin(int slot, UnicodeString playerName);	// 35
	virtual void OnHostLeave(void);
	virtual void OnPlayerLeave(UnicodeString player);
	virtual void OnAccept(const BfmeNetAddress *address, bool status);
	virtual void OnHasMap(const BfmeNetAddress *address, bool status);
	virtual void OnChat(const UnicodeString &player, const BfmeNetAddress *address,
		const UnicodeString &message, ChatType format);			// 40
	virtual void rva00249B08(LivingWorldBattle *battle);
	virtual void OnGameStart(void);
	virtual void OnWOTRGameStart(void);
	virtual void OnGameStartTimer(int seconds);
	virtual void OnGameOptions(const BfmeNetAddress &sender, int playerSlot, AsciiString options);	// 45
	virtual bool OnGameOptionsPacked(const BfmeNetAddress &sender, int playerSlot, const void *data, int length);
	virtual void OnGameCreate(ReturnType ret);
	virtual void OnNameChange(unsigned int ip, UnicodeString newName);
	virtual LANGameInfo *LookupGame(UnicodeString gameName);
	virtual LANGameInfo *LookupGameByListOffset(int offset);		// 50
	virtual LANGameInfo *GetGameList(void) { return m_games; }		// 51 (folded +0x10 getter 0x001DB09D)
	virtual bool SetLocalIP(unsigned int localIP);					// 53 (overloads land in reverse order)
	virtual void SetLocalIP(AsciiString localIP);					// 52
	virtual int AmIHost(void);
	virtual UnicodeString GetMyName(void);							// 55
	virtual LANGameInfo *GetMyGame(void) { return m_currentGame; }	// 56 (folded +0x44 getter 0x005C4AF9)
	virtual void fillInLANMessage(LANMessage *message);			// 57

private:
 virtual void _bfme_lan58();
 virtual void _bfme_lan59();
public:
 virtual bool rva00449B79(); //60
 virtual void rva00248E2F(bool); //61
private:
 virtual void _bfme_lan62(); //uncallable unknown one-argument native stub
public:
 virtual LANPlayer *LookupPlayer(const BfmeNetAddress *); //63
private:
 virtual void _bfme_lan64(); //uncallable native +48 address getter
public:
 void handleGameOptions(LANMessage *,const BfmeNetAddress *);
 void handleGameStartTimer(LANMessage *,const BfmeNetAddress *);
protected:
	LANPlayer *m_lobbyPlayers;		// +0x0C
	LANGameInfo *m_games;		// +0x10
	UnicodeString m_name;		// +0x14
	AsciiString m_userName;		// +0x18
	AsciiString m_hostName;		// +0x1C
	unsigned int m_gameStartTime;	// +0x20
	unsigned int m_gameStartSeconds;	// +0x24
	unsigned int m_pendingAction;	// +0x28
	unsigned int m_expiration;		// +0x2C
	unsigned int m_actionTimeout;	// +0x30
	BfmeNetAddress m_directConnectAddress;	// +0x34
	unsigned int m_lastResendTime;	// +0x3C
	bool m_isInLANMenu;		// +0x40
	bool m_inLobby;			// +0x41
	unsigned char m_beforeCurrentGame[0x44 - 0x42];
	LANGameInfo *m_currentGame;	// +0x44
	BfmeNetAddress m_localAddress;	// +0x48
	Transport *m_transport;		// +0x50
	unsigned int m_broadcastAddress;	// +0x54
	unsigned int m_unused58;		// +0x58
	bool m_isActive;			// +0x5C
	bool m_unused5D;			// +0x5D
};

