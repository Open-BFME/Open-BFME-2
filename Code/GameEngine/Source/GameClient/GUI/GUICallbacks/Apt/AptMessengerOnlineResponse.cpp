// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// stlport
// AptMessengerOnline::ProcessGameSpyResponse (0x005AF12F): the Apt online
// GameSpy response dispatcher, shaped after ZH WOLLobbyMenu's handlers.
// Retail and WB establish the response switch and the record offsets.
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <string>
#include <map>
#include <vector>
#include <stddef.h>
#include "string_base.h"
template <typename T> __forceinline T StringBase<T>::getCharAt(int index) const throw()
{
    return m_data ? m_data->data[index] : 0;
}
template <typename T> __forceinline void StringBase<T>::concat(T c)
{
    T text = c;
    concat(&text, 1);
}
#include "ascii_string.h"
#include "unicode_string.h"
// Suppress this TU's non-retail copy of ??R?$less@H@_STL@@QBE_NABH0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool less<int>::operator()(int const &,int const &) const; }
// Keep the inlined STLport __malloc_alloc<0>::deallocate without emitting an
// optimised out-of-line copy that would shadow retail's /Od body at 0x23A70
// (STLMallocAlloc0Deallocate.cpp).
namespace _STL { template <> __declspec(dllimport) __forceinline void _STLP_CALL __malloc_alloc<0>::deallocate(void *__p, size_t) { free((char *)__p); } }

typedef int Int;
typedef bool Bool;

struct AsciiUnicodePair
{
    AsciiString m_name;
    UnicodeString m_translatedName;
    int m_groupID, m_numWaiting, m_maxWaiting, m_numGames, m_numPlaying, m_roomType;
    AsciiUnicodePair(const AsciiUnicodePair &other);
    ~AsciiUnicodePair();
};
class GameSpyGroupRoom : public AsciiUnicodePair
{
public:
    GameSpyGroupRoom();
    ~GameSpyGroupRoom();
};
typedef std::map<int, GameSpyGroupRoom> GroupRoomMap;
class PlayerInfo
{
public:
    AsciiString m_name, m_locale, m_clan;
    int m_words[10];
};
struct AsciiComparator { bool operator()(AsciiString, AsciiString) const; };
typedef std::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;

enum SlotState { SLOT_OPEN, SLOT_CLOSED, SLOT_EASY_AI, SLOT_MED_AI, SLOT_BRUTAL_AI, SLOT_AI_5, SLOT_PLAYER };
#include "../../../../../Include/GameNetwork/GameSlotConnectInfo.h"
class GameSlot
{
public:
    virtual void v00();
    void setPlayerTemplate(int value);
    void setColor(int color) { m_color = color; }
    void setHandicap(int handicap) { m_handicap = handicap; }
    void setState(SlotState state, UnicodeString name = UnicodeString::TheEmptyString, const GameSlotConnectInfo *connect = &GameSlotConnectInfo());
    char m_04[8];
    int m_color;
    char m_10[0x10];
    int m_handicap;
    char m_24[0x1ac - 0x24];
};
class GameSpyGameSlot : public GameSlot
{
public:
    int m_profileID;
    char m_1b0[0x10];
    int m_wins, m_losses;
    char m_1c8[0x18];
    void setProfileID(int id) { m_profileID = id; }
    void setWins(int wins) { m_wins = wins; }
    void setLosses(int losses) { m_losses = losses; }
};

