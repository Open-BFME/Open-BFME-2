// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// ?rva0022161B@Rva0022161B@@QAEXXZ, retail 0x0022161B 26B.
// Holder at +4 of Rva0022167C owns Rva002215F4 pointer at +0; derived dtor
// 0x0022167C stores vtable 0x00BE6BA8 then add ecx,4 jmp here. Evidence: retail
// bytes plus rowed callee ??1Rva002215F4@@UAE@XZ at 0x002215F4 plus rowed
// operator delete 0x0002FD60 plus caller jmp at 0x00221685.
class AsciiString;
class Rva002215F4 {
public:
	virtual ~Rva002215F4();
	Rva002215F4(void *owner, const AsciiString &name);
private:
	char m_pad[8];
};

void __cdecl operator delete(void *block);
void *__cdecl operator new(unsigned int size);

class Rva0022161B {
public:
	void rva0022161B();
private:
	Rva002215F4 *m_ptr;
};

void Rva0022161B::rva0022161B()
{
	Rva002215F4 *p = m_ptr;
	m_ptr = 0;
	if (p) {
		p->Rva002215F4::~Rva002215F4();
		::operator delete(p);
	}
}
// ??1Rva0022167C@@QAE@XZ, retail 0x0022167C 14B.
// Non-virtual dtor of 8-byte polymorphic holder: stores vtable 0x00BE6BA8 at +0
// then tail-jumps to member at +4 via Rva0022161B::rva0022161B at 0x0022161B.
// Evidence: chain lane calls just-landed 0x0022161B plus 27 callers plus LINK BONUS 3 files plus vtable 0x00BE6BA8.
extern const void *const g_00BE6BA8[];
class __declspec(novtable) Rva0022167C {
public:
	~Rva0022167C();
	virtual void _pure() = 0;
private:
	Rva0022161B m_at4;
};
Rva0022167C::~Rva0022167C()
{
	*(const void **)this = g_00BE6BA8;
	m_at4.rva0022161B();
}
// ??0Rva00221635@@QAE@H@Z, retail 0x00221635 71B.
// Ctor of 8-byte holder with vtable g_00BE6BA8 at +0 and Rva002215F4 pointer
// at +4 allocated with new 12B and built with rowed callee
// ??0Rva002215F4@@QAE@PAXABVAsciiString@@@Z at 0x002215D5 passing this as owner
// and the int argument as the AsciiString address. Evidence: gap between rows
// 0x0022161B and 0x0022167C in this file plus LINK BONUS name plus vtable
// g_00BE6BA8 plus rowed operator new 0x0002FDA0 plus 13 callers.
class __declspec(novtable) Rva00221635 {
public:
	Rva00221635(int arg);
	virtual void _pure() = 0;
private:
	Rva002215F4 *m_ptr;
};
Rva00221635::Rva00221635(int arg)
{
	*(const void **)this = g_00BE6BA8;
	m_ptr = new Rva002215F4(this, *(const AsciiString *)arg);
}
