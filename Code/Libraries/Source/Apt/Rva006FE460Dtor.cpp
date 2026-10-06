// cl: /MD /EHsc
// ??1Rva006FE460@@UAE@XZ @0x006FE460 93B virtual dtor over rowed base.
// Retail stores vtable 0x008EDE4C, calls slot1 on member at +0x20 if non-null,
// nulls it unconditionally, then rowed base ??1Rva006D6470Owner at 0x006D6470
// around SEH registration. Evidence: unlock lane; deleting-dtor caller
// 0x006FE430 calls this then operator delete; offset +0x20 shared with
// Rva006FE400Chain neighbour; base row in LadderPreferencesDtor.cpp.
struct Rva006D6470Owner
{
	virtual ~Rva006D6470Owner();
};

struct Member006FE460
{
	virtual void slot0();
	virtual void slot1();
};

struct Rva006FE460 : public Rva006D6470Owner
{
	char m_pad[0x1C];
	Member006FE460 *m_20;

	virtual ~Rva006FE460();
};

Rva006FE460::~Rva006FE460()
{
	if (m_20 != 0)
		m_20->slot1();
	m_20 = 0;
}
