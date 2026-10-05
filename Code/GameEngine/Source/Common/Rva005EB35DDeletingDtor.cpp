// cl: /O1 /MD
// ??_GRva005EB2E7@@QAEPAXI@Z, retail 0x005EB35D, 28 bytes.
// Scalar deleting destructor shape (dtor call, flags byte test, conditional
// scalar delete through pinned ??3@YAXPAX@Z 0x0002FD60, return this), same
// recipe as the landed 0x005E948B/0x005E3051 rows. The 118B dtor at 0x005EB2E7
// is declared but not defined here and reached through an address-honest pin
// (non-virtual: retail calls it directly). Emitted via the delete anchor;
// the anchor itself is never called. Honest address name; owner unproven.

class Rva005EB2E7
{
public:
	~Rva005EB2E7();
};

void operator delete(void *p);

void Rva005EB2E7_DeleteAnchor(Rva005EB2E7 *p)
{
	delete p;
}
