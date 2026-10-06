// cl: /Oy- /DNDEBUG /MD /EHsc
// stlport
//
// Version-block table search helpers for the lookup at 0x00427EDA.
// The worker at 0x00427DEA binary-searches 0x18-byte records by key and
// resolves the matching range; the wrapper below forwards the parser
// call with a zero sixth argument and returns the output slot. Worker
// address read from the wrapper REL32; every byte below is retail.
// Semantic class membership is unproven beyond the lookup pins so the
// helpers ride a TU-local VersionBlockParser scope; opaque behavior.

// Retail stores 0x18-byte records with the key string at +0 and the value
// string at +0xC (read from the compare leaves and the worker immediates).
// The bounds only do address arithmetic over the records, never reading
// members, but the full layout is spelled for readability.
struct VersionBlockEntry
{
	const char *m_key; // +0
	char m_padAfterKey[8]; // +4, contents unproven
	const char *m_value; // +0xC
	char m_padTail[8]; // +0x10, contents unproven
};

class VersionBlockKeyCompare
{
public:
	bool lessEntries(const VersionBlockEntry *left, const VersionBlockEntry *right) const;
	bool lessEntryKey(const VersionBlockEntry *entry, const char *key) const;
	bool lessKeyEntry(const char *key, const VersionBlockEntry *entry) const;
};

class VersionBlockParser
{
public:
	static const void *lowerBound(const void *first, const void *last, const char *const *key, const void *comp, int filler);
	static const void *upperBound(const void *first, const void *last, const char *const *key, const void *comp, int filler);
	static const void *searchEntries(const void *found, const void *first, const void *last, const char *const *key, const void *match, int flags);
	static const void *findEntry(const void *found, const void *first, const void *last, const char *const *key, const void *match);
};

// ?lowerBound@VersionBlockParser@@SAPBXPBX0PBQBD0H@Z
const void *VersionBlockParser::lowerBound(const void *first, const void *last, const char *const *key, const void *comp, int filler)
{
	int recordCount = (int)((const char *)last - (const char *)first) / 24;
	while (recordCount > 0) {
		int halfCount = recordCount >> 1;
		const VersionBlockEntry *midEntry = (const VersionBlockEntry *)((const char *)first + halfCount * 24);
		// Retail passes the parameter slot itself as the stateless
		// comparator's this (lea ecx,[ebp+0x14]); the leaves never read it.
		if (((const VersionBlockKeyCompare *)&comp)->lessEntryKey(midEntry, *key)) {
			first = midEntry + 1;
			recordCount = recordCount - halfCount - 1;
		} else {
			recordCount = halfCount;
		}
	}
	(void)filler;
	return first;
}

// ?upperBound@VersionBlockParser@@SAPBXPBX0PBQBD0H@Z
const void *VersionBlockParser::upperBound(const void *first, const void *last, const char *const *key, const void *comp, int filler)
{
	int recordCount = (int)((const char *)last - (const char *)first) / 24;
	while (recordCount > 0) {
		int halfCount = recordCount >> 1;
		const VersionBlockEntry *midEntry = (const VersionBlockEntry *)((const char *)first + halfCount * 24);
		// Same slot-as-this convention as lowerBound (lea ecx,[ebp+0x14]).
		if (((const VersionBlockKeyCompare *)&comp)->lessKeyEntry(*key, midEntry)) {
			recordCount = halfCount;
		} else {
			first = midEntry + 1;
			recordCount = recordCount - halfCount - 1;
		}
	}
	(void)filler;
	return first;
}

// ?findEntry@VersionBlockParser@@SAPBXPBX00PBQBD0@Z
const void *VersionBlockParser::findEntry(const void *found, const void *first, const void *last, const char *const *key, const void *match)
{
	searchEntries(found, first, last, key, match, 0);
	return found;
}
