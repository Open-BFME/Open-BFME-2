// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002C68CE@Rva002C68CE@@QAEHXZ @0x002C68CE 109B
// Evidence: unlock lane sibling of 0x002C67DC same page 002C6xxx prev
// Rva002C67DCMethod next stlport rb_tree 443B caller 0x002C6B92 callees
// getNthPlayer row plus rva002A8AB1 pin globals ThePlayerList and
// g_00DFEEF8 offsets 0x15c/0x54/0x14/0x178. Identity: honest-address
// thiscall method returning int with no args.
class Player
{
public:
	char m_pad[0x54];
	int m_54;
};

class PlayerList
{
public:
	Player *getNthPlayer(int i);
	int m_pad0[5];
	int m_count14;
};

extern PlayerList *ThePlayerList;

struct Rva002A8AB1Record
{
	char m_pad[0x178];
	int m_178;
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *p);
};

extern Rva002A8F24 *g_00DFEEF8;

struct Rva002C68CE15C
{
	char m_pad[0x54];
	int m_54;
};

class Rva002C68CE
{
public:
	int rva002C68CE();

private:
	char m_pad[0x15C];
	Rva002C68CE15C *m_ptr15C;
};

int Rva002C68CE::rva002C68CE()
{
	int target = m_ptr15C->m_54;
	int result = -1;
	for (int i = 0; i < ThePlayerList->m_count14; i++) {
		Player *player = ThePlayerList->getNthPlayer(i);
		Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(player);
		if (!rec)
			continue;
		if (rec->m_178 != target)
			continue;
		if (result == -1) {
			result = player->m_54;
			rec->m_178 = -1;
		} else {
			rec->m_178 = result;
		}
	}
	return result;
}
