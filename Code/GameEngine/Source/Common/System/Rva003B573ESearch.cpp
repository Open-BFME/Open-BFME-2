// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
#include "ascii_string.h"

// ?rva003B573E@Rva003B573E@@QAEHABV?$StringBase@D@@@Z @0x003B573E (80B).
// Sorted record table lower_bound: count from +0/+4 words, binary search
// over 0x14-stride records at +0xC comparing name at +8 via rowed
// StringBase<char>::compare 0x000069D6. Returns match mid or low.
// Unblocks 0x003B66D8 and 0x003B6633. Same compare idiom as the WWLib
// string-table precedent.
struct Rva003B573ERecord
{
	char m_pad[8];
	StringBase<char> m_name;
	char m_tail[0x14 - 8 - 4];
};

class Rva003B573E
{
public:
	int rva003B573E(const StringBase<char> &key);
private:
	int *m_begin;
	int *m_end;
	char m_gap[0xC - 8];
	Rva003B573ERecord *m_records;
};

int Rva003B573E::rva003B573E(const StringBase<char> &key)
{
	int count = ((char *)m_end - (char *)m_begin) >> 2;
	int low = 0;
	while (count > low) {
		int mid = (count + low) >> 1;
		int idx = m_begin[mid];
		int cmp = key.compare(m_records[idx].m_name);
		if (cmp == 0) {
			return mid;
		} else if (cmp < 0) {
			count = mid;
		} else {
			low = mid + 1;
		}
	}
	return low;
}
