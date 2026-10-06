// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002C67DC@Rva002C67DC@@QAE_NXZ @0x002C67DC 105B
// Evidence: unlock lane, prev Disp8CmpBoolGetters 0x002C67CF next stlport
// rb_tree 0x002C6C93, 1 caller 0x002AB44A, callees getNthPlayer row plus
// DispByteFieldGetters row plus rva002A8AB1 pin, globals ThePlayerList and
// g_00DFEEF8, offsets 0x178/0x15c/0x54/0x14. Identity: honest-address
// thiscall method returning bool with no args.
class Player
{
};

class PlayerList
{
public:
	Player *getNthPlayer(int i);
	int m_pad0[5];
	int m_count14;
};

extern PlayerList *ThePlayerList;

class Rva002AA22AByteField
{
public:
	unsigned char get() const;
};

struct Rva002A8AB1Record
{
public:
	char m_pad[0x178];
	int m_178;
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *p);
};

extern Rva002A8F24 *g_00DFEEF8;

struct Rva002C67DC15C
{
	char m_pad[0x54];
	int m_54;
};

class Rva002C67DC
{
public:
	bool rva002C67DC();

private:
	char m_pad[0x15C];
	Rva002C67DC15C *m_ptr15C;
	char m_pad2[0x18];
	int m_178;
};

bool Rva002C67DC::rva002C67DC()
{
	if (m_178 != -1)
		return true;
	for (int i = 0; i < ThePlayerList->m_count14; i++) {
		Player *player = ThePlayerList->getNthPlayer(i);
		if (((Rva002AA22AByteField *)player)->get() != 0)
			continue;
		Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(player);
		if (!rec)
			continue;
		if (rec->m_178 == m_ptr15C->m_54)
			return true;
	}
	return false;
}
