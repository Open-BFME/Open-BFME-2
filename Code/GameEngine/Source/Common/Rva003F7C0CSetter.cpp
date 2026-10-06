// cl: /MD
// ?rva003F7C0C@Rva003F7C0C@@QAEXPAX@Z, retail 0x003F7C0C (35B).
// Evidence: unlock lane; caller 0x003F8F2B SessionTask::ParseINI sets +0x14 to new 0x20 INI object; callee operator delete 0x0002FD60 rowed; virtual slot0 with 0 then delete.

void __cdecl operator delete(void *p);

struct Rva003F7C0COld
{
	virtual void *rva003F7C0CFunc(int x);
};

class Rva003F7C0C
{
public:
	void rva003F7C0C(void *v);
private:
	char m_00[0x14];
	Rva003F7C0COld *m_14;
};

void Rva003F7C0C::rva003F7C0C(void *v)
{
	void *p = 0;
	if ((void *)m_14 != p)
		p = m_14->rva003F7C0CFunc((int)p);
	::operator delete(p);
	m_14 = (Rva003F7C0COld *)v;
}
