// cl: /MD /EHsc /DNDEBUG
// ?rva002B34E5@Rva002B34E5@@QAEX_N@Z @0x002B34E5 184B: __thiscall void(bool) storing flag at +0x10B then notifying matching outers. Evidence: retail mov cl,[ebp+8] lea [esi+0x10B] cmp/mov byte plus outer array [+0x8C,+0x90) of Rva002E071E* compared via rowed Rva002E071E::rva002E071E against +0x98 with self-skip then inner array [+0x1B8,+0x1BC) calling rowed Rva003FDE71::rva003FDE71 via +0x88; caller at 0x0042CF44; callees rowed.
class Rva002E071E
{
public:
	bool rva002E071E(const Rva002E071E *other) const;
};

class Rva003FDE71
{
public:
	void rva003FDE71();
};

struct Rva002B34E5Inner
{
	char m_pad[0x88];
	Rva003FDE71 *m_obj;
};

struct Rva002B34E5Outer
{
	char m_pad[0x1B8];
	Rva002B34E5Inner **m_begin;
	Rva002B34E5Inner **m_end;
};

class Rva002B34E5
{
	char m_pad0[0x8C];
	Rva002E071E **m_begin;
	Rva002E071E **m_end;
	char m_pad1[4];
	Rva002E071E *m_ref;
	char m_pad2[0x10B - 0x9C];
	bool m_flag;
public:
	void rva002B34E5(bool v);
};

void Rva002B34E5::rva002B34E5(bool v)
{
	if (m_flag == v)
		return;
	m_flag = v;
	if (m_ref == 0)
		return;
	for (unsigned i = 0; i < (unsigned)(m_end - m_begin); ++i) {
		Rva002E071E *cur = m_begin[i];
		if (m_ref == cur)
			continue;
		if (!m_ref->rva002E071E(cur))
			continue;
		Rva002B34E5Outer *o = (Rva002B34E5Outer *)cur;
		for (unsigned j = 0; j < (unsigned)(o->m_end - o->m_begin); ++j) {
			Rva002B34E5Inner *inner = o->m_begin[j];
			Rva003FDE71 *obj = inner->m_obj;
			if (obj != 0)
				obj->rva003FDE71();
		}
	}
}
