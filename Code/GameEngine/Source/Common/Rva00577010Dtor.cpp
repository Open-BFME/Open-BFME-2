// cl: /O1 /DNDEBUG /MD
// ??1Rva00577010@@QAE@XZ @0x00577010 30B: holder dtor clears void* at +0 then calls pointee virtual slot 1 with 0 and frees return via operator delete. Evidence: pinned dtor plus 3 matched callers in MemberBaseDtorsB01 plus rowed delete 0x0002FD60 plus rva00577324 holder use.
class Rva00577010Pointee
{
public:
	virtual ~Rva00577010Pointee();
	virtual void *release(int a);
};

class Rva00577010
{
public:
	~Rva00577010();
private:
	Rva00577010Pointee *m_value;
};

Rva00577010::~Rva00577010()
{
	Rva00577010Pointee *p = m_value;
	m_value = 0;
	operator delete(p ? p->release(0) : 0);
}
