// cl: /MD /GX-
// stlport
// ?rva002ACD09@Player@@QAEXPAXH@Z @0x002ACD09 98B: Player factory creating
// Rva002AC3BE entry (new 0x18) from source +0x118 via rowed ctor 0x002AC3BE
// then vector<uint> assign via pinned 0x0026F4F4 from source +0x11c and int
// at +0x10 from second arg and bool at +0x14 from source +0x12a then
// list<int> push_back via rowed 0x0005548F at Player+0x6f4. Callers at
// 0x004B5B38 and 0x004B5B7B pass Player as this with object and ObjectID.
// Prev PlayerRva002AC629 next Rva002ACF9CInsert. Honest Player method name
// with voidptr-int args; uint vector spelling matches 4B assign row.
#include <vector>
#include <list>

class Rva002AC3BE
{
public:
	Rva002AC3BE(void *a);
	void *m_00;
	_STL::vector<unsigned int> m_04;
	int m_10;
	bool m_14;
};

struct Src002ACD09
{
	char m_pad[0x118];
	void *m_118;
	_STL::vector<unsigned int> m_11c;
	char m_pad128[2];
	bool m_12a;
};

class Player
{
public:
	void rva002ACD09(void *src, int id);
private:
	char m_pad[0x6f4];
	_STL::list<int> m_list6f4;
};

void Player::rva002ACD09(void *srcVoid, int id)
{
	Src002ACD09 *src = (Src002ACD09 *)srcVoid;
	Rva002AC3BE *e = new Rva002AC3BE(&src->m_118);
	int tmp = (int)e;
	e->m_04 = src->m_11c;
	e->m_10 = id;
	e->m_14 = src->m_12a;
	m_list6f4.push_back(tmp);
}
