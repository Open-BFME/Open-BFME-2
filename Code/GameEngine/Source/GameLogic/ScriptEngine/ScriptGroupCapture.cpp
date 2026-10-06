// cl: /DNDEBUG /MD /EHsc
//
// ?captureGroup@Rva003B40A1Holder@@QAEPAXPAX@Z,
// retail 0x003B40A1, 21 bytes. Dedicated TU.
//
// First capture wrapper over the 0x3B3F09 indexed-table worker (matched row):
// forwards the record's two words (index at +4, sub at +8) with the holder
// adjusted to the +0x0C entry table. The sibling at 0x3B40B6 is the same
// shape over the +0x2C table. The worker resolves through its matched row,
// so this TU declares (never defines) its holder.

typedef int Int;

class Rva003B3F09Holder
{
public:
	void *lookupTableEntry(Int entryIndex, Int linkIndex);
};

class Rva003B40A1Holder
{
public:
	void *captureGroup(void *record);
};

// ?captureGroup@Rva003B40A1Holder@@QAEPAXPAX@Z
void *Rva003B40A1Holder::captureGroup(void *record)
{
	Int *words = (Int *)record;
	Rva003B3F09Holder *worker = (Rva003B3F09Holder *)((char *)this + 0x0C);
	return worker->lookupTableEntry(words[1], words[2]);
}
