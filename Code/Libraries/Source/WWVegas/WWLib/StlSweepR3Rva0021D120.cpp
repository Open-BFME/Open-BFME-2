// cl: /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// Native string-record search family: comparator21BBDC22B, unrolled search
// 21C5BE179B, dispatch wrapper21D12027B. All boundaries and call sites read
// independently from game.dat. The records are16B and the comparator passes
// their+8 field to the established StringBase<char>::compare at69D6.
// Only the observed string field is typed; the other12 bytes remain opaque.
// Original record and function names are unknown. The search algorithm follows
// verified sibling40ABA5 and STLport4.5.3 random-access find, not its record type.
// Replaces the refuted uninitialized_fill_n owner: retail dispatch21D120 calls
// find21C5BE, whose seven calls compare strings; it never fills memory.
#include "ascii_string.h"
struct Rva0021BBDCRecord {char beforeName[8]; AsciiString name; char afterName[4];};
bool Rva0021BBDCEqual(const Rva0021BBDCRecord* item,const StringBase<char>* name) {return ((const StringBase<char>*)&item->name)->compare(*name)==0;}
const Rva0021BBDCRecord *Rva0021C5BEFind(const Rva0021BBDCRecord *first, const Rva0021BBDCRecord *last, const StringBase<char> *val, int tag)
{
	(void)tag;
	const Rva0021BBDCRecord *f = first;
	const char *e = (const char *)last;
	int n = (int)((const char *)last - (const char *)first) >> 6;
	while (n > 0) {
		if (Rva0021BBDCEqual(f, val))
			return f;
		++f;
		if (Rva0021BBDCEqual(f, val))
			return f;
		++f;
		if (Rva0021BBDCEqual(f, val))
			return f;
		++f;
		if (Rva0021BBDCEqual(f, val))
			return f;
		++f;
		--n;
	}
	switch ((int)(e - (const char *)f) >> 4) {
	case 3:
		if (Rva0021BBDCEqual(f, val))
			return f;
		++f;
	case 2:
		if (Rva0021BBDCEqual(f, val) == false) {
			++f;
		} else {
			return f;
		}
	case 1:
		if (Rva0021BBDCEqual(f, val))
			return f;
	}
	return last;
}


const Rva0021BBDCRecord *Rva0021D120Find(const Rva0021BBDCRecord *first,const Rva0021BBDCRecord *last,const StringBase<char> *name) {
 char tag;
 return Rva0021C5BEFind(first,last,name,(int)&tag);
}
