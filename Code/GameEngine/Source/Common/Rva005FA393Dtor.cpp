// cl: /MD
//
// Opaque destructor at 0x005FA393 (14B): stores its vtable, adjusts this to
// the member at +0x04, and tail-calls the guarded-delete helper at 0x005FA146
// (pinned opaque ?clear: nulls its pointer at +0, runs the element dtor at
// 0x005F9877, then operator delete; exact method unproven). Same shape as the
// three Rva000AD6F4Members.cpp bodies (0x328A75/0x577936/0x5F83DF) and the
// 0x005F7750 twin; the helper type is only declared here (defined nowhere --
// it resolves via the pin). Owner identity is unproven (opaque Rva name).
// The 77B constructor at 0x005FA7EB allocates 0x64 bytes, calls 0x005FA3B1
// with this plus three pointer-sized args, and stores the returned inner
// object at +4. It writes the folded 0x008078DC vtable; because that table has
// several aliases, the constructor keeps its address-derived Rva005FA7EB name.
class Rva005FA3B1Inner
{
public:
	Rva005FA3B1Inner(void *owner, void *a, void *b, void *c);
	char m_opaque[0x64];
};

extern const void *const g_00C078DC[];

class Rva005FA7EB
{
public:
	Rva005FA7EB(void *a, void *b, void *c);

private:
	const void *const *m_vtable;
	Rva005FA3B1Inner *m_member04;
};

Rva005FA7EB::Rva005FA7EB(void *a, void *b, void *c)
	: m_vtable(g_00C078DC)
{
	m_member04 = new Rva005FA3B1Inner(this, a, b, c);
}

class Rva005F9877
{
public:
	~Rva005F9877();
};

void __cdecl operator delete(void *);

class Rva005FA146
{
public:
	void clear();

private:
	Rva005F9877 *m_ptr;
};

class Rva005FA393
{
public:
	virtual ~Rva005FA393();

private:
	Rva005FA146 m_member04;
};

Rva005FA393::~Rva005FA393()
{
	m_member04.clear();
}

// ?clear@Rva005FA146@@QAEXXZ @0x005FA146 26B: guarded-delete helper for
// Rva005FA393 member at +4. Nulls its pointer, runs element dtor at
// 0x005F9877 (??1Rva005F9877@@QAE@XZ pin), then operator delete
// (??3@YAXPAX@Z row mem_ops.cpp). Caller jmp at 0x005FA39C in
// ??1Rva005FA393@@UAE@XZ. LINK BONUS names this exact mangling.
void Rva005FA146::clear()
{
	Rva005F9877 *p = m_ptr;
	m_ptr = 0;
	if (p) {
		p->~Rva005F9877();
		operator delete(p);
	}
}
