// cl: /MD
//
// ??1Rva00481805@@UAE@XZ, retail 0x00481805 (7 bytes). Opaque trivial
// single-inheritance destructor: reinstalls its vtable (DIR32 auto-patch)
// and returns. Owner identity unproven (opaque Rva name). Dedicated TU so
// no caller can inline it.

class Rva00481805
{
public:
	virtual ~Rva00481805();
};

Rva00481805::~Rva00481805()
{
}
