// cl: /MD
// ?rva0057A418@Rva0057A418@@QAEXXZ @0x0057A418 27B.
// Holder clear: if m_ptr at +0 then virtual get(0) on subobject at +8 else 0 then operator delete.
// Evidence: unlock lane plus callers 0x0057B485 plus callee delete 0x0002FD60 plus prev 0x0057A3F4.
void __cdecl operator delete(void *);
class Sub
{
public:
	virtual void *get(int);
};
class Full
{
public:
	char m_pad[8];
	Sub m_sub;
};
class Rva0057A418
{
public:
	void rva0057A418();
private:
	Full *m_ptr;
};
void Rva0057A418::rva0057A418()
{
	void *p = m_ptr ? m_ptr->m_sub.get(0) : 0;
	::operator delete(p);
}
