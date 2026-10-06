// cl: /MD
//
// Opaque destructor at 0x005FA393 (14B): stores its vtable, adjusts this to
// the member at +0x04, and tail-calls the guarded-delete helper at 0x005FA146
// (pinned opaque ?clear: nulls its pointer at +0, runs the element dtor at
// 0x005F9877, then operator delete; exact method unproven). Same shape as the
// three Rva000AD6F4Members.cpp bodies (0x328A75/0x577936/0x5F83DF) and the
// 0x005F7750 twin; the helper type is only declared here (defined nowhere --
// it resolves via the pin). Owner identity is unproven (opaque Rva name).

class Rva005FA146
{
public:
	void clear();

private:
	void *m_ptr;
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
