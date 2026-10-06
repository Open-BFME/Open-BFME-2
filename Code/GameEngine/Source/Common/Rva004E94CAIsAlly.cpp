// cl: /MD
// ?rva004E94CA@Rva004E94CA@@QAE_NPAVPlayer@@@Z @0x004E94CA 49B if +4==0 false else nth=getNthPlayer([[[this]+8]+0x10]) return arg->getRelationship(nth)==ALLIES callees 0x002A7A29 0x002AC3E0 global ThePlayerList caller 0x002A949F
enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };
class Player
{
public:
    Relationship getRelationship(const Player *that) const;
};
class PlayerList
{
public:
    Player *getNthPlayer(int i);
};
extern PlayerList *ThePlayerList;
struct Inner004E94CA { char _pad[0x10]; int m_10; };
struct Mid004E94CA { char _pad[8]; Inner004E94CA *m_08; };
class Rva004E94CA
{
public:
    Mid004E94CA *m_00;
    int m_04;
    bool rva004E94CA(Player *p);
};

bool Rva004E94CA::rva004E94CA(Player *p)
{
    if (m_04) {
        int idx = m_00->m_08->m_10;
        Player *nth = ThePlayerList->getNthPlayer(idx);
        Relationship r = p->getRelationship(nth);
        return r == ALLIES;
    }
    return false;
}
