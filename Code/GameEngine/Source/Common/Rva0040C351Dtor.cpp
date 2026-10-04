// cl: /O1 /DNDEBUG /MD
// ??1Rva0040C351@@UAE@XZ @0x0040C39E (29B). Dtor of Rva0040C351 (own vtable
// 0x00C3944C, member at +0xAC with derived vtable 0x00C3945C restored to base
// 0x00BC6F20 by the inlined member dtor), tail-jmp to base dtor. Same layout
// as the neighbour ctor TU Rva0040C351Ctor.cpp; base dtor is rowed under the
// ICF twin ??1Rva0037DEE4 at 0x0037DEE4 (pin).
extern const void *const g_00C3944C[];
extern const void *const g_00C3945C[];
extern const void *const g_00BC6F20[];

class Rva0037DF2C
{
public:
	Rva0037DF2C();
	virtual ~Rva0037DF2C();
private:
	char m_pad[0xAC - 4];
};

struct MemberAC
{
	~MemberAC();
	void *m_vtable;
	int m_04;
};

// ??1MemberAC@@QAE@XZ present-unmatched
__forceinline MemberAC::~MemberAC() { m_vtable = (void *)g_00BC6F20; }

class __declspec(novtable) Rva0040C351 : public Rva0037DF2C
{
public:
	Rva0040C351();
	virtual ~Rva0040C351();
private:
	MemberAC m_ac;
};

Rva0040C351::~Rva0040C351()
{
	*(const void **)this = g_00C3944C;
	MemberAC *p = &m_ac;
	p->m_vtable = (void *)g_00C3945C;
}
