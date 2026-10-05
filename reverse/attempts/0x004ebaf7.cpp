// ?rva004EBAF7@@YAXPAVObject@@PAURva004EBAF7Rec@@_N@Z
// partial score=0.9 date=2026-10-05
// ?rva004EBAF7@@YAXPAVObject@@PAURva004EBAF7Rec@@_N@Z
// partial score=0.9 date=2026-10-05
// cl: /O1
// stlport
//
// ?rva004EBAF7@@YAXPAVObject@@PAURva004EBAF7Rec@@_N@Z @0x004EBAF7 97B.
// Find-or-append counter: unless flag is clear, scan the record's BfmeE8
// vector for an entry whose `a` matches the controlling player's +0x54;
// on a hit bump its `b`, otherwise append {m_54, 0} through rowed push_back
// 0x00539A2E and bump the reloaded last element (reallocation-safe).
namespace _STL
{
template<class _T> class allocator { };
template<class _Tp, class _Alloc = allocator<_Tp> > class vector
{
public:
	void push_back(const _Tp &v);
	_Tp *_M_start;
	_Tp *_M_finish;
	_Tp *_M_end_of_storage;
};
}

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

struct Rva004EBAF7Player
{
	char m_pad[0x54];
	unsigned int m_54;
};

struct BfmeE8
{
	unsigned int a;
	unsigned int b;
};

struct Rva004EBAF7Rec
{
	char m_pad[0x28];
	_STL::vector<BfmeE8> m_vec;
};

void rva004EBAF7(Object *a1, Rva004EBAF7Rec *a2, bool flag)
{
	if (!flag)
		return;
	BfmeE8 *end = a2->m_vec._M_finish;
	_STL::vector<BfmeE8> &vec = a2->m_vec;
	BfmeE8 *it = vec._M_start;
	for (; it != end; ++it) {
		Rva004EBAF7Player *p = (Rva004EBAF7Player *)a1->getControllingPlayer();
		if (it->a == p->m_54)
			goto FOUND;
	}
	{
		BfmeE8 e;
		e.a = ((Rva004EBAF7Player *)a1->getControllingPlayer())->m_54;
		e.b = 0;
		vec.push_back(e);
		it = vec._M_start + (vec._M_finish - vec._M_start) - 1;
	}
FOUND:
	++it->b;
}
