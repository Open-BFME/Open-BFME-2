// cl: /O1 /DNDEBUG /MD
//
// ?rva002D7FAE@Rva002D7FAEOwner@@QAEXPAVObject@@@Z @0x002D7FAE 62B: list
// lookup with side effect (thiscall, 1 Object arg, void). Null arg or
// null controlling player bails; walks the intrusive list at m_14
// (data +4, next +8) for the arg; on a hit stores pinned cdecl
// 0x002D7BFD(player+0x280) into node+0xc. Callee is landed
// getControllingPlayer. Views minimal; exact identities unproven.
class Player
{
public:
	char m_pad[0x280];
	int m_280;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

struct Rva002D7FAENode
{
	void *m_00;
	Object *m_04;
	Rva002D7FAENode *m_08;
	int m_0c;
};

class Rva002D7FAEOwner
{
public:
	void rva002D7FAE(Object *obj);

private:
	char m_pad[0x14];
	Rva002D7FAENode *m_14;
};

int __cdecl rva002D7BFD(int x);

// ?rva002D7FAE@Rva002D7FAEOwner@@QAEXPAVObject@@@Z
void Rva002D7FAEOwner::rva002D7FAE(Object *obj)
{
	if (obj == 0)
		return;
	Player *p = obj->getControllingPlayer();
	if (p == 0)
		return;
	Rva002D7FAENode *n = m_14;
	while (n != 0) {
		if (n->m_04 == obj)
			goto FOUND;
		n = n->m_08;
	}
	return;
FOUND:
	n->m_0c = rva002D7BFD(p->m_280);
}
