// cl: /O1 /EHsc /MD /arch:SSE /G7
// ?rva002C6ACB@Rva002A8AB1Record@@QAEPAXXZ @0x002C6ACB 47B
// Evidence: pin Rva002A8AB1Record; callers in Rva005A9ACDTactic and Rva005AD6F5Finish; callees rowed 0x002A8B24 and 0x004E93E8 plus pinned 0x002A8AB1 plus rowed tail 0x002C5FD9; global g_00DFEEF8; member plus 0x15C.
class Rva003A2BD4M08;
class Player;
class Rva004E9600;
class Rva002C5FD9
{
public:
	Player *rva002C5FD9();
};

class Player
{
public:
	unsigned char m_pad00[0x164];
	Rva002C5FD9 *m_164;
};

class PlayerList
{
public:
	Player *rva002A8AB1(Rva003A2BD4M08 *key);
};

class Rva002A8F24 : public PlayerList
{
public:
	Rva004E9600 *rva002A8B24(void *key);
};

extern Rva002A8F24 *g_00DFEEF8;

class Rva004E93E8
{
public:
	void *rva004E93E8();
};

class Rva004E9600 : public Rva004E93E8
{
};

struct Rva002A8AB1Record
{
public:
	void *rva002C6ACB();

private:
	unsigned char m_pad00[0x15c];
	void *m_15c;
};

// ?rva002C6ACB@Rva002A8AB1Record@@QAEPAXXZ
void *Rva002A8AB1Record::rva002C6ACB()
{
	Rva004E9600 *mid = g_00DFEEF8->rva002A8B24(m_15c);
	void *found = mid->rva004E93E8();
	Player *p = g_00DFEEF8->rva002A8AB1((Rva003A2BD4M08 *)found);
	return p->m_164->rva002C5FD9();
}
