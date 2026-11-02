// ConnectionManager: canonical BFME2 declaration.
// Target facts (addresses are RVAs unless marked VA): caller 0x004D3BA2 calls 0x004CEF58 with one integer argument and tests AL at 0x004D3BA7; reverse/symbols.csv binds the compatibility spelling _bfme_slotIsLocalOrLive to that address. This spelling does not assert the original method name.
// Constructor 0x004D274B stores VA 0x00C601C0 at +0 (store 0x004D276D); destructor 0x004D2344 stores the same VA at 0x004D2359. No base constructor or base destructor is called. The four table words at RVA 0x008601C0 are 0x004D24A2 (init), 0x004D0669 (reset), 0x004CF032 (unnamed slot), and 0x004D342A (update(bool,int)); RVA 0x008601D0 starts "NULLGAME". The destructor is nonvirtual and declared out of line. Allocation in 0x0025DF01 passes 0x121B0 to operator new before calling 0x004D274B and then init through slot 0. Constructor 0x004D2758..0x004D2773 builds nine 0x2000-byte histories at +0x24 through constructor 0x004D13EA. Its stores 0x004D2778..0x004D2840 establish connections[8] at +4, transport +0x12024, local slot +0x12028, router +0x1202C, fallback[8] +0x12030, an address dword/word at +0x12050/+0x12054, a string word +0x12058, five eight-dword arrays at +0x12060..+0x120E0, pointer +0x12100, frameData[8] +0x12104, list pointers +0x12124/+0x12128/+0x1212C, dword +0x12130 and bytes +0x12134/+0x12135. getPlayerName 0x004D0198 copies the +0x12058 member through wide StringBase copy 0x00037050; destructor 0x004D2488..0x004D248E releases it through wide releaseBuffer 0x00036E70. Constructor 0x004D279F..0x004D2806 and destructor 0x004D241A..0x004D2484 place 12-byte containers at +0x12138 and +0x12144 and eight 12-byte containers at +0x12150; their template identities remain opaque here. getLocalPlayerID 0x004CF906 and getPacketRouterSlot 0x004CF3B2 read +0x12028/+0x1202C. Method spellings and signatures below come from reverse/functions.csv; Zero Hour ConnectionManager.h supplies the connection, transport, slot, fallback, frame-data and command-list member names, with offsets established by these retail bodies. Unnamed fields retain offset placeholders.

#pragma once
#ifndef __BFME2_CONNECTIONMANAGER_H_
#define __BFME2_CONNECTIONMANAGER_H_

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"

class Connection;
class Transport;
class DisconnectManager;
class FrameDataManager;
class GameInfo;
class GameMessage;
class CreateAHeroData;
class NetCommandMsg;
class NetCommandRef;
class NetCommandList;
class NetCommandWrapperList;
class NetProgressCommandMsg;
class NetWrapperCommandMsg;
class NetDisconnectChatCommandMsg;
class NetChatCommandMsg;
class NetFileAnnounceCommandMsg;
class NetFileProgressCommandMsg;
class NetFileCommandMsg;
struct BfmeNetAddress;
enum PlayerLeaveCode;

class ConnectionManager
{
public:
    ConnectionManager();
    ~ConnectionManager();
    virtual void init();
    virtual void reset();
    virtual void vslot02();
    virtual void update(bool isInGame, int frameAdvanced);

    unsigned int getLocalPlayerID();
    unsigned int getPacketRouterSlot();
    UnicodeString getPlayerName(int playerID);
    int getNumPlayers();
    bool isPlayerConnected(int playerID);
    bool _bfme_slotIsLocalOrLive(int playerID);
    bool areAllQueuesEmpty();
    bool IsFrameAcked(unsigned int frame);
    bool rva004CF3E1();
    void disconnectLocalPlayer();
    PlayerLeaveCode disconnectPlayer(int slot);
    PlayerLeaveCode processPlayerLeave(unsigned char playerID);
    void voteForPlayerDisconnect(int slot);
    void requestLeave(int value);
    void resendPendingCommands();
    void parseUserList(const GameInfo *game);
    void initTransport();
    void setFrameGrouping(unsigned int frameGrouping);
    void updateLoadProgress(int progress);
    void loadProgressComplete();
    void sendFrameDataToPlayer(unsigned int playerID, unsigned int startingFrame);
    NetCommandList *getFrameCommandList(unsigned int frame);
    void sendLocalGameMessage(GameMessage *msg);
    void sendLocalCommand(NetCommandMsg *msg, unsigned char relay = 0xFF);
    void sendLocalCommandDirect(NetCommandMsg *msg, unsigned char relay);
    void sendChat(UnicodeString text, int playerMask);
    void sendDisconnectChat(UnicodeString text);
    void sendFile(AsciiString path, unsigned char playerMask, unsigned short commandID);
    unsigned short sendFileAnnounce(AsciiString path, unsigned char playerMask);
    int getFileTransferProgress(int playerID, AsciiString path);
    void sendHero(CreateAHeroData *hero, int seed, unsigned short slot, unsigned char playerMask);
    void processHero(NetCommandMsg *command);
    void rva004CF35D(NetWrapperCommandMsg *msg);
    void rva004D0A0A();
    void rva004D0E8B();
    void doRelay();
    void rva004D316A(NetCommandList *list, const BfmeNetAddress *source);

private:
    void ackCommand(NetCommandRef *ref, const BfmeNetAddress *source);
    bool processNetCommand(NetCommandRef *ref);
    void processProgress(NetProgressCommandMsg *msg);
    void processDisconnectChat(NetDisconnectChatCommandMsg *msg);
    void processChat(NetChatCommandMsg *msg);
    void processWrapper(NetCommandRef *ref);
    void processFile(NetFileCommandMsg *msg);
    void processFileAnnounce(NetFileAnnounceCommandMsg *msg);
    void processFileProgress(NetFileProgressCommandMsg *msg);

public:
    Connection *m_connections[8];
    char m_pad00024[0x12000];
    Transport *m_transport;
    unsigned int m_localSlot;
    unsigned int m_packetRouterSlot;
    int m_packetRouterFallback[8];
    unsigned int field12050;
    unsigned short field12054;
    char m_pad12056[2];
    UnicodeString m_localPlayerName;
    unsigned int field1205C;
    unsigned int field12060[8];
    int field12080[8];
    unsigned int field120A0[8];
    unsigned int field120C0[8];
    unsigned int field120E0[8];
    DisconnectManager *m_disconnectManager;
    FrameDataManager *m_frameData[8];
    NetCommandList *m_pendingCommands;
    NetCommandList *m_relayedCommands;
    NetCommandWrapperList *m_netCommandWrapperList;
    unsigned int field12130;
    bool field12134;
    bool field12135;
    char m_pad12136[2];
    char m_pad12138[0x78];
};

#endif
