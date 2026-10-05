// cl: /O1 /MD
// ?rva002A7B1C@Rva002A7B1C@@QAEXXZ 24B @0x002A7B1C
// Player array refresh: 20 entries at +0x18 calling updateTeamStates.
// Evidence: neighbours PlayerListRva002A7AFE / PlayerList_getNthPlayer share
// +0x18 and /O1; callee row 0x002AB429; caller at 0x0020D2A6 unclaimed so
// owner address-derived; push/pop 0x14 is /O1 size idiom.
class Player
{
public:
	void updateTeamStates();
};

class Rva002A7B1C
{
public:
	void rva002A7B1C();
private:
	unsigned char m_pad[0x18]; // +0x00
	Player *m_players[20]; // +0x18
};

void Rva002A7B1C::rva002A7B1C()
{
	int n = 0x14;
	Player **pp = m_players;
	do
	{
		(*pp)->updateTeamStates();
		++pp;
	} while (--n != 0);
}
