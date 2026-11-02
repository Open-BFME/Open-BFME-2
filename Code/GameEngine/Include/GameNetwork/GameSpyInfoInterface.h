// Target facts: code addresses are RVAs; table addresses are VAs. Constructor 0x00381D95 stores 0x00C19230 at +0; destructor 0x00381D71 restores it, and deleting destructor 0x00381D78 occupies slot 0. The table has 99 entries: slot 1 is the empty 0x000B3FD0, and slots 2-98 are __purecall (0x0003B810); non-code begins at 0x00C193BC. The native lifetime functions and Zero Hour's data-free root declaration support a primary vptr at +0, sizeof 4, no base and no virtual bases; the size is a structural inference. GameSpyInfo constructor 0x00385FE1 installs the implementation table 0x00C19500; its destructor 0x00386374 installs that table at 0x00386385 and restores the interface table at 0x003864BC after member teardown. Factory 0x003864CC allocates 0x1640 for the implementation, not the interface. The different tables represent base and derived destruction phases.
// Target slot facts from 0x00C19500 and its ledger bodies: 1 reset=0x00385D25; 2 clearGroupRoomList=0x003862CA; 3 getGroupRoomList=0x0036CBE7 (+0x18); 4 addGroupRoom=0x00386B7B; 5 gotGroupRoomList=0x003860EF (+0x6C); 6 joinGroupRoom=0x003853DA; 7 leaveGroupRoom=0x0038544D; 8 rva003854C5=0x003854C5; 9 joinBestGroupRoom=0x00385678; 10 joinPreferredGroupRoom=0x0038553D; 11 setCurrentGroupRoom=0x003862DB; 12 getCurrentGroupRoom=0x0008BB81 (+0x5C); 13/14 rva00386139/rva0038616D=0x00386139/0x0038616D; 17 rva003674FE=0x003674FE; 19 updatePlayerInfo=0x00386EF8; 20 playerLeftGroupRoom=0x00384660; 21 getPlayerInfoMap=0x003EFDD7 (+0x4C); 22/23 rva00382CCE/rva00382D0A=0x00382CCE/0x00382D0A; 24/25 getBuddyMap/getBuddyRequestMap=0x002B236A/0x0049CB86 (+0x34/+0x40); 26 getBuddyMessages=0x00042287 (+0x58); 27 isBuddy=0x003835D7; 28/29 setLocalName/getLocalName=0x00386188/0x003861BC; 30/31 setLocalProfileID/getLocalProfileID=0x002D94FE/0x000421C4 (+0x74); 32-37 getLocalEmail/setLocalEmail/getLocalPassword/setLocalPassword/setLocalBaseName/getLocalBaseName=0x003861D7/0x003861F2/0x00386226/0x00386241/0x00386275/0x003862AC; 38/39 setCachedLocalPlayerStats/getCachedLocalPlayerStats=0x00387479/0x003862ED (+0x84, PSPlayerAllStats copy 0x0038630B and assignment 0x003874B0); 40 clearStagingRoomList=0x00382E2F; 41 getStagingRoomList=0x00091A25 (+0x24); 42 findStagingRoomByID=0x00383846; 43 addStagingRoom=0x003857EB; 44 updateStagingRoom=0x00383784; 45 removeStagingRoom=0x003837D3; 46 hasStagingRoomListChanged=0x00381DDA; 47 leaveStagingRoom=0x003858DF; 48 markAsStagingRoomHost=0x00382623; 49 markAsStagingRoomJoiner=0x00383865; 50 sawFullGameList=0x003860FA; 51 amIHost=0x00381DBD; 52 rva00381DC4=0x00381DC4; 53 getCurrentStagingRoom=0x003835A0; 54 validateStagingRoom=0x00383207; 55 setGameOptions=0x00386501; 56 getCurrentStagingRoomID=0x003860F3; 57-60 setDisallowAsianText/setDisallowNonAsianText/getDisallowAsianText/getDisallowNonAsianText=0x00381E05/0x00381E12/0x00381E1F/0x00381E26; 61 addText=0x001EF552 (two stack arguments, ret 8); 62 slot62=0x001EF90E (caller 0x005AF3F5 through 0x005AF406 passes two byte booleans to the vcall at 0x005AF43E); 63 addChat=0x001EF9A0; 64 sendChat=0x001EFD9C (bool result and three arguments; calls at 0x0059FE2B); 65 slot65=0x001EFCF7; 66/67 setMOTD/getMOTD=0x0038200D/0x001DBA69 (+0x0C); 68/69 setConfig/getConfig=0x00382015/0x003F712F (+0x10); 70/71 setPingString/getPingString=0x0030D420/0x005C4AD9 (+0x14); 72 getPingValue=0x0038277F; 73 addToBuddyList=0x00382767; 74 removeBuddy=0x003871F6; 75-77 addToSavedIgnoreList/removeFromSavedIgnoreList/isSavedIgnored=0x00385E2A/0x00385B1C/0x003839B9; 78 returnSavedIgnoreList=0x00381DFE (+0x1614, returns its address); 79 loadSavedIgnoreList=0x00385B78; 80 returnIgnoreList=0x00385AFE; 81-83 addToIgnoreList/removeFromIgnoreList/isIgnored=0x003846A8/0x003871BF/0x003846E5; 84 setLocalIPs=0x00381D9E; 85 getInternalIP=0x0043813D (+0x5D0); 86 getInternalPort=0x003860FF (unsigned short result; 0x005A3796 calls slot 86 and 0x005A379C/0x005A37B7 store its port word beside the local IP); 87 getExternalIP=0x0028A936 (+0x5D4); 88-91 isDisconnectedAfterGameStart/markAsDisconnectedAfterGameStart/didPlayerPreorder/markPlayerAsPreorder=0x00386104/0x00386117/0x00383580/0x00383E80; 92/93 setMaxMessagesPerUpdate/getMaxMessagesPerUpdate=0x00381E2D/0x00381E3A; 94/95 getAdditionalDisconnects/clearAdditionalDisconnects=0x000D43D0/0x00381DB5; 96 readAdditionalDisconnects=0x003853C6; 97/98 slot97/slot98=0x00386125/0x0038612C (+0x163C, byte getter and setter).
// Donor facts: Zero Hour GeneralsMD GameNetwork/GameSpy/PeerDefs.h supplies the interface name, class-key, data-free root shape and the names paired above with retail operations. BFME2's ledger supplies the rva-prefixed names and its added methods. Unknown operations retain slotNN names. Container types follow the donor declarations and the matched PeerDefs.cpp operations; no donor header or scoped PeerDefs shim is included. No special member is defined here, so callers continue to use out-of-line bodies.
#pragma once

