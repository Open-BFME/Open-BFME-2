// cl: /O1 /arch:SSE /MD /DNDEBUG
//
// ?rva0049DC50@Rva0049DC50@@QAEXH@Z @0x0049DC50 187B.
// Walk the list at +8. A node whose id matches the argument is removed
// after the player refund, unless the byte at +0xFD is clear and the
// float at +0x14 is at least the global.

struct Rva0039BAD2Input;

class Rva0039B7AD;

class Rva003B0D7C
{
public:
	void rva003B0D7C(int amount, Rva0039B7AD *arg, bool flag);
};

class Rva0039BAD2
{
public:
	void rva0039BAD2(Rva0039BAD2Input *in, int amount);
};

class Rva0037E421
{
public:
	unsigned char rva0037E7DA(int id);
};

class Rva0049D526
{
public:
	void rva0049D57F(void *node);
};

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva0049DC50Node
{
public:
	virtual void *slot0(int flag);
	int m_4;
	Rva0039BAD2Input *m_8;
	char m_gap0c[4];
	int m_10;
	float m_14;
	char m_gap18[0x10];
	int m_28;
	char m_gap2c[0x1C];
	Rva0049DC50Node *m_next;
};

class Rva0049DC50
{
public:
	void rva0049DC50(int id);
	char m_pad[8];
	Rva0049DC50Node *m_list;
	char m_gap[0xF1];
	unsigned char m_fd;
	char m_gap2[2];
	int m_100;
};

void Rva0049DC50::rva0049DC50(int id)
{
	Rva0049DC50Node *node = m_list;
	while (node != 0)
	{
		bool flag = node->m_14 >= 100.0f && m_100 != 0;
		if (node->m_10 == id && (m_fd != 0 || flag == 0))
		{
			Player *player = (*(Object **)((char *)this - 0x18))->getControllingPlayer();
			if (flag == 0)
			{
				((Rva003B0D7C *)((char *)player + 0x90))->rva003B0D7C(
					node->m_28, (Rva0039B7AD *)((char *)player + 0x3bc), true);
				((Rva0039BAD2 *)((char *)player + 0x3bc))->rva0039BAD2(node->m_8, -node->m_28);
			}
			if (node->m_4 == 3)
				((Rva0037E421 *)((char *)player + 0x738))->rva0037E7DA(node->m_10);
			((Rva0049D526 *)((char *)this - 0x20))->rva0049D57F(node);
			::operator delete(node->slot0(0));
			return;
		}
		node = node->m_next;
	}
}
