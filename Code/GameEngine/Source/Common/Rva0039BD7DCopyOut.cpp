// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// ?rva0039BD7D@Rva0039BD7D@@QAE?AUBfmeStringRecord002B4DC1@@XZ @0x0039BD7D
// @0x0039BD7D 30B: returns the +0x310 string record by value; the rowed
// BfmeStringRecord002B4DC1 copy ctor at 0x002B4DC1 builds directly into the
// hidden return pointer (NRVO). Evidence: single stack arg cleaned (ret 4),
// callee takes dest in ecx per the rowed copy ctor, arg returned in eax.
#include "unicode_string.h"

struct BfmeStringRecord002B4DC1
{
	UnicodeString text;
	unsigned int word0;
	unsigned int word1;
	BfmeStringRecord002B4DC1(const BfmeStringRecord002B4DC1 &o);
};

class Rva0039BD7D
{
public:
	BfmeStringRecord002B4DC1 rva0039BD7D(void);

private:
	char m_pad00[0x310];
	BfmeStringRecord002B4DC1 m_rec310;
};

BfmeStringRecord002B4DC1 Rva0039BD7D::rva0039BD7D(void)
{
	return m_rec310;
}
