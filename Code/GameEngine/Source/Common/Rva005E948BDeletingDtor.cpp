// cl: /O1 /MD
// ??_GRva005E92F7@@QAEPAXI@Z, retail 0x005E948B, 28 bytes.
// Evidence: scalar deleting destructor shape (dtor call, flags byte test,
// conditional scalar delete through pinned ??3@YAXPAX@Z 0x0002FD60, return
// this). The dtor is the 60B EH body at 0x005E92F7 (installs C78030/C78010,
// member cleanup through 0x005E12D1, restores base g_00BC6F20 per the matched
// Rva005E129B family); it is declared but not defined here and reached
// through an address-honest pin, since its vtable literals have no providers.
// Non-virtual dtor (retail calls it directly, not through the vtable).
// Emitted via the delete anchor after the Rva00154320Cluster precedent;
// the anchor itself is never called. Honest address name; owner unproven.

class Rva005E92F7
{
public:
	~Rva005E92F7();
};

void operator delete(void *p);

void Rva005E92F7_DeleteAnchor(Rva005E92F7 *p)
{
	delete p;
}
