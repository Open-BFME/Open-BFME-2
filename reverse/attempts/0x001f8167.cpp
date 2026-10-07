// ??1Rva005C67C0@@QAE@XZ
// partial score=0.95 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD /EHsc
// ??1Rva005C67C0@@QAE@XZ retail 0x001F8167 88B. Second-base dtor called from
// 0x001F9025 at 0x001F9043 and chain root 0x001F8BE8 at 0x001F8C06. Owning
// pointer range destroyed through virtual slot0 with 0 plus operator delete
// then the buffer freed. No donor.
void __cdecl operator delete(void *);
extern "C" void __cdecl free(void *);
struct Rva005C67C0Element
{
	virtual void *virt0(unsigned int);
};
class Rva005C67C0Base
{
public:
	Rva005C67C0Element **m_begin;
	Rva005C67C0Element **m_end;
	Rva005C67C0Element **m_endOfStorage;
	~Rva005C67C0Base()
	{
		if (m_begin)
			free(m_begin);
	}
};
class Rva005C67C0 : public Rva005C67C0Base
{
public:
	~Rva005C67C0();
};
Rva005C67C0::~Rva005C67C0()
{
	Rva005C67C0Base *self = this;
	for (Rva005C67C0Element **it = self->m_begin; it != self->m_end; ++it) {
		Rva005C67C0Element *p = *it;
		::operator delete(p ? p->virt0(0) : 0);
	}
}
