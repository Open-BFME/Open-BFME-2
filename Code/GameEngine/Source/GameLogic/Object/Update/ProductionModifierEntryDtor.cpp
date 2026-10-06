// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
//
// ??1ProductionModifierEntry@@QAE@XZ, retail 0x0049D12D, 53 bytes.
//
// Heap element of ProductionUpdateModuleData's +0x3C modifier list (the big
// dtor at 0x0049E2B3 walks the list null-testing each value, running this
// dtor, then deleting through 0x002FD60). The entry is an AsciiString name
// at +0 plus a pool-aware member at +4 destroyed through the opaque 13B
// forwarder at 0x00360D26 (Rva00360D26Member spelling per the
// TransportContainModuleData precedent; member type itself unrecovered).
// Members die in reverse declaration order: the +4 member first (throwing,
// so retail arms state 0 around it), then the name through the folded
// 0x0036410 (nothrow throw() spelling, so no second state). The entry's true
// type name is unproven; ProductionModifierEntry claims only its role as the
// production modifier-list entry. A scalar-deleting ??_G calling here sits
// at ~0x0049D82A (boundary to prove before landing).

#include "ascii_string.h"

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned m_unknown;
};

class ProductionModifierEntry
{
public:
	~ProductionModifierEntry();

private:
	AsciiString m_name; // +0
	Rva00360D26Member m_filter; // +4
};

// ??1ProductionModifierEntry@@QAE@XZ @0x0049D12D
ProductionModifierEntry::~ProductionModifierEntry()
{
}

// ??_GProductionModifierEntry@@QAEPAXI@Z @0x0049D82F (28 bytes, abuts the
// entry dtor's ??_G slot; boundary proven by the ret at 0x0049D82E plus the
// ??_G prologue). Emitted by the delete helper (Version precedent); the dtor
// and operator-delete calls resolve through their rows.
void deleteProductionModifierEntry(ProductionModifierEntry *entry) { delete entry; }
