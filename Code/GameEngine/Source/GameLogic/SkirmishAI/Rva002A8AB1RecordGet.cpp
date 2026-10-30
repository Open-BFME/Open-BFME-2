// cl: /O1 /EHsc /MD /arch:SSE /G7
// ?rva002C6ACB@Rva002A8AB1Record@@QAEPAXXZ @0x002C6ACB 47B
// Evidence: pin Rva002A8AB1Record; callers in Rva005A9ACDTactic and Rva005AD6F5Finish; callees rowed 0x002A8B24 and 0x004E93E8 plus pinned 0x002A8AB1 plus rowed tail 0x002C5FD9; global TheSkirmishAIManager; member plus 0x15C.
class Rva003A2BD4M08;
class Player;
class Rva004E9600;
class Rva002C5FD9
{
public:
	Player *rva002C5FD9();
};

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

struct Rva002A8AB1Record;
// 0x002A8AB1 by its row name (Rva002A8AB1.cpp).
struct Rva002A8B59Data;
class Rva002A8F24
{
public:
	Rva004E9600 *rva002A8B24(void *key);
	Rva002A8B59Data *rva002A8B59(void *p);
	Rva002A8AB1Record *rva002A8AB1(void *p);
};

extern Rva002A8F24 *TheSkirmishAIManager;

class AIGameTeam
{
public:
	void *getMasterPlayer();
};

class Rva004E9600 : public AIGameTeam
{
};

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

// ?rva002C6ACB@Rva002A8AB1Record@@QAEPAXXZ
void *Rva002A8AB1Record::rva002C6ACB()
{
	Rva004E9600 *mid = TheSkirmishAIManager->rva002A8B24(m_15c);
	void *found = mid->getMasterPlayer();
	Player *player = (Player *)TheSkirmishAIManager->rva002A8AB1(found);
	return player->m_164->rva002C5FD9();
}