#ifndef BFME2_GAMESPYINFOINTERFACE_H
#define BFME2_GAMESPYINFOINTERFACE_H

class AsciiString;
class UnicodeString;
class GameSpyGroupRoom;
class GameSpyStagingRoom;
class PlayerInfo;
class BuddyInfo;
class BuddyMessage;
class PSPlayerAllStats;
struct AsciiComparator;
struct SelPair;

namespace _STL {
template <class T> struct less;
template <class T> class allocator;
template <class T, class U> struct pair;
template <class K, class T, class C, class A> class map;
template <class K, class C, class A> class set;
template <class T, class A> class list;
}

class GameSpyInfoInterface
{
public:
    virtual ~GameSpyInfoInterface();
    virtual void reset();
    virtual void clearGroupRoomList() = 0;
    virtual _STL::map<int, GameSpyGroupRoom, _STL::less<int>, _STL::allocator<_STL::pair<const int, GameSpyGroupRoom> > > *getGroupRoomList() = 0;
    virtual void addGroupRoom(GameSpyGroupRoom room) = 0;
    virtual bool gotGroupRoomList() = 0;
    virtual void joinGroupRoom(int groupID) = 0;
    virtual void leaveGroupRoom() = 0;
    virtual void rva003854C5() = 0;
    virtual void joinBestGroupRoom(int roomType) = 0;
    virtual void joinPreferredGroupRoom(bool flag, int roomType) = 0;
    virtual void setCurrentGroupRoom(int groupID) = 0;
    virtual int getCurrentGroupRoom() = 0;
    virtual void rva00386139(AsciiString value) = 0;
    virtual AsciiString rva0038616D() = 0;
    virtual void slot15(int value) = 0;
    virtual int slot16() = 0;
    virtual void rva003674FE(int value) = 0;
    virtual int slot18() = 0;
    virtual void updatePlayerInfo(PlayerInfo player, AsciiString oldNick) = 0;
    virtual void playerLeftGroupRoom(AsciiString nick) = 0;
    virtual _STL::map<AsciiString, PlayerInfo, AsciiComparator, _STL::allocator<_STL::pair<const AsciiString, PlayerInfo> > > *getPlayerInfoMap() = 0;
    virtual PlayerInfo *rva00382CCE(const char *name) = 0;
    virtual PlayerInfo *rva00382D0A(int profileID) = 0;
    virtual _STL::map<int, BuddyInfo, _STL::less<int>, _STL::allocator<_STL::pair<const int, BuddyInfo> > > *getBuddyMap() = 0;
    virtual _STL::map<int, BuddyInfo, _STL::less<int>, _STL::allocator<_STL::pair<const int, BuddyInfo> > > *getBuddyRequestMap() = 0;
    virtual _STL::list<BuddyMessage, _STL::allocator<BuddyMessage> > *getBuddyMessages() = 0;
    virtual bool isBuddy(int profileID) = 0;
    virtual void setLocalName(AsciiString name) = 0;
    virtual AsciiString getLocalName() = 0;
    virtual void setLocalProfileID(int profileID) = 0;
    virtual int getLocalProfileID() = 0;
    virtual AsciiString getLocalEmail() = 0;
    virtual void setLocalEmail(AsciiString email) = 0;
    virtual AsciiString getLocalPassword() = 0;
    virtual void setLocalPassword(AsciiString password) = 0;
    virtual void setLocalBaseName(AsciiString name) = 0;
    virtual AsciiString getLocalBaseName() = 0;
    virtual void setCachedLocalPlayerStats(PSPlayerAllStats stats) = 0;
    virtual PSPlayerAllStats getCachedLocalPlayerStats() = 0;
    virtual void clearStagingRoomList() = 0;
    virtual _STL::map<int, GameSpyStagingRoom *, _STL::less<int>, _STL::allocator<_STL::pair<const int, GameSpyStagingRoom *> > > *getStagingRoomList() = 0;
    virtual GameSpyStagingRoom *findStagingRoomByID(int id) = 0;
    virtual void addStagingRoom(GameSpyStagingRoom room) = 0;
    virtual void updateStagingRoom(GameSpyStagingRoom room) = 0;
    virtual void removeStagingRoom(GameSpyStagingRoom room) = 0;
    virtual bool hasStagingRoomListChanged() = 0;
    virtual void leaveStagingRoom() = 0;
    virtual void markAsStagingRoomHost() = 0;
    virtual void markAsStagingRoomJoiner(int game) = 0;
    virtual void sawFullGameList() = 0;
    virtual bool amIHost() = 0;
    virtual bool rva00381DC4() = 0;
    virtual GameSpyStagingRoom *getCurrentStagingRoom() = 0;
    virtual bool validateStagingRoom(GameSpyStagingRoom *room) = 0;
    virtual void setGameOptions() = 0;
    virtual int getCurrentStagingRoomID() = 0;
    virtual void setDisallowAsianText(bool value) = 0;
    virtual void setDisallowNonAsianText(bool value) = 0;
    virtual bool getDisallowAsianText() = 0;
    virtual bool getDisallowNonAsianText() = 0;
    virtual void addText(UnicodeString message, int color) = 0;
    virtual void slot62(AsciiString nick, int profileID, UnicodeString message, bool isPublic, bool isAction) = 0;
    virtual void addChat(PlayerInfo player, UnicodeString message, bool isPublic, bool isAction) = 0;
    virtual bool sendChat(UnicodeString message, bool isAction, const SelPair *selection) = 0;
    virtual bool slot65(UnicodeString message) = 0;
    virtual void setMOTD(const AsciiString &motd) = 0;
    virtual const AsciiString &getMOTD() = 0;
    virtual void setConfig(const AsciiString &config) = 0;
    virtual const AsciiString &getConfig() = 0;
    virtual void setPingString(const AsciiString &ping) = 0;
    virtual const AsciiString &getPingString() = 0;
    virtual int getPingValue(const AsciiString &otherPing) = 0;
    virtual void addToBuddyList(int profileID) = 0;
    virtual void removeBuddy(int profileID) = 0;
    virtual void addToSavedIgnoreList(int profileID, AsciiString nick) = 0;
    virtual void removeFromSavedIgnoreList(int profileID) = 0;
    virtual bool isSavedIgnored(int profileID) = 0;
    virtual _STL::map<int, AsciiString, _STL::less<int>, _STL::allocator<_STL::pair<const int, AsciiString> > > *returnSavedIgnoreList() = 0;
    virtual void loadSavedIgnoreList() = 0;
    virtual _STL::set<AsciiString, _STL::less<AsciiString>, _STL::allocator<AsciiString> > returnIgnoreList() = 0;
    virtual void addToIgnoreList(AsciiString nick) = 0;
    virtual void removeFromIgnoreList(AsciiString nick) = 0;
    virtual bool isIgnored(AsciiString nick) = 0;
    virtual void setLocalIPs(unsigned int internalIP, unsigned int externalIP) = 0;
    virtual unsigned int getInternalIP() = 0;
    virtual unsigned short getInternalPort() = 0;
    virtual unsigned int getExternalIP() = 0;
    virtual bool isDisconnectedAfterGameStart(int *reason) const = 0;
    virtual void markAsDisconnectedAfterGameStart(int reason) = 0;
    virtual bool didPlayerPreorder(int profileID) const = 0;
    virtual void markPlayerAsPreorder(int profileID) = 0;
    virtual void setMaxMessagesPerUpdate(int count) = 0;
    virtual int getMaxMessagesPerUpdate() = 0;
    virtual int getAdditionalDisconnects() = 0;
    virtual void clearAdditionalDisconnects() = 0;
    virtual void readAdditionalDisconnects() = 0;
    virtual unsigned char slot97() = 0;
    virtual void slot98(unsigned char value) = 0;

    static GameSpyInfoInterface *createNewGameSpyInfoInterface();
};

#endif
