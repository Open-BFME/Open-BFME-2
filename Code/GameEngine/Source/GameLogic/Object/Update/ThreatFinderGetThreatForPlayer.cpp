// cl: /DNDEBUG /MD /EHsc
// ThreatFinder::getThreatForPlayer, retail 0x003ED0C4..0x003ED191 (205B).
// WB 0x01027ED0 names this same member and its calculateThreatLevel call;
// ScriptActions::doSetCounterToThreatFinderThreat calls the existing pin.
// Retail has twenty 0x44-byte records followed by data through +0x564.
// The record ctor's landed address owner is retained as a data-only base:
// ThreatInfo's name comes from the WB return type, its extent from rep movsd.
// Callback names remain addresses; their 0/1 EAX results are already proven.
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../Common/PartitionRangeQueryCallView.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
extern PartitionManager *ThePartitionManager;
extern "C" void *memset(void *, int, unsigned int);
#pragma function(memset)
extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;
class Player
{
public:
 unsigned char m_pad000[0x54];
 int m_playerIndex;
 int getPlayerIndex() const { return m_playerIndex; }
};
class PlayerList
{
public:
 Player *getNthPlayer(int index);
};
extern PlayerList *ThePlayerList;
int Rva003ECB3DIsAlly(const Player *, const Player *);
int Rva003ECB2AIsEnemy(const Player *, const Player *);
class Rva003ECA4BElement
{
public:
 Rva003ECA4BElement();
 void rva003ECA81(const Rva003ECA4BElement *other);
private:
 float m_values[17];
};
struct Rva003ECB52Arg;
class Rva003ECA69Element : public Rva003ECA4BElement {
public: Rva003ECA69Element *rva003ECB52(Rva003ECB52Arg *);
};
struct ThreatInfo : public Rva003ECA69Element {};
template<int N> class BitFlags
{
public:
 BitFlags() { memset(m_bits, 0, sizeof(m_bits)); }
 void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
 unsigned int m_bits[7]; // native and existing ThingIsAnyKindOf view
};
class Thing
{
public:
 bool isAnyKindOf(const BitFlags<69> &) const;
};
class Object : public Thing
{
public:
 Player *getControllingPlayer() const;
};
class Rva000421C8
{
public:
 Rva000421C8() : m_next(0) {}
 virtual ~Rva000421C8() {}
 virtual bool allow(Object *) = 0;
 virtual int getPlayerMask();
 Rva000421C8 *m_next;
};
class Rva0026119DFilter : public Rva000421C8
{
public:
 virtual bool allow(Object *);
};
class Rva003ECB13Array
{
public:
 void clear();
};
class ThreatFinder
{
public:
 ThreatInfo getThreatForPlayer(Player *searchingPlayer, int mode, Player *specificEnemy);
 void calculateThreatLevel();
private:
 ThreatInfo m_playerThreat[20];
 unsigned char m_pad550[4];
 Coord3D m_position;
 float m_radius;
 unsigned int m_lastFrame;
 bool m_excludeStructures;
};

// WB ThreatFinder::calculateThreatLevel and native3ECFBC..3ED0A8.
// The range filter is the already verified alive filter BFAD10. The
// seven-word masks select kind bits3/90 and place bit7 in include/exclude
// according to568. Each accepted object's player54 selects a44-byte record.
void ThreatFinder::calculateThreatLevel()
{
 reinterpret_cast<Rva003ECB13Array *>(this)->clear();
 BfmeWideResult objects = ThePartitionManager->iterateObjectsInRange(
  &m_position, m_radius, 0, &Rva0026119DFilter(), 0);
 BitFlags<69> include;
 BitFlags<69> exclude;
 include.set(3);
 include.set(90);
 if (m_excludeStructures)
  exclude.set(7);
 else
  include.set(7);
 Object *object;
 while ((object = objects.next()) != 0) {
  if (object->isAnyKindOf(include) && !object->isAnyKindOf(exclude)) {
   Player *player = object->getControllingPlayer();
   m_playerThreat[player->getPlayerIndex()].rva003ECB52(reinterpret_cast<Rva003ECB52Arg *>(object));
  }
 }
}
ThreatInfo ThreatFinder::getThreatForPlayer(Player *searchingPlayer, int mode, Player *specificEnemy)
{
 if (static_cast<float>((TheGameLogic->getFrame() - m_lastFrame) * g_Va00DBA4E4) >= 3.0f)
 {
  calculateThreatLevel();
  m_lastFrame = TheGameLogic->getFrame();
 }
 ThreatInfo result;
 if (searchingPlayer)
 {
  int (*relationship)(const Player *, const Player *);
  switch (mode)
  {
  case 0: relationship = Rva003ECB2AIsEnemy; break;
  case 1: relationship = Rva003ECB3DIsAlly; break;
  case 2: return m_playerThreat[specificEnemy->m_playerIndex];
  default: return result;
  }
  for (int i = 0; i < 20; ++i)
  {
   Player *player = ThePlayerList->getNthPlayer(i);
   if (player && static_cast<unsigned char>(relationship(searchingPlayer, player)))
    result.rva003ECA81(&m_playerThreat[i]);
  }
 }
 return result;
}
