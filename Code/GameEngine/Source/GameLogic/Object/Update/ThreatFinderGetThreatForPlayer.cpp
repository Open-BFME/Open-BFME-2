// cl: /DNDEBUG /MD /EHsc
// ThreatFinder::getThreatForPlayer, retail 0x003ED0C4..0x003ED191 (205B).
// WB 0x01027ED0 names this same member and its calculateThreatLevel call;
// ScriptActions::doSetCounterToThreatFinderThreat calls the existing pin.
// Retail has twenty 0x44-byte records followed by data through +0x564.
// The record ctor's landed address owner is retained as a data-only base:
// ThreatInfo's name comes from the WB return type, its extent from rep movsd.
// Callback names remain addresses; their 0/1 EAX results are already proven.
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
extern int g_Va00DBA4E4;
class Player
{
public:
 unsigned char m_pad000[0x54];
 int m_playerIndex;
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
struct ThreatInfo : public Rva003ECA4BElement {};
class ThreatFinder
{
public:
 ThreatInfo getThreatForPlayer(Player *searchingPlayer, int mode, Player *specificEnemy);
 void calculateThreatLevel();
private:
 ThreatInfo m_playerThreat[20];
 unsigned char m_pad550[0x564 - 0x550];
 unsigned int m_lastFrame;
};
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
