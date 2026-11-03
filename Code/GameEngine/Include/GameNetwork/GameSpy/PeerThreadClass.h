// Target facts (all addresses are RVAs unless marked VA):
// Constructor 0x0038AAEB calls ThreadClass(0) at 0x0038AB03 and stores VA 0x00C1989C at +0 at 0x0038AB0E. Table 0x0081989C has exactly three code words: deleting destructor 0x0038ADC6, ThreadClass::Execute 0x006104B0 and PeerThreadClass::Thread_Function 0x0038EDD7; string data starts at 0x008198A8. Destructor 0x0038ADE2 does not restore a derived table and calls ThreadClass::~ThreadClass at 0x0038AF17. That base destructor (0x00610480) restores VA 0x00C7B6AC, whose three slots are 0x00610620, 0x006104B0 and __purecall 0x0003B810. These are derived and base lifetime tables of one object, not competing PeerThreadClass tables.
// Allocation 0x0038B205 pushes 0x4B0, calls operator new at 0x0038B20A, passes its result to this constructor at 0x0038B224, stores the result at queue+0x64 and dispatches Execute at 0x0038B238. Constructor writes +0x4AC at 0x0038ABFA, fixing the final pointer and extent; its first derived byte writes are +0x50/+0x51 at 0x0038AC8E/0x0038AC8B, immediately after the registered 0x50-byte ThreadClass base.
// Constructor calls string construction at +0x54/+0x60/+0x6C/+0x78 (0x0038AB14..0x0038AB38), +0xB4/+0xC4 (0x0038AB65/0x0038AB74), +0x160/+0x16C (0x0038ABA1/0x0038ABB0), +0x284 (wide, 0x0038ABD0) and +0x490 (0x0038ABEE). Its array constructor at 0x0038AB92 constructs eight 12-byte strings at +0xD0. Destructor 0x0038ADE2 tears down the same spans, the two string-keyed integer trees at +0x98/+0xA4 (0x0038AEB5/0x0038AEC4), the 12-byte server tree at +0x278 (0x0038AE39) and the owned 0x1EC-byte request at +0x298 (0x0038AE15, constructor call 0x0038ABDF). Opaque member storage below preserves these extents without choosing a union arm for the request's overlapping payload at owner+0x3B0.
// Scalar widths and offsets follow constructor 0x0038AAEB: byte +0x8C/+0x94/+0xB0/+0xB1/+0x15C/+0x484/+0x48C/+0x48D/+0x49C/+0x4A8; word +0x178; dwords +0x84/+0x88/+0x90/+0xC0, +0x130..+0x158, +0x17C..+0x23C, +0x240/+0x244, +0x248..+0x274, +0x290/+0x294/+0x488/+0x4A0/+0x4A4/+0x4AC. The loop at 0x0038AD0C initializes the six eight-dword player arrays. handleQMMatch (0x0038B6C1) reads/writes the quickmatch enum at +0x294 and reads the login string at +0x54; playerMessageCallback reads that enum before calling handleQMMatch with six pointer arrays.
// Out-of-line method names and signatures are the ledger's PeerThreadClass rows: 0x003888A8..0x0038892F, 0x003896BD, 0x00389E2D, 0x00389E69, 0x00389E87, 0x00389EA5, 0x00389F2C, 0x00389F4A, 0x0038A5D6, 0x0038A63C, 0x0038A6BF, 0x0038A6DF, 0x0038A774, 0x0038AD81, 0x0038AF29, 0x0038B6C1, 0x0038B9F8, 0x0038BBF0, 0x0038D526, 0x0038E0C4, 0x0038E492 and 0x0038E684. The constructor and virtual destructor stay out of line.
// Request assignment 0x0038B248 copies the same +0x118 payload repeatedly as dwords, bytes and blocks of 15/53/26/7 dwords at 0x0038B324..0x0038B377. Its largest block ends at +0x1EC, so owner+0x3B0 lies inside the single +0x298 request, not a second worker layout. RoomType is the W4RoomType enum in the stat-method ledger rows; the SDK's __PEER_H__ declaration gives it an anonymous enum typedef, which is already complete when that guard is set.

