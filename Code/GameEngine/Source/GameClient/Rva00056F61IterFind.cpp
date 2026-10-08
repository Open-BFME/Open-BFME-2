// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0041534B@Rva00056F61@@QAE?AURva0041534BIter@@PBVAsciiString@@@Z, retail 0x0041534B (27B).
// Find returning iterator over the AsciiString-keyed bucket table owned by
// Rva00056F61 (rowed find 0x00056F61). Same this plus AsciiString key in then
// hidden-pointer out {node table} with ret 8. Callers at 0x00223D02
// (add ecx 0x48) and 0x002AE98B (add ecx 0x294) read node at out+0 and use
// payload at node+8. Shape matches STLport hashtable find 0x00620DD0 and the
// InsertRet00212A5A hidden-pointer precedent via user ctor.
#include "ascii_string.h"

class Rva00056F61;
struct Rva0041534BIter
{
	void *m_node;
	Rva00056F61 *m_table;
	Rva0041534BIter(void *n, Rva00056F61 *t) : m_node(n), m_table(t) {}
};

class Rva00056F61
{
public:
	void *rva00056F61(const AsciiString *key);
	// The 0x56F61 lookup only hashes and compares existing bytes: its callees
	// are 0x55041 -> 0x2BA61 and 0x69D6 -> 0x6733 -> memcmp. No allocation,
	// callbacks, or C++ throws occur. This exception contract also lets callers
	// reuse the iterator return buffer for their later conditional pair.
	__declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *key);
};

__declspec(nothrow) Rva0041534BIter Rva00056F61::rva0041534B(const AsciiString *key)
{
	return Rva0041534BIter(rva00056F61(key), this);
}
