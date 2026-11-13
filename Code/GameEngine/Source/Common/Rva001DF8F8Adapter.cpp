// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: scratch adapter at 0x1DF8F8 (35B). Passes a by-value
// record to the 0x1DF88C grower; the record is built by the rowed
// Rva001DE6E1 default ctor (0x1DE6E1); callee named as its owner rows it. Codegen view only (opaque members,
// declared copy/dtor force in-place construction - the same device as the
// other adapters). Address-derived names.

struct Rva001DF88CEntry
{
	char m_bytes[48];
public:
	Rva001DF88CEntry();
	Rva001DF88CEntry(const Rva001DF88CEntry &other);
	~Rva001DF88CEntry();
};
#include "../../Include/Common/Rva001DF88CVector.h"
class Rva001DF8F8
{
public:
	void rva001DF8F8(int n);
};

// ?rva001DF8F8@Rva001DF8F8@@QAEXH@Z
void Rva001DF8F8::rva001DF8F8(int n)
{
	((Rva001DF88CVector *)this)->resize(n, Rva001DF88CEntry());
}
