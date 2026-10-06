// cl: /Oy- /DNDEBUG /MD /EHsc
// stlport
//
// Version-block equal-range worker for the lookup at 0x00427EDA.
// Binary-searches the 0x18-byte record table for the query key: the miss
// path reports the insertion point in both output slots while the key-hit
// path resolves the matching range through the lower-bound and upper-bound
// adapters (STLport equal_range shape with the found case calling back
// into lower_bound plus upper_bound). The comparator object is a dummy:
// the less leaves never read `this`, so the chain threads an unread slot
// whose address serves as the member-call target. The trailing flags
// argument is vestigial and unread. /G7 is load-bearing (register
// coloring plus the imul stride). Defined apart from the findEntry wrapper
// so the wrapper keeps its out-of-line call. Semantic class membership is
// unproven so the worker rides the TU-local VersionBlockParser scope;
// opaque behavior.

struct VersionBlockEntry
{
	const char *m_key;
};

class VersionBlockKeyCompare
{
public:
	bool lessEntryKey(const VersionBlockEntry *entry, const char *key) const;
	bool lessKeyEntry(const char *key, const VersionBlockEntry *entry) const;
};

class VersionBlockParser
{
public:
	static const void *searchEntries(const void *found, const void *first, const void *last, const char *const *key, const void *match, int flags);
	static const void *forwardLowerBound(const void *first, const void *last, const char *const *key, const void *match);
	static const void *forwardUpperBound(const void *first, const void *last, const char *const *key, const void *match);
};

// ?searchEntries@VersionBlockParser@@SAPBXPBX00PBQBD0H@Z
const void *VersionBlockParser::searchEntries(const void *found, const void *first, const void *last, const char *const *key, const void *match, int flags)
{
	const VersionBlockKeyCompare &compare = (const VersionBlockKeyCompare &)match;
	int count = ((const char *)last - (const char *)first) / 24;
	const void *mid;
	while (count > 0) {
		int half = count >> 1;
		mid = (const char *)first + half * 24;
		if (compare.lessEntryKey((const VersionBlockEntry *)mid, *key)) {
			first = (const char *)mid + 24;
			count = count - half - 1;
		} else if (compare.lessKeyEntry(*key, (const VersionBlockEntry *)mid)) {
			count = half;
		} else {
			goto found;
		}
	}
	((const void **)found)[0] = first;
	((const void **)found)[1] = first;
	return found;
found:
	const void *low = VersionBlockParser::forwardLowerBound(first, mid, key, match);
	const void *high = VersionBlockParser::forwardUpperBound((const char *)mid + 24, (const char *)first + count * 24, key, match);
	((const void **)found)[0] = low;
	((const void **)found)[1] = high;
	return found;
}