struct Rva005AE5EEQuad { int value[4]; };
#include "../../../../../Include/GameClient/Rva003821E2.h"
class Rva005AE5EE { public: void rva005AE5EE(const Rva005AE5EEQuad *value); };
#include "../../../../../Include/GameNetwork/Rva00381D02.h"
class Rva004FDB57 { public: void rva004FDB57(AsciiString value); };
class Rva0059F2EB { public: void rva0059F2EB(AsciiString value); };
class GameInfo
{
public:
    virtual ~GameInfo();
    void rva003FF1A7(int value);
    void setMap(AsciiString value);
    UnicodeString m_name;
    char m_08[0x58 - 8];
    int m_scenario;
    int m_gameType;
    int m_rules[10];
    char m_88[0xc0 - 0x88];
    int m_iniCRC, m_cmdCRC;
    char m_c8[4];
    unsigned char m_hash[16];
};
class GameSpyStagingRoom : public GameInfo
{
public:
    GameSpyStagingRoom();
    GameSpyStagingRoom(const GameSpyStagingRoom &other);
    virtual ~GameSpyStagingRoom();
    GameSpyGameSlot *getGameSpySlot(int i);
    char m_slots[8 * 0x1e0];
    AsciiString m_extraMap;
    int m_id;
    void *m_transport;
    AsciiString m_localName;
    bool m_hasPassword, m_allowObservers;
    int m_version;
    bool m_ff4;
    int m_ff8;
    AsciiString m_ladderIP, m_ping;
    int m_pingInt;
    unsigned short m_ladderPort;
    int m_numPlayers, m_maxPlayers, m_numObservers;
    int m_1018, m_101c;
};

class PeerResponse
{
public:
    int peerResponseType;
    std::string groupRoomName, nick, oldNick;
    std::wstring text;
    std::string locale, stagingServerGameOptions;
    std::wstring stagingServerName;
    std::string stagingServerPingString, stagingServerLadderIP, stagingRoomMapName, unknown_7c;
    std::string stagingRoomPlayerNames[8], command, commandOptions;
    std::vector<AsciiString> unknown_100;
    union
    {
        unsigned int words[143];
        struct { int id, numWaiting, maxWaiting, numGames, numPlaying, roomType; } groupRoom;
        struct { int id; bool ok; } joinGroupRoom;
        struct { bool isPrivate, isAction; int profileID; } message;
        struct { int profileID, wins, losses, roomType, flags, ip; } player;
        struct
        {
            int id, action;
            bool isStaging, requiresPassword, allowObservers, useStats;
            unsigned int version;
            Rva005AE5EEQuad exeCRC;
            unsigned int iniCRC, cmdCRC;
            unsigned char ladderHash[16];
            unsigned short ladderPort;
            int wins[8], losses[8], profileID[8], faction[8], color[8], handicap[8];
            int numPlayers, numObservers, maxPlayers, percentComplete, gameType;
            int ladPortValues[10], scenario;
        } stagingRoom;
    };
};
typedef char CheckPeerSize[sizeof(PeerResponse) == 0x348 ? 1 : -1];
typedef char CheckPayload[offsetof(PeerResponse, words) == 0x10c ? 1 : -1];
typedef char CheckRoomSize[sizeof(GameSpyStagingRoom) == 0x1020 ? 1 : -1];
typedef char CheckGameInfoSize[sizeof(GameInfo) == 0xdc ? 1 : -1];
typedef char CheckGroupRoomSize[sizeof(GameSpyGroupRoom) == 0x20 ? 1 : -1];
typedef char CheckRoomID[offsetof(GameSpyStagingRoom, m_id) == 0xfe0 ? 1 : -1];
typedef char CheckRoomVersion[offsetof(GameSpyStagingRoom, m_version) == 0xff0 ? 1 : -1];
typedef char CheckResponseWins[offsetof(PeerResponse, stagingRoom.wins) == 0x148 ? 1 : -1];
typedef char CheckResponseEnd[offsetof(PeerResponse, stagingRoom.scenario) == 0x244 ? 1 : -1];

