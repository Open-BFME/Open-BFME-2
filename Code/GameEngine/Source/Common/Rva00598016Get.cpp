// cl: /MD
// ?rva00598016@Rva00598016@@QAEPAXXZ @0x00598016 15B via global store lookup
// Evidence: thiscall ret0 returns void*; pushes Player at this+0x30; rowed rva002A8F24 0x002A8F24 via global g_00DFEEF8; caller 0x0059883B; same g_00DFEEF8 pattern as Rva005DC8A2
class Player;
class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);
};
extern Rva002A8F24 *g_00DFEEF8;
class Rva00598016
{
public:
	void *rva00598016();
private:
	char m_pad[0x30];
	Player *m_player;
};
void *Rva00598016::rva00598016()
{
	return g_00DFEEF8->rva002A8F24(m_player);
}
