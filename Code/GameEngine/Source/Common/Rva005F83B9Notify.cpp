// cl: /MD /DNDEBUG
// ?rva005F83B9@Rva005F83B9@@QAEXXZ @0x005F83B9 38B
// Notifier walking the 8-byte-entry range [+0x20,+0x24): runs the pinned
// thiscall helper 0x00577944 first, then virtual slot #1 on each non-null
// element head. Evidence: direct call plus indirect call [eax+4] with
// test/je guard and add-8 stride in retail; frameless with no EH state.
class Rva005F83B9Item
{
public:
	virtual ~Rva005F83B9Item();
	virtual void rva005F83B9Run();
};

struct Rva005F83B9Entry
{
	Rva005F83B9Item *m_obj;
	int m_pad;
};

struct Rva005F83B9Vector
{
	Rva005F83B9Entry *m_start;
	Rva005F83B9Entry *m_finish;
	int size() const { return m_finish - m_start; }
};

class Rva005F83B9
{
public:
	void rva005F83B9();
	void rva00577944();
	char m_pad[0x20];
	Rva005F83B9Vector m_vec;
};

void Rva005F83B9::rva005F83B9()
{
	rva00577944();
	Rva005F83B9Entry *end = m_vec.m_finish;
	Rva005F83B9Entry *it = m_vec.m_start;
	for (; it != end; ++it)
	{
		Rva005F83B9Item *o = it->m_obj;
		if (o)
			o->rva005F83B9Run();
	}
}

// ?rva005F8427@Rva005F8427@@QAEXXZ @0x005F8427 8B member forwarder to rowed
// ?rva005F83B9@Rva005F83B9@@QAEXXZ (0x005F83B9). No callers. Honest address name.
class Rva005F8427
{
public:
	int rva005F8408() const;
	void rva005F8427();
private:
	char m_pad[4];
	Rva005F83B9 *m_member;
};

int Rva005F8427::rva005F8408() const
{
	return m_member->m_vec.size();
}

void Rva005F8427::rva005F8427()
{
	return m_member->rva005F83B9();
}
