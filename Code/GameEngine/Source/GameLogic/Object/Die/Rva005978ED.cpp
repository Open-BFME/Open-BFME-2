// cl: /O1 /GX- /arch:SSE2
// ?rva005978ED@Rva005978ED@@QAEPAVRva005970ED@@XZ @0x005978ED 150B
// Banked attempt reverse/attempts/0x005978ed.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
// ?rva005978ED@Rva005978ED@@QAEPAVRva005970ED@@XZ @0x005978ED 150B
// Leaf __thiscall beside Rva0059781D/Rva00597B32 (same flags and Die dir).
// Two passes over the +0x24 voidptr vector (start +0x24 finish +0x28) with
// int param at +0x14. Each element is an Rva005970ED (m_id08 at +8 m_30 at
// +0x30 m_34 at +0x34 per its ctor TU): call rva0059710E then check 2/1 and
// m_34 zero then findObjectByID plus Object::rva00294ADD returning the
// element when the final check is zero else null. Row for rva0059710E says
// void(int) but every caller (here 0x00597902 0x00597943) cmps eax so it is
// used as int(int); declared int here and noted. Pin for rva00294ADD says
// one int arg ret 4; used as int(int) with the arg pushed early.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object
{
public:
	int rva00294ADD(int x);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

namespace _STL
{

template <class _Tp> class allocator
{
};

template <class _Tp, class _Alloc> class vector
{
public:
	_Tp *m_start;
	_Tp *m_finish;
	_Tp *m_end;
};

}

class Rva005970ED
{
public:
	int rva0059710E(int x);
	char m_pad00[8];
	ObjectID m_id08;
	char m_pad0C[0x30 - 0x0C];
	int m_30;
	unsigned char m_34;
};

class Rva005978ED
{
public:
	Rva005970ED *rva005978ED();
private:
	char m_pad00[0x14];
	int m_14;
	char m_pad18[0x24 - 0x18];
	_STL::vector<void *, _STL::allocator<void *> > m_vec24;
};

Rva005970ED *Rva005978ED::rva005978ED()
{
	Rva005970ED **it = (Rva005970ED **)m_vec24.m_start;
	Rva005970ED **finish = (Rva005970ED **)m_vec24.m_finish;
	while (it != finish)
	{
		Rva005970ED *e = *it;
		if (e->rva0059710E(m_14) == 2 && e->m_34 == 0)
		{
			int v30 = e->m_30;
			ObjectID id = e->m_id08;
			if (TheGameLogic->findObjectByID(id)->rva00294ADD(v30) == 0)
				return e;
		}
		++it;
	}
	it = (Rva005970ED **)m_vec24.m_start;
	while (it != finish)
	{
		Rva005970ED *e = *it;
		if (e->rva0059710E(m_14) == 1 && e->m_34 == 0)
		{
			int v30 = e->m_30;
			ObjectID id = e->m_id08;
			if (TheGameLogic->findObjectByID(id)->rva00294ADD(v30) == 0)
				return e;
		}
		++it;
	}
	return 0;
}
