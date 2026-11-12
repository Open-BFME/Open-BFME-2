// cl: /MD
//
// Opaque destructor at 0x005F7750 (14B): stores its vtable, adjusts this to
// the member at +0x04, and tail-calls the guarded-delete helper at 0x005F7736
// (pinned opaque ?clear: nulls its pointer at +0, runs the element dtor at
// 0x005F75C9, then operator delete; exact method unproven). Same shape as the
// three Rva000AD6F4Members.cpp bodies (0x328A75/0x577936/0x5F83DF); the helper
// type is only declared here (defined nowhere -- it resolves via the pin).
// Owner identity is unproven; the ctor 0x005F830A installs the same vtable
// 0x00C79A90, so the class carries the ctor's address name.

class Rva005F7736
{
public:
	void clear();

private:
	void *m_ptr;
};

class Rva005F830A
{
public:
	virtual ~Rva005F830A();
	// Retail's table holds the shared empty body 0x000B3FD0 in slot 1.
	virtual void slot01() {}

private:
	Rva005F7736 m_member04;
};

Rva005F830A::~Rva005F830A()
{
	m_member04.clear();
}
