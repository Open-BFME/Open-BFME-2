// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Heterogeneous key-compare leaves for the BFME2 version-block table
// search at 0x00427DEA. Retail stores 0x18-byte records with the key
// string at +0 and the value string at +0xC; the lookup at 0x00427EDA
// returns the record whose key matches or the default. The worker drives
// all three spellings: record-vs-record, record-vs-key and key-vs-record.
// Each body is a strcmp less-than with a byte-wide result temp; the
// strcmp call rides the existing _strcmp thunk pin at 0x006291C6.
// Semantic class membership is unproven so the comparator is a TU-local
// holder; every address and slot below is read from the BFME2 bytes.

#include <string.h>

int strcmp(const char *left, const char *right);

struct VersionBlockEntry
{
	const char *m_key;
};

class VersionBlockKeyCompare
{
public:
	bool lessEntries(const VersionBlockEntry *left, const VersionBlockEntry *right) const;
	bool lessEntryKey(const VersionBlockEntry *entry, const char *key) const;
	bool lessKeyEntry(const char *key, const VersionBlockEntry *entry) const;
};

// ?lessEntries@VersionBlockKeyCompare@@QBE_NPBUVersionBlockEntry@@0@Z
bool VersionBlockKeyCompare::lessEntries(const VersionBlockEntry *left, const VersionBlockEntry *right) const
{
	const char *rightKey = right->m_key;
	const char *leftKey = left->m_key;
	return (strcmp(leftKey, rightKey) < 0) || false;
}

// ?lessEntryKey@VersionBlockKeyCompare@@QBE_NPBUVersionBlockEntry@@PBD@Z
bool VersionBlockKeyCompare::lessEntryKey(const VersionBlockEntry *entry, const char *key) const
{
	const char *entryKey = entry->m_key;
	return (strcmp(entryKey, key) < 0) || false;
}

// ?lessKeyEntry@VersionBlockKeyCompare@@QBE_NPBDPBUVersionBlockEntry@@@Z
bool VersionBlockKeyCompare::lessKeyEntry(const char *key, const VersionBlockEntry *entry) const
{
	const char *entryKey = entry->m_key;
	return (strcmp(key, entryKey) < 0) || false;
}
