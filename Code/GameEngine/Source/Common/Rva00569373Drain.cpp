// cl: /O1 /MD
//
// ?rva00569373@Rva00569373@@QAEXPAX@Z @0x00569373 32B.
// Drain loop over the +0x58/+0x5C pointer vector: while begin != end, call
// the rowed 0x005691DB-twin 0x0056913D on *begin with (this, tag). Each call
// erases its own element from this vector via rowed 0x00568F04, so the
// re-fetched begin advances without an explicit cursor. Honest
// address-derived names; host doubles as the BitRange of 0x0056913D.
class BitRange;

class Rva0056913D
{
public:
	void rva0056913D(BitRange *host, void *tag);
};

class Rva00569373
{
public:
	void rva00569373(void *tag);
private:
	// Volatile begin: the rva0056913D call erases through this vector, so
	// retail re-fetches m_begin for the body dereference instead of carrying
	// the test's load across the back-edge.
	char m_pad[0x58];
	Rva0056913D **volatile m_begin;	// +0x58
	Rva0056913D **m_end;	// +0x5C
};

void Rva00569373::rva00569373(void *tag)
{
	while (m_begin != m_end)
		(*m_begin)->rva0056913D((BitRange *)this, tag);
}
