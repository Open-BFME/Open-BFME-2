// cl: /DNDEBUG /MD /EHsc
//
// ?captureGroup@Rva003B40B6Holder@@QAEPAXPAX@Z,
// retail 0x003B40B6, 21 bytes. Dedicated TU.
//
// Capture-group thunk over the indexed table walker at 0x3B3F09 (matched
// row ?lookupTableEntry@Rva003B3F09Holder@@QAEPAXHH@Z, declared here and
// resolved out-of-line). The incoming record carries the entry index at
// +0x04 and the link index at +0x08; this holder's walker lives at +0x2C,
// which reads the scriptList+0x38 generational name table. Sibling thunk at
// 0x3B40A1 serves the +0x0C table the same way. BFME1 has no subgroup or
// generational tables anywhere in ScriptEngine, so both thunks keep honest
// Rva-holder names (registry/FESL/listbox opaque-row precedent).

class Rva003B3F09Holder
{
	char m_pad[0x0C]; // +0x00..+0x0B, owned by the caller object
	void *m_entryTable; // +0x0C, read by the matched worker body

public:
	void *lookupTableEntry(int entryIndex, int linkIndex);
};

struct Rva003B40B6Args
{
	int m_unused; // +0x00
	int m_entryIndex; // +0x04
	int m_linkIndex; // +0x08
};

class Rva003B40B6Holder
{
	char m_pad[0x2C]; // +0x00..+0x2B, owned by the caller object
	Rva003B3F09Holder m_tableWalker; // +0x2C

public:
	void *captureGroup(void *rawArgs);
};

// ?captureGroup@Rva003B40B6Holder@@QAEPAXPAX@Z
void *Rva003B40B6Holder::captureGroup(void *rawArgs)
{
	Rva003B40B6Args *args = (Rva003B40B6Args *)rawArgs;
	return m_tableWalker.lookupTableEntry(args->m_entryIndex, args->m_linkIndex);
}
