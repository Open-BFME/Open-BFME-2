// cl: /O1
// stlport
// ?rva002E21D1@Rva002E21D1@@QAEXXZ retail 0x002E21D1 84 bytes.
// Unlock lane: clear vector at +0x1b8; per element forward [elem+0x78]
// via pinned GameLogic 0x0023D007, call virtual slot0 with 0 and delete
// the returned pointer, then STL erase begin/end via rowed 0x0031BD55.
// Evidence: same +0x1b8 vector and +0x78/GameLogic pattern as sibling
// Rva002E10BDFind.cpp; callees rowed/pinned per packet; neighbours /O1.
#include <vector>

class GameLogic
{
public:
	void rva0023D007(int x);
};
extern GameLogic *TheGameLogic;

class Rva002E21D1Elem
{
public:
	virtual void *vf0(int x);
};

class Rva002E21D1
{
public:
	void rva002E21D1();
private:
	char m_pad[0x1b8];
	_STL::vector<void *> m_1b8;
};

// ?rva002E21D1@Rva002E21D1@@QAEXXZ
void Rva002E21D1::rva002E21D1()
{
	for (unsigned int i = 0; i < m_1b8.size(); ++i) {
		Rva002E21D1Elem *o = (Rva002E21D1Elem *)m_1b8[i];
		TheGameLogic->rva0023D007(*(const int *)((const char *)o + 0x78));
		delete o->vf0(0);
	}
	_STL::vector<void *> *v = &m_1b8;
	v->erase(v->begin(), v->end());
}
