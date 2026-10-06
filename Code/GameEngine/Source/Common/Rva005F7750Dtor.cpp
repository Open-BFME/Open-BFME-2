// cl: /MD
//
// Opaque destructor at 0x005F7750 (14B): stores its vtable, adjusts this to
// the member at +0x04, and tail-calls the guarded-delete helper at 0x005F7736
// (pinned opaque ?clear: nulls its pointer at +0, runs the element dtor at
// 0x005F75C9, then operator delete; exact method unproven). Same shape as the
// three Rva000AD6F4Members.cpp bodies (0x328A75/0x577936/0x5F83DF); the helper
// type is only declared here (defined nowhere -- it resolves via the pin).
// Owner identity is unproven (opaque Rva name).

class Rva005F7736
{
public:
	void clear();

private:
	void *m_ptr;
};

class Rva005F7750
{
public:
	virtual ~Rva005F7750();

private:
	Rva005F7736 m_member04;
};

Rva005F7750::~Rva005F7750()
{
	m_member04.clear();
}
