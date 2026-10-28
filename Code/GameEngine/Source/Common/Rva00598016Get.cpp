// cl: /MD
// ?rva00598016@AIUnitBuilder@@QAEPAXXZ @0x00598016 15B via global store lookup
// Evidence: thiscall ret0 returns void*; pushes Player at this+0x30; rowed rva002A8F24 0x002A8F24 via global TheSkirmishAIManager; caller 0x0059883B; same TheSkirmishAIManager pattern as Rva005DC8A2
class Player;
struct Rva002A8AB1Record;
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *p);
	void *rva002A8F24(Player *player);
};
extern Rva002A8F24 *TheSkirmishAIManager;
class AIUnitBuilder
{
public:
	void *rva00598016();
private:
	char m_pad[0x30];
	Player *m_player;
};
void *AIUnitBuilder::rva00598016()
{
	return TheSkirmishAIManager->rva002A8F24(m_player);
}
