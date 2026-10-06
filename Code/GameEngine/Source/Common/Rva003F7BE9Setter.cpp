// cl: /MD
// ?rva003F7BE9@Rva003F7BE9@@QAEXPBVModuleData@@@Z, retail 0x003F7BE9 (35B).
// Evidence: leaf lane; caller 0x003F9291 Rva003F9258Parse stores new ModuleData; callee operator delete 0x0002FD60 rowed; virtual slot0 with 0 then delete; same shape as 0x003F7C0C setter.
void __cdecl operator delete(void *p);

class ModuleData;

struct Rva003F7BE9Old
{
	virtual void *rva003F7BE9Func(int x);
};

class Rva003F7BE9
{
public:
	void rva003F7BE9(const ModuleData *v);
private:
	char m_00[0x20];
	Rva003F7BE9Old *m_20;
};

void Rva003F7BE9::rva003F7BE9(const ModuleData *v)
{
	void *p = 0;
	if ((void *)m_20 != p)
		p = m_20->rva003F7BE9Func((int)p);
	::operator delete(p);
	m_20 = (Rva003F7BE9Old *)v;
}
