// ??1Rva001F092A@@UAE@XZ
// partial score=0.8 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva001F092A@@UAE@XZ @0x001F0996 302B.
// Complete-object destructor of Rva001F092A (its scalar deleting dtor at
// 0x001F0BEF calls here; vtable 0x00BE100C re-stated at entry like the
// rowed base dtor 0x001B4E74 does). Layout evidence (target facts):
// - Base is the 12B GameEngineDeletingBase (virtual dtor rowed 0x001B4E74,
//   auto-called at the end); map-typed +0x0C per the rowed map<int,void*>
//   ctor 0x0033C432 in the 0x001F092A ctor, followed by two 12B range
//   triples at +0x18/+0x24 (the ctor TU's BfmeE16 element guess is
//   unverified pattern: this body proves 4B pointer elements, so the
//   triples are declared opaquely and the two vector<void*> erases retail
//   issues go through punned calls to the rowed 34B void erase 0x0031BD55;
//   no vector member dtors appear in retail, fixing the trivial type).
// - +0x0C doubles as the Rva001F050B head+count view (ObjectCreationList
//   TU): the value-dtor loop walks head->next with the pinned Rb_next
//   0x0024250 spelling until back at the head, deleting Rva001F077D values
//   (undefined-dtor declaration forces the out-of-line rowed 0x001F077D
//   call); then the rowed clear 0x001F050B frees the nodes, and the rowed
//   tree dtor 0x001F0657 runs as the member dtor at the end.
// - +0x24 holds virtuals (slot0 called with literal 0, return value fed to
//   scalar delete 0x0002FD60: `delete e->v0(0)`); +0x18 holds Rva001F077D
//   pointers deleted by index with a recomputed bound; both vector buffers
//   are freed through 0x00030830 when non-null.
// The strict element/string types, the +0x10 count member and the +0x14 gap
// are unproven; the Rva001F050B overlay pun is explicit below.
#include <map>
#include <vector>

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

struct Rva001F077D
{
	~Rva001F077D();
};

struct Rva001F0996Elem1
{
	virtual void *v0(int arg);
	~Rva001F0996Elem1() {}
};

struct Rva001F0996Node
{
	void *m_00;
	void *m_04;
	Rva001F0996Node *m_next08;
	void *m_0C;
	char m_pad10[4];
	Rva001F077D *m_value14;
};

class Rva001F050B
{
public:
	void rva001F050B();
	~Rva001F050B();
	Rva001F0996Node *m_ptr00;
	int m_count04;
};

// TU-local throwing free spelling for the vector-buffer inline teardown
// (pinned at 0x00030830 beside the pre-existing ?free@@ alias): the C++
// decoration is throwing, which is what makes the caller emit retail's
// state stores ahead of the branches (DynamicPortal WayPoint precedent).
void freeRva001F092AVecBuf(void *ptr);

struct Rva001F092AVec
{
	~Rva001F092AVec()
	{
		if (m_begin != 0)
			freeRva001F092AVecBuf(m_begin);
	}
	void **m_begin;
	void **m_end;
	void **m_storage;
};

class Rva001F092A : public GameEngineDeletingBase
{
public:
	virtual ~Rva001F092A();
private:
	Rva001F050B m_list0C;
	int m_pad14;
	Rva001F092AVec m_vec18;
	Rva001F092AVec m_vec24;
};

Rva001F092A::~Rva001F092A()
{
	Rva001F092A *self = this;
	Rva001F092AVec &v24 = self->m_vec24;
	Rva001F0996Elem1 **i = (Rva001F0996Elem1 **)v24.m_begin;
	while (i != (Rva001F0996Elem1 **)v24.m_end)
	{
		Rva001F0996Elem1 *e = *i;
		if (e)
			delete e->v0(0);
		++i;
	}
	((_STL::vector<void *> *)&v24)->erase(((_STL::vector<void *> *)&v24)->begin(), ((_STL::vector<void *> *)&v24)->end());
	for (Rva001F0996Node *n = self->m_list0C.m_ptr00->m_next08; n != self->m_list0C.m_ptr00; n = (Rva001F0996Node *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)n))
	{
		Rva001F077D *v = n->m_value14;
		if (v)
			delete v;
	}
	self->m_list0C.rva001F050B();
	unsigned int idx = 0;
	if ((((char *)self->m_vec18.m_end - (char *)self->m_vec18.m_begin) >> 2) != 0)
	{
		do
		{
			Rva001F077D *e = (Rva001F077D *)((_STL::vector<void *> *)&self->m_vec18)->begin()[idx];
			if (e)
				delete e;
			++idx;
		} while (idx < (unsigned int)(((char *)self->m_vec18.m_end - (char *)self->m_vec18.m_begin) >> 2));
	}
	((_STL::vector<void *> *)&self->m_vec18)->erase(self->m_vec18.m_begin, self->m_vec18.m_end);
}