class GameSpyInfoInterface
{
public:
#define V(n) virtual void slot##n();
    V(0) V(1) V(2)
    virtual GroupRoomMap *getGroupRoomList();
    virtual void addGroupRoom(AsciiUnicodePair value);
    V(5) V(6) V(7) V(8)
    virtual void joinBestGroupRoom(int type);
    V(10)
    virtual void setCurrentGroupRoom(int id);
    V(12) V(13) V(14)
    virtual void slot15(int id);
    V(16) V(17) V(18) V(19) V(20)
    virtual PlayerInfoMap *getPlayerInfoMap();
    V(22) V(23) V(24) V(25) V(26) V(27) V(28)
    virtual AsciiString getLocalName();
    V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
    virtual void clearStagingRoomList();
    V(41) V(42)
    virtual void addStagingRoom(GameSpyStagingRoom value);
    virtual void updateStagingRoom(GameSpyStagingRoom value);
    virtual void removeStagingRoom(GameSpyStagingRoom value);
    V(46) V(47) V(48) V(49)
    virtual void sawFullGameList();
    V(51)
    virtual bool rva00381DC4();
    V(53) V(54) V(55) V(56) V(57) V(58) V(59) V(60)
    virtual void addText(UnicodeString value, int color);
    virtual void slot62(AsciiString name, int profile, UnicodeString text, bool isPublic, bool isAction);
#undef V
};
extern GameSpyInfoInterface *TheGameSpyInfo;
struct Rva00382D39Input;
class GameSpyInfo { public: void rva00382D39(Rva00382D39Input *value, AsciiString oldNick); };
#include "../../../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
#include "../../../../../Include/Common/GameState.h"
extern GameState *TheGameState;
int g_lastJoinedGroupRoomID = -1; // 0x00DD3938: -1 after leaving, 0 in a staging room
extern int GameSpyColor[2];
void Rva00381C2DClear(unsigned int index);
void Rva00381C82AddChatText(int index, const UnicodeString &text, int color);

#include "../../../../../Include/GameClient/AptMessengerOnline.h"

