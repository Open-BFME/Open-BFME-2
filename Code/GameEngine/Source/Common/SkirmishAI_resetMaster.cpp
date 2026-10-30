// flags: region default (reverse/retail_inventory/flag_regions.csv)
// SkirmishAI::resetMaster (WorldBuilder name, SkirmishAI.cpp lines 246..254: walk the players via getNthPlayer and 0x002A8AB1 for a new master).
//
// was ?rva002C68CE@Rva002C68CE@@QAEHXZ @0x002C68CE 109B
// Evidence: unlock lane sibling of 0x002C67DC same page 002C6xxx prev
// Rva002C67DCMethod next stlport rb_tree 443B caller 0x002C6B92 callees
// getNthPlayer row plus rva002A8AB1 pin globals ThePlayerList and
// TheSkirmishAIManager offsets 0x15c/0x54/0x14/0x178. Identity: honest-address
// thiscall method returning int with no args.
class Rva002AA22AByteField
{
public:
	unsigned char get() const;			// 0x002AA22A
};
class Rva00380200
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	bool rva003805BB(float value, bool flag);		// 0x003805BB
	float getValue() const { return m_value; }

private:
	unsigned char m_pad04[0x0C - 0x04];
	float m_value;						// +0x0C
};

class SkirmishAI;
class Rva002C5FD9;
class Team;
struct ListNode;
class Player : public Rva002AA22AByteField
{
private:
	friend class SkirmishAI;
public:
	void rva002AE2ED(Player *other); // 0x002AE2ED
	Rva00380200 &getField08() { return m_field08; }
	int getField24() const { return m_field24; }
	void setField24(int value) { m_field24 = value; }
	char m_pad00[0x8];
private:
	Rva00380200 m_field08; // +0x08 +0x08
	char m_pad18[0xC];
	int m_field24; // +0x24 +0x24
	char m_pad28[0x2C];
public:
	int m_54; // +0x54
	char m_pad58[0x10C];
	Rva002C5FD9 *m_164; // +0x164
	char m_pad168[0x184];
private:
	Team *m_team2EC; // +0x2EC +0x2EC
	char m_pad2F0[0x3C];
	ListNode *m_listHead32C; // +0x32C +0x32C list sentinel
};

class PlayerList
{
public:
	Player *getNthPlayer(int i); // 0x002A7A29
	char m_pad00[0x14];
	int m_count14; // +0x14
};

extern PlayerList *ThePlayerList;

struct Rva002A8AB1Record
{
public:
	void *rva002C6ACB();
	char m_pad00[0x15C];
private:
	void *m_15c; // +0x15C
	char m_pad160[0x18];
public:
	int m_178; // +0x178
};

class Rva004E9600;
struct Rva002A8B59Data;
class Rva002A8F24
{
public:
	Rva004E9600 *rva002A8B24(void *key);
	Rva002A8B59Data *rva002A8B59(void *p);
	Rva002A8AB1Record *rva002A8AB1(void *p);
};

extern Rva002A8F24 *TheSkirmishAIManager;

struct Rva002C68CE15C
{
	char m_pad[0x54];
	int m_54;
};

class SkirmishAI
{
public:
	int resetMaster();

private:
	char m_pad[0x15C];
	Player *m_player;
};

int SkirmishAI::resetMaster()
{
	int target = m_player->m_54;
	int result = -1;
	for (int i = 0; i < ThePlayerList->m_count14; i++) {
		Player *player = ThePlayerList->getNthPlayer(i);
		Rva002A8AB1Record *rec = TheSkirmishAIManager->rva002A8AB1(player);
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
