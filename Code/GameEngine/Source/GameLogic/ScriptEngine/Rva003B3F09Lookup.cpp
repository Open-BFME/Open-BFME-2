// cl: /DNDEBUG /MD /EHsc
//
// ?lookupTableEntry@Rva003B3F09Holder@@QAEPAXHH@Z,
// retail 0x003B3F09, 38 bytes. Dedicated TU.
//
// Indexed walk over a table of 20-byte entries. Each entry carries a signed
// variant count (word at +0x0E) and a link-chain head (pointer at +0x10).
// When the count is above the requested link index the walk skips
// (count - linkIndex) chain links, then returns the node payload past its
// 4-byte header. The two capture wrappers at 0x3B40A1 (+0x0C table) and
// 0x3B40B6 (+0x2C table) both forward here; the +0x2C side reads the
// scriptList+0x38 generational name table. BFME1 has no subgroup or
// generational tables anywhere in ScriptEngine, so the identity stays an
// honest Rva token (registry/FESL/listbox opaque-row precedent).

struct Rva003B3F09Entry
{
	char m_unknown[0x0E]; // +0x00..+0x0D, unseen by this body
	short m_variantCount; // +0x0E, signed (movsx)
	void *m_linkChain; // +0x10
}; // 0x14 bytes

class Rva003B3F09Holder
{
	char m_pad[0x0C]; // +0x00..+0x0B, owned by the caller object
	Rva003B3F09Entry *m_entryTable; // +0x0C

public:
	void *lookupTableEntry(int entryIndex, int linkIndex);
};

// ?lookupTableEntry@Rva003B3F09Holder@@QAEPAXHH@Z
void *Rva003B3F09Holder::lookupTableEntry(int entryIndex, int linkIndex)
{
	Rva003B3F09Entry *entry = &m_entryTable[entryIndex];
	int variantCount = entry->m_variantCount;
	void *chainLink = entry->m_linkChain;
	if (variantCount > linkIndex) {
		int linksToSkip = variantCount - linkIndex;
		do {
			--linksToSkip;
			chainLink = *(void **)chainLink;
		} while (linksToSkip != 0);
	}
	return (char *)chainLink + 4;
}
