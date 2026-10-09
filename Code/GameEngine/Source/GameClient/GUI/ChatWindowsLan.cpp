// cl: /O1 /G7 /arch:SSE /EHsc /MD /Ireference/shims/bfme2_ascii
// WorldBuilder ChatWindowsLan::GetLobbyPlayers, ChatWindowsLan.cpp:99/102.
// Native 5D557F..5D5648 proves the complete EH body and list/address layout.
// String record lifetime and vector append use their existing verified owners.
#include "unicode_string.h"

struct BfmeStringRecord005D511F {
    UnicodeString text0;
    unsigned int word0, word1;
    UnicodeString text1;
    unsigned int word2;
    BfmeStringRecord005D511F(const BfmeStringRecord005D511F &);
    BfmeStringRecord005D511F(const UnicodeString &, unsigned int,
        unsigned int, const UnicodeString &, unsigned int);
    ~BfmeStringRecord005D511F();
};
namespace _STL {
template<class T> class allocator {};
template<class T, class A = allocator<T> > class vector {
public:
    void push_back(const T &);
};
}

struct BfmeNetAddress {
    bool Rva00248CBF(const BfmeNetAddress *) const;
    unsigned int address;
    unsigned int port;
};
struct LANPlayer {
    UnicodeString name;
    unsigned char m_unknown04[12];
    LANPlayer *next;
    BfmeNetAddress address;
};

// Reduced interfaces: only the native call-site slots are named here.
class LANAPI {
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
    V10(0) V10(1) V10(2) V10(3) V10(4)
    V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58)
    virtual LANPlayer *GetLobbyPlayers(); // +EC
    V(60) V(61) V(62) V(63)
    virtual const BfmeNetAddress *GetLocalAddress(); // +100
#undef V10
#undef V
};
class GameTextInterface {
public:
#define V(n) virtual void slot##n();
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
    V(8) V(9) V(10) V(11) V(12) V(13) V(14)
#undef V
    virtual UnicodeString fetch(const char *, bool *);
};
extern LANAPI *TheLAN;
extern GameTextInterface *TheGameText;
extern int GameSpyColor[];

class ChatWindowsLan {
public:
    void GetLobbyPlayers(_STL::vector<BfmeStringRecord005D511F> *);
};

void ChatWindowsLan::GetLobbyPlayers(
    _STL::vector<BfmeStringRecord005D511F> *players)
{
    if (!TheLAN)
        return;
    LANPlayer *player = TheLAN->GetLobbyPlayers();
    if (!player)
        return;
    const BfmeNetAddress *local = TheLAN->GetLocalAddress();
    UnicodeString description = TheGameText->fetch("APT:PlayerInLobby", 0);
    do {
        const BfmeNetAddress &address = player->address;
        int colorIndex = address.Rva00248CBF(local) ? 10 : 8;
        BfmeStringRecord005D511F record(player->name, address.address,
            address.port, description, GameSpyColor[colorIndex]);
        players->push_back(record);
        player = player->next;
    } while (player);
}
