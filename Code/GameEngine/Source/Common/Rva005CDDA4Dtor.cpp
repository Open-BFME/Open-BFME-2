// cl: /EHsc /MD
//
// ??1Rva005CDDA4@@UAE@XZ @0x005CDDA4 (76B).
// Dtor restoring two vptrs plus +0x20 pointer field clear plus two base dtors.
// Evidence: deleting dtor 0x005CDF2D calls here; vtable slot 0 of 0x00C750BC;
// +0xc vptr plus +0x20 null-checked +0x24 clear plus callees (5D2015 pinned, 5E663C canonical)
// ??1Rva005D2015 and ??1Rva005E663C; neighbours ctor 0x005CDB8F and wrapper.

// Canonical native twelve-byte owning wrapper prefix, ctor663C/dtor66A4.
class Rva005E663C
{
public:
 virtual ~Rva005E663C();
private:
 void *m_04;
 void *m_08;
};

class Rva005D2015
{
public:
	virtual ~Rva005D2015();

private:
	char m_pad04[0x14 - 0x04];
};

struct Rva005CDDA4Ptr
{
	char m_pad00[0x24];
	int m_24;
};

class Rva005CDDA4 : public Rva005E663C, public Rva005D2015
{
public:
	virtual ~Rva005CDDA4();

private:
	Rva005CDDA4Ptr *m_20;
};

Rva005CDDA4::~Rva005CDDA4()
{
	if (m_20 != 0)
		m_20->m_24 = 0;
}