#pragma once

#ifndef BFME2_PEERTHREADCLASS_H
#define BFME2_PEERTHREADCLASS_H

#include "../../../../Libraries/Source/WWVegas/WWLib/ThreadClass.h"

class MutexClass;
struct _SBServer;
#ifndef __PEER_H__
enum RoomType;
#endif
enum QMStatus;

namespace _STL {
template <class T> class char_traits;
template <class T> class allocator;
template <class Char, class Traits, class Alloc> class basic_string;
}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > PeerThreadString;
typedef _STL::basic_string<unsigned short, _STL::char_traits<unsigned short>, _STL::allocator<unsigned short> > PeerThreadWideString;

class PeerThreadClass : public ThreadClass
{
public:
    PeerThreadClass(MutexClass *queueMutex);
    virtual ~PeerThreadClass();
    virtual void Thread_Function();

    void connectCallback(void *peer, int success);
    void nickErrorCallback(void *peer, int type, const char *nick);
    int addServerToMap(_SBServer *server);
    int removeServerFromMap(_SBServer *server);
    _SBServer *findServerByID(int id);
    int findServer(_SBServer *server);
    void stopHostingAlready(void *peer);
    PeerThreadString getMapName();
    PeerThreadWideString getLocalStagingServerName();
    PeerThreadString pingStr();
    PeerThreadString getPlayerName(int index);
    int getPlayerWins(int index);
    int getPlayerLosses(int index);
    int getPlayerProfileID(int index);
    int getPlayerFaction(int index);
    int getPlayerColor(int index);
    int getPlayerHandicap(int index);
    PeerThreadString getQMBotName();
    void sawMatchbot(PeerThreadString bot);
    QMStatus getQMStatus() { return m_qmStatus; }
    void handleQMMatch(void *peer, int mapIndex, int seed, char *names[8],
        char *ips[8], char *sides[8], char *colors[8], char *nats[8], char *extra[8]);
    void pushStatsToRoom(void *peer);
    void getStatsFromRoom(void *peer, RoomType room);
    void trackStatsForPlayer(RoomType room, const char *nick, const char *key, const char *value);
    int lookupStatForPlayer(RoomType room, const char *nick, const char *key);
    void clearPlayerStats(RoomType room);

private:
    PeerThreadString packStatKey(const char *nick, const char *key);
    void doQuickMatch(void *peer);

    bool m_050, m_051;
    void *m_054[3], *m_060[3], *m_06C[3], *m_078[3];
    int m_084, m_088;
    bool m_08C;
    int m_090;
    bool m_094;
    void *m_098[3], *m_0A4[3];
    bool m_0B0, m_0B1;
    void *m_0B4[3];
    int m_0C0;
    void *m_0C4[3], *m_0D0[8][3];
    unsigned int m_130[4], m_140, m_144, m_148[4], m_158;
    bool m_15C;
    void *m_160[3], *m_16C[3];
    unsigned short m_178;
    int m_17C[8], m_19C[8], m_1BC[8], m_1DC[8], m_1FC[8], m_21C[8];
    int m_23C, m_240, m_244, m_248[10], m_270, m_274;
    void *m_278[3], *m_284[3];
    int m_290;
    QMStatus m_qmStatus;
    unsigned char m_298[0x1EC];
    bool m_484;
    void *m_488;
    bool m_48C, m_48D;
    void *m_490[3];
    bool m_49C;
    int m_4A0, m_4A4;
    bool m_4A8;
    MutexClass *m_4AC;
};

typedef char PeerThreadClassExtent[sizeof(PeerThreadClass) == 0x4B0 ? 1 : -1];

#endif
