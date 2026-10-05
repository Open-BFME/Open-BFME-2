// cl: /O1 /MD /DNDEBUG
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

class Rva005F83B9
{
public:
	void rva005F83B9();
	void rva00577944();
private:
	char m_pad[0x20];
	Rva005F83B9Entry *m_20;
	Rva005F83B9Entry *m_24;
};

void Rva005F83B9::rva005F83B9()
{
	rva00577944();
	Rva005F83B9Entry *end = m_24;
	Rva005F83B9Entry *it = m_20;
	for (; it != end; ++it)
	{
		Rva005F83B9Item *o = it->m_obj;
		if (o)
			o->rva005F83B9Run();
	}
}
