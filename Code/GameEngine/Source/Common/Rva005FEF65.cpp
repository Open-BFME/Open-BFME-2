// cl: /DNDEBUG /MD /EHs
// ??1Rva005FEF65@@UAE@XZ @0x005FEF65 75B
// Virtual dtor freeing buffer at +0x18 via _free and destroying member at +8.
// Evidence: _free 0x00030830 rowed, pinned ??1Rva005FF95C@@UAE@XZ,
// vtables 0x0087A464 own then 0x007C6F20 base, caller deleting dtor 0x005FEFB3.
extern "C" void __cdecl free(void *p);

class Rva005FF95C
{
public:
	virtual ~Rva005FF95C();
private:
	char m_pad[0x0C];
};

class Rva005FEF65Base
{
public:
	virtual ~Rva005FEF65Base() {}
private:
	int m_04;
};

class Rva005FEF65 : public Rva005FEF65Base
{
public:
	virtual ~Rva005FEF65();
private:
	Rva005FF95C m_08;
	void *m_18;
};

Rva005FEF65::~Rva005FEF65()
{
	if (m_18)
		free(m_18);
}
