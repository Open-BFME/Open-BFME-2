// cl: /MD /O1 /arch:SSE /G7
//
// ??1Rva005E35DA@@QAE@XZ @0x005E35DA 26B: owning-pointer dtor nulling +0 then
// running pointee dtor 0x005E3585 plus operator delete 0x0002FD60.
// Evidence: push esi mov esi [ecx] and [ecx] 0 test je call dtor push delete;
// caller 0x005E364D in ??1Rva005E362F@@UAE@XZ via member +0xC; LINK BONUS name.
void __cdecl operator delete(void *p);

class Rva005E3585
{
public:
	~Rva005E3585();
};

class Rva005E35DA
{
public:
	~Rva005E35DA();
private:
	Rva005E3585 *m_ptr;
};

Rva005E35DA::~Rva005E35DA()
{
	Rva005E3585 *p = m_ptr;
	m_ptr = 0;
	if (p)
	{
		p->Rva005E3585::~Rva005E3585();
		::operator delete(p);
	}
}
