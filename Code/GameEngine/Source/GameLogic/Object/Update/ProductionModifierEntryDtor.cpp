// cl: /O1 /EHsc /DNDEBUG /MD
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

class AsciiString
{
public:
	// Declared-only dtor (throwing): the teardown resolves through the
	// ??1AsciiString pin at the folded 0x0036410. Being the last unwindable
	// destruction, retail resets the trylevel before it (Transport dtor
	// precedent: two throwing members give and/call/or/call).
	~AsciiString();

private:
	void *m_data;
};

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