bool AptMessengerOnline::ProcessGameSpyResponse(void *p)
{
    PeerResponse *resp = (PeerResponse *)p;
    switch (resp->peerResponseType)
    {
    case 3:
    {
        GameSpyGroupRoom room;
        room.m_groupID = resp->groupRoom.id;
        room.m_maxWaiting = resp->groupRoom.maxWaiting;
        room.m_name = resp->groupRoomName.c_str();
        room.m_translatedName = UnicodeString((const unsigned short *)L"TEST");
        room.m_numGames = resp->groupRoom.numGames;
        room.m_numPlaying = resp->groupRoom.numPlaying;
        room.m_numWaiting = resp->groupRoom.numWaiting;
        room.m_roomType = resp->groupRoom.roomType;
        TheGameSpyInfo->addGroupRoom(room);
        break;
    }
    case 0:
    case 1:
        g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:CurrentLobbyName"), UnicodeString((const unsigned short *)L" "), false);
        g_lastJoinedGroupRoomID = -1;
        Rva00381C2DClear(1);
        break;
    case 8:
    case 9:
        g_lastJoinedGroupRoomID = 0;
        g_bfmeAptWindowManager->rva00225375("APT:CurrentLobbyName", TheGameSpyInfo->getLocalName(), false);
        Rva00381C2DClear(1);
        break;
    case 20:
        TheGameSpyInfo->addText(UnicodeString((const unsigned short *)resp->text.c_str()), GameSpyColor[0]);
        break;
    case 7:
        if (resp->joinGroupRoom.ok)
        {
            //buttonPushed = true;
            TheGameSpyInfo->setCurrentGroupRoom(resp->joinGroupRoom.id);
            TheGameSpyInfo->slot15(resp->joinGroupRoom.id);
            TheGameSpyInfo->getPlayerInfoMap()->clear();
            GroupRoomMap::iterator it = TheGameSpyInfo->getGroupRoomList()->find(resp->joinGroupRoom.id);
            if (it != TheGameSpyInfo->getGroupRoomList()->end())
            {
                const GameSpyGroupRoom &room = it->second;
                UnicodeString msg;
                msg.format(TheGameText->fetchPtr("GUI:LobbyJoined"), room.m_translatedName.str());
                if (g_lastJoinedGroupRoomID != resp->joinGroupRoom.id)
                {
                    Rva00381C82AddChatText(1, msg, GameSpyColor[1]);
                    g_lastJoinedGroupRoomID = resp->joinGroupRoom.id;
                }
                g_bfmeAptWindowManager->bfmeSetText("APT:CurrentLobbyName", room.m_translatedName, false);
            }
        }
        else
        {
            TheGameSpyInfo->joinBestGroupRoom(1);
        }
        return true;
    case 12:
        if ((resp->player.roomType == 1 && !TheGameSpyInfo->rva00381DC4()) ||
            (resp->player.roomType == 2 && TheGameSpyInfo->rva00381DC4()))
            ((GameSpyInfo *)TheGameSpyInfo)->rva00382D39((Rva00382D39Input *)resp, AsciiString::TheEmptyString);
        return true;
    case 13:
        if ((resp->player.roomType == 1 && !TheGameSpyInfo->rva00381DC4()) ||
            (resp->player.roomType == 2 && TheGameSpyInfo->rva00381DC4()))
            ((GameSpyInfo *)TheGameSpyInfo)->rva00382D39((Rva00382D39Input *)resp, AsciiString::TheEmptyString);
        return true;
    case 14:
    case 22:
        if ((resp->player.roomType == 1 && !TheGameSpyInfo->rva00381DC4()) ||
            (resp->player.roomType == 2 && TheGameSpyInfo->rva00381DC4()))
            ((GameSpyInfo *)TheGameSpyInfo)->rva00382D39((Rva00382D39Input *)resp, AsciiString::TheEmptyString);
        return true;
    case 10:
        if (resp->player.roomType == 1 && !TheGameSpyInfo->rva00381DC4())
            ((GameSpyInfo *)TheGameSpyInfo)->rva00382D39((Rva00382D39Input *)resp, AsciiString::TheEmptyString);
        return true;
    case 11:
        ((GameSpyInfo *)TheGameSpyInfo)->rva00382D39((Rva00382D39Input *)resp, AsciiString::TheEmptyString);
        return true;
    case 2:
        TheGameSpyInfo->slot62(resp->nick.c_str(), resp->message.profileID,
            UnicodeString((const unsigned short *)resp->text.c_str()), !resp->message.isPrivate, resp->message.isAction);
        return true;
    case 5:
        TheGameSpyInfo->sawFullGameList();
        return true;
    case 4:
    {
        GameSpyStagingRoom room;
        switch (resp->stagingRoom.action)
        {
        case 3:
            TheGameSpyInfo->clearStagingRoomList();
            //TheGameSpyInfo->addText( UnicodeString(L"gameList: PEER_CLEAR"), GameSpyColor[GSCOLOR_DEFAULT], listboxLobbyChat );
            break;
        case 0:
        case 1:
        {
            if (resp->stagingRoom.percentComplete == 100)
                TheGameSpyInfo->sawFullGameList();
            //if (ParseAsciiStringToGameInfo(&room, resp.stagingRoomMapName.c_str()))
            //if (ParseAsciiStringToGameInfo(&room, resp.stagingServerGameOptions.c_str()))
            Bool serverOk = true;
            if (!resp->stagingRoomMapName.length() || !resp->unknown_7c.length())
                serverOk = false;
            // fix for ghost game problem - need to iterate over all resp.stagingRoomPlayerNames[i]
            Bool sawSelf = false;
            //for (Int i=0; i<MAX_SLOTS; ++i)
            //{
            if (TheGameSpyInfo->getLocalName().compare(resp->stagingRoomPlayerNames[0].c_str()) == 0)
                sawSelf = true; // don't show ghost games for myself
            //}
            if (sawSelf)
                serverOk = false;
            if (serverOk)
            {
                ((Rva003821E2 *)&room)->assign(UnicodeString((const unsigned short *)resp->stagingServerName.c_str()));
                room.rva003FF1A7(resp->stagingRoom.gameType);
                room.m_id = resp->stagingRoom.id;
                room.m_hasPassword = resp->stagingRoom.requiresPassword;
                room.m_version = resp->stagingRoom.version;
                ((Rva005AE5EE *)&room)->rva005AE5EE(&resp->stagingRoom.exeCRC);
                room.m_iniCRC = resp->stagingRoom.iniCRC;
                room.m_cmdCRC = resp->stagingRoom.cmdCRC;
                ((Rva00381D02 *)&room)->rva00381D02(resp->stagingRoom.ladderHash);
                room.m_allowObservers = resp->stagingRoom.allowObservers;
                ((Rva004FDB57 *)&room)->rva004FDB57(resp->stagingServerPingString.c_str());
                ((Rva0059F2EB *)&room)->rva0059F2EB(resp->stagingServerLadderIP.c_str());
                room.m_ladderPort = resp->stagingRoom.ladderPort;
                room.m_numPlayers = resp->stagingRoom.numPlayers;
                room.m_maxPlayers = resp->stagingRoom.maxPlayers;
                room.m_numObservers = resp->stagingRoom.numObservers;
                memcpy(room.m_rules, resp->stagingRoom.ladPortValues, 0x28);
                room.m_extraMap = AsciiString(resp->unknown_7c.c_str());
                room.m_scenario = resp->stagingRoom.scenario;
                Int i;
                AsciiString gsMapName = resp->stagingRoomMapName.c_str();
                AsciiString mapName = "";
                for (i = 0; i < gsMapName.getLength(); ++i)
                {
                    char c = gsMapName.getCharAt(i);
                    if (c != '/')
                        ((StringBase<char> *)&mapName)->concat(c);
                    else
                        ((StringBase<char> *)&mapName)->concat('\\');
                }
                room.setMap(TheGameState->portableMapPathToRealMapPath(mapName));
                for (i = 0; i < 8; ++i)
                {
                    GameSpyGameSlot *slot = room.getGameSpySlot(i);
                    if (slot)
                    {
                        slot->setWins(resp->stagingRoom.wins[i]);
                        slot->setLosses(resp->stagingRoom.losses[i]);
                        slot->setProfileID(resp->stagingRoom.profileID[i]);
                        slot->setPlayerTemplate(resp->stagingRoom.faction[i]);
                        slot->setColor(resp->stagingRoom.color[i]);
                        slot->setHandicap(resp->stagingRoom.handicap[i]);
                        if (resp->stagingRoom.profileID[i] == SLOT_EASY_AI)
                            slot->setState(SLOT_EASY_AI);
                        else if (resp->stagingRoom.profileID[i] == SLOT_MED_AI)
                            slot->setState(SLOT_MED_AI);
                        else if (resp->stagingRoom.profileID[i] == SLOT_BRUTAL_AI)
                            slot->setState(SLOT_BRUTAL_AI);
                        else if (resp->stagingRoom.profileID[i] == SLOT_AI_5)
                            slot->setState(SLOT_AI_5);
                        else if (resp->stagingRoomPlayerNames[i].length())
                        {
                            UnicodeString nameUStr;
                            nameUStr.translate(resp->stagingRoomPlayerNames[i].c_str());
                            slot->setState(SLOT_PLAYER, nameUStr);
                        }
                        else
                            slot->setState(SLOT_OPEN);
                    }
                }
                //DEBUG_LOG(("Saw room: hasPass=%d, allowsObservers=%d\n", room.getHasPassword(), room.getAllowObservers()));
                if (resp->stagingRoom.action == 0)
                {
                    TheGameSpyInfo->addStagingRoom(room);
                    //TheGameSpyInfo->addText( UnicodeString(L"gameList: PEER_ADD"), GameSpyColor[GSCOLOR_DEFAULT], listboxLobbyChat );
                }
                else
                {
                    TheGameSpyInfo->updateStagingRoom(room);
                    //TheGameSpyInfo->addText( UnicodeString(L"gameList: PEER_UPDATE"), GameSpyColor[GSCOLOR_DEFAULT], listboxLobbyChat );
                }
            }
            else
            {
                room.m_id = resp->stagingRoom.id;
                TheGameSpyInfo->removeStagingRoom(room);
                //TheGameSpyInfo->addText( UnicodeString(L"gameList: PEER_UPDATE FAILED"), GameSpyColor[GSCOLOR_DEFAULT], listboxLobbyChat );
            }
            break;
        }
        case 2:
            room.m_id = resp->stagingRoom.id;
            TheGameSpyInfo->removeStagingRoom(room);
            //TheGameSpyInfo->addText( UnicodeString(L"gameList: PEER_REMOVE"), GameSpyColor[GSCOLOR_DEFAULT], listboxLobbyChat );
            break;
        default:
            //TheGameSpyInfo->addText( UnicodeString(L"gameList: Unknown"), GameSpyColor[GSCOLOR_DEFAULT], listboxLobbyChat );
            break;
        }
        return true;
    }

    }
    return false;
}
