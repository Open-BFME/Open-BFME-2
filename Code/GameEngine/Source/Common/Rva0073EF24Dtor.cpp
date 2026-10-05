// cl: /O1 /Ob2 /EHsc /DNDEBUG /MD
#include "../../Include/Common/Rva00041004Lock.h"

struct EmitVtableTag;

struct RvaSmallVtableZeroBase
{
	void *m_04;
	RvaSmallVtableZeroBase() : m_04(0) {}
};

class Rva0007DF07 : public RvaSmallVtableZeroBase
{
public:
	Rva0007DF07();
	virtual ~Rva0007DF07() {}
};

// novtable suppresses the unobserved derived-vptr install in this dtor TU;
// the companion tag-ctor TU emits the scalar deleting wrapper and vtable.
class __declspec(novtable) Rva0073EF24 : public Rva0040EDB, public Rva0007DF07
{
public:
	Rva0073EF24(EmitVtableTag *);
	virtual ~Rva0073EF24();
};

// ??1Rva0073EF24@@UAE@XZ @0x0073EF24 22B. Retail null-safely restores the
// folded second-base vtable at this+8, then tail-jumps to the matched primary
// base destructor at 0x00040EDB. Rva0007DF07 names the vftable symbol at
// 0x00BC6F20 only; the target's secondary-base identity remains unknown.
Rva0073EF24::~Rva0073EF24()
{
}
