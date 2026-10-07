// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?rva00568143@Rva00568143@@QAEXH@Z @0x00568143 23B: ref lane slot0 of table
// 0x0086CF6C neighbour deleting dtor Rva005685EE; unregisters this as
// CreateAHeroData via rowed Rva002B7250 0x002B7250 then nulls +0x18; ret 4
// vestigial int arg unused.
class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

struct Rva00568143Owner
{
	char m_pad[0x20];
	Rva002B7250 m_list;
};

class Rva00568143
{
public:
	void rva00568143(int unused);

private:
	char m_pad[0x18];
	Rva00568143Owner *m_owner;
};

void Rva00568143::rva00568143(int unused)
{
	(void)unused;
	m_owner->m_list.rva002B7250((CreateAHeroData *)this);
	m_owner = 0;
}
